#ifndef IMGPASSPORT_H
#define IMGPASSPORT_H

#include <QObject>
#include <QString>
#include <QImage>
#include <QDebug>
#include "../SERVICE/imgtransform.h"
#include "../SERVICE/imgsearchparams.h"
#include "../defines.h"

#define PASSPORT_LENGTH 128
#define MAX_LUM 128

class ImgPassport : public QObject
{
	Q_OBJECT
public:
	explicit ImgPassport(QObject *parent = 0);
	QList<QByteArray> GetImgPassports(QImage *t_img);
	QList<double> ConvertFromByteArrayToDoubleList(QByteArray t_array);

private:
	QByteArray GetScaledLuminancePassport(QImage *t_img);
	QList<double> CountPercentOfPixelsForEachLuminance(QImage *t_img, int t_maxLumLevel);

signals:

public slots:

};

#endif // IMGPASSPORT_H
