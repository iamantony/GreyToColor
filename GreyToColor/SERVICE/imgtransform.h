#ifndef IMGTRANSFORM_H
#define IMGTRANSFORM_H

#include <QObject>
#include <QImage>
#include <QColor>
#include "../SERVICE/imgsearchparams.h"

#define NEW_MIN_LUM 0
#define NEW_MAX_LUM 255

class ImgTransform : public QObject
{
	Q_OBJECT
public:
	explicit ImgTransform(QObject *parent = 0);
	void TransColorImgToGrayImg(QImage *t_img);
	bool NormaliseImg(QImage *t_img);
	bool LevelLuminanceOfImg(QImage *t_img, int t_levelNum);


signals:

public slots:

};

#endif // IMGTRANSFORM_H
