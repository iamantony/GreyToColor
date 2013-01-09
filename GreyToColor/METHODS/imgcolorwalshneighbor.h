#ifndef IMGCOLORWALSHNEIGHBOR_H
#define IMGCOLORWALSHNEIGHBOR_H

#include <QObject>
#include <QDebug>
#include <time.h>
#include <math.h>
#include "../IMG_ENTITY/imgentity.h"
#include "../defines.h"

#define TRESHOLD 0.0001
#define LUMINANCE_TRESHOLD 0.09
#define SKO_TRESHOLD 0.01

class ImgColorWalshNeighbor : public QObject
{
	Q_OBJECT

// Data
private:
	ImgEntity *m_imgTarget;
	ImgEntity *m_imgOriginal;

	// Methods
public:
	explicit ImgColorWalshNeighbor(QObject *parent = 0);
	QImage startImgProcessing(QImage t_targ, QImage t_orig);

private:
	void ScaleLuminance();
	void ScaleLuminanceBack();
	void colorTarget();
};

#endif // IMGCOLORWALSHNEIGHBOR_H
