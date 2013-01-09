#ifndef IMGHANDLER_H
#define IMGHANDLER_H

#include <QObject>
#include <QMessageBox>
#include <QImage>
#include <QColor>
#include "METHODS/imgcolorwalshsimple.h"
#include "METHODS/imgcolorwalshneighbor.h"
#include "SERVICE/comparestuff.h"
#include "SERVICE/imgtransform.h"
#include "defines.h"

class ImgHandler : public QObject
{
	Q_OBJECT

	/*------------------------------------------------------------------------------*/
	/*-----------------------------Data-------------------------------------------*/
	/*------------------------------------------------------------------------------*/
private:
	QImage m_imgMass[3];

	/*------------------------------------------------------------------------------*/
	/*-----------------------------Methods-------------------------------------------*/
	/*------------------------------------------------------------------------------*/
public:
	explicit ImgHandler(QObject *parent = 0);
	void setImg(QImage t_img, int t_type);
	QImage getImg(int t_type);
	void getGrayImg(QString t_imgPath);
	void getColorImg(QString t_imgPath);

	QImage startImgColorizationWSimple();
	QImage startImgColorizationWNeighbor();
	void imageComparison (QImage &t_targ, QImage &t_coloured);

private:
	void setImg2Label(QImage *t_img, int t_type);
	void getLumImg(QImage *t_img);

signals:
	void signalImagesSKO (QString);
	void signalEnableProcButtn(int);
	void signalSetTargetImg(QImage);
	void signalSetResultImg(QImage);
	void signalSetOriginalImg(QImage);

public slots:

};

#endif // IMGHANDLER_H
