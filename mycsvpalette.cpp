#include "mycsvpalette.h"

/*********************************************/
MyCSVPalette::MyCSVPalette(QFile* file){
    palette = loadCSVToPalette(file->fileName());
}
/*********************************************/

/*********************************************/
QImage  MyCSVPalette::getQImage(){
    QImage image(palette.length(), 1, QImage::Format_RGB32);
    for (int i=0; i<palette.length(); i++){
        image.setPixel(i,0,palette[i]);
    }
    return image;
}
/*********************************************/

/*********************************************/
QPixmap MyCSVPalette::getQPixmap(){
   return QPixmap::fromImage( getQImage() );
}
/*********************************************/

/*********************************************/
QVector<QRgb> MyCSVPalette::getPalette(){
   return palette;
}
/*********************************************/
