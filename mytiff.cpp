#include "mytiff.h"
/*********************************************/

/*********************************************/
MyTiff::MyTiff(QFile* file){
  inMat  = cv::imread( file->fileName().toStdString());
  dst    = inMat.clone();
}
/*********************************************/

/*********************************************/
int MyTiff::getType(){
return inMat.type();
}
/*********************************************/

/*********************************************/
cv::Mat* MyTiff::getMat(){
    return &inMat;
}
/*********************************************/

/*********************************************/
cv::Mat* MyTiff::getDst(){
    return &dst;
}
/*********************************************/

/*********************************************/
int MyTiff::getChannels(){
return inMat.channels();
}
/*********************************************/

/*********************************************/
QPixmap MyTiff::getQPixmap(cv::Mat mat){
  switch ( mat.type() ) {
    case CV_8UC3:{
       QImage image( mat.data,
                     mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_RGB888 );

       return QPixmap::fromImage( image.rgbSwapped());
    }
    default:{
       qWarning() << "Error: cv::Mat image type not handled:" << mat.type();
       return QPixmap(0,0);

    }
  }
}
/*********************************************/

/*********************************************/
QPixmap MyTiff::getQPixmap(){
   return getQPixmap(inMat);
}
/*********************************************/

/*********************************************/
QPixmap MyTiff::getQPixmapDst(){
   return getQPixmap(dst);
}
/*********************************************/

/*********************************************/
int MyTiff::validGrayscale(){
    int i,j;
    for(i = 0;i<inMat.rows;i++){
        for(j=0;j<inMat.cols;j++){
            cv::Vec3b bgr = inMat.at<cv::Vec3b>(i, j);
            if (bgr[0]==bgr[1] && bgr[0]==bgr[2])
            {
                continue;
            }
            else
            {
                qDebug() << "ERROR\n";
                return 0;
            }
        }
    }
    qDebug() << "Ok, grayscale\n";
    return 1;
}
/*********************************************/

/*********************************************/
void MyTiff::saveMat3(QString filename){
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outStream(&file);

    int min0,max0,min1,max1,min2,max2;
    min0 = min1 = min2 = 1000;
    max0 = max1 = max2 = 0;
    int i,j;
    for(i = 0;i<inMat.rows;i++){
        for(j=0;j<inMat.cols;j++){
            cv::Vec3b bgr = inMat.at<cv::Vec3b>(i, j);
            outStream << "(" << bgr(0) << "," << bgr(1) << "," << bgr(2) << "), ";
            if  (bgr(0)<min0) min0=bgr(0);
            if  (bgr(1)<min1) min1=bgr(1);
            if  (bgr(2)<min2) min2=bgr(2);
            if  (bgr(0)>max0) max0=bgr(0);
            if  (bgr(1)>max1) max1=bgr(1);
            if  (bgr(2)>max2) max2=bgr(2);
        }
        outStream <<  "\n"  ;
    }

    outStream <<  "\n"  ;
    outStream <<  "Results: \n"  ;
    outStream <<  "channel 0: min=" << min0 << "  max=" << max0 << "\n";
    outStream <<  "channel 1: min=" << min1 << "  max=" << max1 << "\n";
    outStream <<  "channel 2: min=" << min2 << "  max=" << max2 << "\n";
    file.close();
}
/*********************************************/

/*********************************************/
void MyTiff::saveMat1(QString filename){
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outStream(&file);

    int min0,max0;
    min0  = 1000;
    max0  = 0;
    int i,j;
    for(i = 0;i<inMat.rows;i++){
        for(j=0;j<inMat.cols;j++){
            unsigned short bgr = inMat.at<unsigned short>(i, j);
            outStream << "(" << bgr << "), ";
            if  (bgr<min0) min0=bgr;
            if  (bgr>max0) max0=bgr;        }
        outStream <<  "\n"  ;
    }

    outStream <<  "\n"  ;
    outStream <<  "Results: \n"  ;
    outStream <<  "channel 0: min=" << min0 << "  max=" << max0 << "\n";
    file.close();
}
/*********************************************/


