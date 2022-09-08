#include "mainwindow.h"
#include "ui_mainwindow.h"

/*********************************************/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
/*********************************************/

/*********************************************/
MainWindow::~MainWindow(){
    delete ui;
}
/*********************************************/

/*********************************************/
void  MainWindow::saveTiffImage(){
    if ( !scene_2 ) {
        QMessageBox::critical(this, "Alert","Tiff no processed!");
        return;
     }

    QString file(QFileDialog::getSaveFileName(this, tr("Save processed TIFF"),"",tr("Tiff Files(*.tiff *.TIFF)")));

    if ( file.isEmpty() ) {
       QMessageBox::critical(this, "Alert","filename empty!");
       return;
    }

    if (!file.isEmpty())    {
      cv::imwrite(file.toStdString(), *mytiff_1->getDst() );
    }
}
/*********************************************/

/*********************************************/
void  MainWindow::loadTiffImage(){
    QFile file(QFileDialog::getOpenFileName(this,"", tr("Open tiff image"),tr("Tiff Files(*.tiff *.TIFF)")));
    mytiff_1 = new MyTiff(&file);
    scene_1 = new QGraphicsScene(this);
    ui->graphicsView_1->setScene(scene_1);
    ui->graphicsView_1->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    item_1 = scene_1->addPixmap(mytiff_1->getQPixmap());

    ui->groupBox_1->setTitle("Original TIFF:  "+QFileInfo(file.fileName()).fileName() + " (" + QString::number(mytiff_1->getChannels()) + ")");
    ui->graphicsView_1->fitInView( (QGraphicsItem *) item_1, Qt::KeepAspectRatio ); // Qt::KeepAspectRatioByExpanding
    //mytiff_1->validGrayscale();
    tiffLoaded = true;
    //mytiff_1->saveMat3(QString("saved_Tiff.txt"));
}
/*********************************************/

/*********************************************/
void  MainWindow::loadCSVPalette(){
    QFile file(QFileDialog::getOpenFileName(this,"", tr("Open CSV palette"),tr("CSV Files(*.csv *.CSV)")));
    csvpalette = new MyCSVPalette(&file);
    ui->groupBox_3->setTitle("CSV Palette:  "+QFileInfo(file.fileName()).fileName());
    ui->label_palette->setPixmap(csvpalette->getQPixmap());
    paletteLoaded = true;
}
/*********************************************/

/*********************************************/
void MainWindow::on_pushButton_1_clicked(){
    loadTiffImage();
}
/*********************************************/

/*********************************************/
void MainWindow::on_pushButton_loadCSVPalette_clicked(){
    loadCSVPalette();
}
/*********************************************/

/*********************************************/
void MainWindow::on_lineEdit_min_textChanged(const QString &arg1){
    int min = arg1.toInt();
    min = min<0?0:min;
    min = min>255?255:min;
    ui->lineEdit_min->setText(QString::number(min));
}
/*********************************************/

/*********************************************/
void MainWindow::on_lineEdit_max_textChanged(const QString &arg1){
    int max = arg1.toInt();
    max = max<0?0:max;
    max = max>255?255:max;
    ui->lineEdit_max->setText(QString::number(max));
}
/*********************************************/

/*********************************************/
void MainWindow::on_pushButton_2_clicked(){

 //if (!tiffLoaded || !paletteLoaded || processing) return;
 if (!tiffLoaded) {
    QMessageBox::critical(this, "Alert","Tiff no loaded!");
    return;
 }

 if ( !paletteLoaded ) {
     QMessageBox::critical(this, "Alert","CSV Palette no loaded!");
     return;
  }

 if ( processing ) {
     QMessageBox::critical(this, "Alert","There is a process running!");
     return;
  }

  processing = true;

  int min = ui->lineEdit_min->text().toInt();
  int max = ui->lineEdit_max->text().toInt();

  mytiff_1->saveMat3(QString("saved_Tiff.txt"));

  // Watcher
  QFutureWatcher<int> *watcher = new QFutureWatcher<int>(this);
  connect(watcher, SIGNAL(finished()), this, SLOT(handleFinished()));
  connect(watcher, SIGNAL(finished()), watcher, SLOT(deleteLater()));

  // Concurrent process
  QFuture<int> future = QtConcurrent::run(&my_process, *mytiff_1->getMat(), mytiff_1->getDst(), csvpalette->getPalette(), min, max);  /*Ok*/
  watcher->setFuture( future);

}
/*********************************************/

/*********************************************/
void MainWindow::handleFinished(){
    //qDebug()<<"End Process\n";

    scene_2 = new QGraphicsScene(this);
    ui->graphicsView_2->setScene(scene_2);
    ui->graphicsView_2->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    item_2 = scene_2->addPixmap(mytiff_1->getQPixmapDst());
    ui->graphicsView_2->fitInView( (QGraphicsItem *) item_2, Qt::KeepAspectRatio ); // Qt::KeepAspectRatioByExpanding

    processing =  false;
}
/*********************************************/

/*********************************************/
void MainWindow::resizeEvent(QResizeEvent* event){
   QMainWindow::resizeEvent(event);
   if (scene_1)  ui->graphicsView_1->fitInView( (QGraphicsItem *) item_1, Qt::KeepAspectRatio);
   if (scene_2)  ui->graphicsView_2->fitInView( (QGraphicsItem *) item_2, Qt::KeepAspectRatio);
}
/*********************************************/

/*********************************************/
void MainWindow::on_pushButton_save_clicked()
{
    saveTiffImage();
}
/*********************************************/
