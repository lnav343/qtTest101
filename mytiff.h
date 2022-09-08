#ifndef MYTIFF_H
#define MYTIFF_H

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QFile>
#include <opencv2/opencv.hpp>
#include <string>
#include <QRgb>
#include <QColor>
#include <QMessageBox>
#include "myfunctions.h"

class MyTiff
{
private:
    cv::Mat inMat;
    cv::Mat dst;
    QPixmap  getQPixmap(cv::Mat mat);

public:
    MyTiff(QFile *);
    //MyTiff(cv::Mat *);
    QPixmap getQPixmap();
    QPixmap getQPixmapDst();
    int getType();
    int getChannels();
    int validGrayscale();
    cv::Mat* getMat();
    cv::Mat* getDst();
    void saveMat3(QString filename);
    void saveMat1(QString filename);
};

#endif // MYTIFF_H

