#include "myfunctions.h"

/*********************************************/
QVector<QRgb> loadCSVToPalette(QString fullFilePath){
    QFile file(fullFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QVector<QRgb> palette;
    // Read data from file
    QTextStream stream(&file);
    //    QList<QStringList> data;
    QString separator(",");
    while (stream.atEnd() == false)
    {
        QString line = stream.readLine();
        QStringList data = line.split(separator);
        if( data.size() < 3 ){ return QVector<QRgb>(); }
        palette.append( qRgb( data.at(0).toInt(), data.at(1).toInt(), data.at(2).toInt())  );
    }
    file.close();
    return palette;
}
/*********************************************/

/*********************************************/
 int   my_process(cv::Mat src, cv::Mat* dst, QVector<QRgb> palette, unsigned short mintemp, unsigned short maxtemp){
     unsigned short maxInd = palette.size()-1 ;
     //dst = dsttmp;
     int i,j;
     size_t m=0;
     unsigned short tmp = 0;
     for(i = 0;i<src.rows;i++){
         for(j=0;j<src.cols;j++){
             tmp = (src.at<cv::Vec3b>(i,j)[0] + src.at<cv::Vec3b>(i,j)[1] + src.at<cv::Vec3b>(i,j)[2])/3;

             if(tmp > maxtemp) {tmp = maxtemp;}
             if(tmp < mintemp) {tmp = mintemp;}

             m = round(maxInd *(tmp-mintemp)/(maxtemp-mintemp+.0001));
             if(m > maxInd) {m = maxInd;}
             //if(m < 0) { m = 0;}

             dst->at<cv::Vec3b>(i,j)[0]=qRed(palette[m]);
             dst->at<cv::Vec3b>(i,j)[1]=qGreen(palette[m]);
             dst->at<cv::Vec3b>(i,j)[2]=qBlue(palette[m]);
         }
     }
     return 1;
 }
/*********************************************/

