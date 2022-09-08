#ifndef MYCSVPALETTE_H
#define MYCSVPALETTE_H

#include <QRgb>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QImage>
#include <QPixmap>
#include "myfunctions.h"


class MyCSVPalette
{
    QVector<QRgb> palette;

public:
    MyCSVPalette(QFile *);
    QPixmap getQPixmap();
    QImage  getQImage();
    QVector<QRgb> getPalette();
};

#endif // MYCSVPALETTE_H
