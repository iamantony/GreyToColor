#ifndef IMGENTITY_H
#define IMGENTITY_H

#include <QImage>
#include <QColor>
#include <QDebug>
#include "pixelentity.h"
#include "../defines.h"

class ImgEntity
{
// Data
private:
	QImage m_img;
	int m_imgHeight;
	int m_imgWidth;
	PixelEntity **m_pixelsArray;


	// Methods
public:
	explicit ImgEntity();
	~ImgEntity();

	bool SetImg(QImage t_img);
	QImage GetImg();
	int GetImgWidth();
	int GetImgHeight();
	PixelEntity* PixelAt(const int &t_x, const int &t_y);
	void TransformImgRGB2LAB();
	void TransformImgLAB2RGB();
	double PixelLum(const int &t_x, const int &t_y);
	double PixelChA(const int &t_x, const int &t_y);
	double PixelChB(const int &t_x, const int &t_y);
	void SetPixelChA(const int &t_x, const int &t_y, const double &t_chA);
	void SetPixelChB(const int &t_x, const int &t_y, const double &t_chB);
	double MaxLum();
	void ScaleLum(const double &t_scaleFactor);
	void ScaleLumBack();
	void CalcSKO();
	double PixelSKO(const int &t_x, const int &t_y);
	bool PixelHasColor(const int &t_x, const int &t_y);
	void SetPixelHasColor(const int &t_x, const int &t_y);

private:
	void CreatePixelArray();

signals:

public slots:

};

#endif // IMGENTITY_H
