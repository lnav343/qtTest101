#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <QRgb>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <QDebug>

/*********************************************/
QVector<QRgb> loadCSVToPalette(QString fullFilePath);
 int  my_process(cv::Mat src, cv::Mat * dst, QVector<QRgb> palette, unsigned short mintemp, unsigned short maxtemp);
/*********************************************/

#endif // MYFUNCTIONS_H
