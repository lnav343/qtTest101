#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QMessageBox>
#include "mytiff.h"
#include "mycsvpalette.h"
#include "myfunctions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    MyTiff *mytiff_1 = nullptr;
    QGraphicsScene *scene_1 = nullptr, *scene_2 = nullptr;
    QGraphicsPixmapItem *item_1 = nullptr, *item_2= nullptr;
    MyCSVPalette *csvpalette =nullptr;
    bool tiffLoaded = false;
    bool paletteLoaded = false;
    bool processing = false;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event) override;
    void  loadTiffImage();
    void  saveTiffImage();
    void  loadCSVPalette();

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_loadCSVPalette_clicked();
    void on_pushButton_2_clicked();
    void on_lineEdit_min_textChanged(const QString &arg1);
    void on_lineEdit_max_textChanged(const QString &arg1);

    void on_pushButton_save_clicked();

public slots:
    void handleFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
