#ifndef IMGSEARCHPARAMS_H
#define IMGSEARCHPARAMS_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QDebug>
#include "../defines.h"

class ImgSearchParams : public QObject
{
	Q_OBJECT
public:
	explicit ImgSearchParams(QObject *parent = 0);
	int FindMaxLuminanceInGrayImg(QImage *t_img);
	int FindMinLuminanceInGrayImg(QImage *t_img);
	QList<int> CountNumOfPixelsForEachLuminance(QImage *t_img, int t_maxLumLevel);

signals:

public slots:

};

#endif // IMGSEARCHPARAMS_H
