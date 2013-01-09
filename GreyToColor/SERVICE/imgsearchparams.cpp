#include "imgsearchparams.h"

ImgSearchParams::ImgSearchParams(QObject *parent) :
	QObject(parent)
{
}

int ImgSearchParams::FindMaxLuminanceInGrayImg(QImage *t_img)
{
	if ( NULL == t_img )
	{
		qDebug() << "FindMaxLuminanceInGrayImg(): error - invalid arguments";
		return ERROR;
	}

	if ( false == t_img->isGrayscale() )
	{
		qDebug() << "FindMaxLuminanceInGrayImg(): error - image is not grayscale";
		return ERROR;
	}


	QColor pixel;
	int R;
	pixel = t_img->pixel(0, 0);
	int maxLum = pixel.red();

	int imgW = t_img->width();
	int imgH = t_img->height();
	for (int w = 0; w < imgW; w++)
	{
		for (int h = 0; h < imgH; h++)
		{
			pixel = t_img->pixel(w, h);
			R = pixel.red();
			if ( maxLum < R )
			{
				maxLum = R;
			}
		}
	}

	if ( maxLum < 0 )
	{
		maxLum = 0;
	}

	if ( 255 < maxLum )
	{
		maxLum = 255;
	}

	return maxLum;
}

int ImgSearchParams::FindMinLuminanceInGrayImg(QImage *t_img)
{
	if ( NULL == t_img )
	{
		qDebug() << "FindMinLuminanceInGrayImg(): error - invalid arguments";
		return ERROR;
	}

	if ( false == t_img->isGrayscale() )
	{
		qDebug() << "FindMinLuminanceInGrayImg(): error - image is not grayscale";
		return ERROR;
	}

	QColor pixel;
	int R;
	pixel = t_img->pixel(0, 0);
	int minLum = pixel.red();

	int imgW = t_img->width();
	int imgH = t_img->height();
	for (int w = 0; w < imgW; w++)
	{
		for (int h = 0; h < imgH; h++)
		{
			pixel = t_img->pixel(w, h);
			R = pixel.red();
			if ( minLum > R )
			{
				minLum = R;
			}
		}
	}

	if ( minLum < 0 )
	{
		minLum = 0;
	}

	if ( 255 < minLum )
	{
		minLum = 255;
	}

	return minLum;
}

QList<int> ImgSearchParams::CountNumOfPixelsForEachLuminance(QImage *t_img, int t_maxLumLevel)
{
	QList<int> pixelsPerLum;

	if ( NULL == t_img )
	{
		qDebug() << "CountNumOfPixelsForEachLuminance(): error - invalid arguments";
		return pixelsPerLum;
	}

	// Create list with size of max luminance level
	for (int i = 0; i < t_maxLumLevel; i++)
	{
		pixelsPerLum.append(0);
	}

	QColor pixel;
	int R;
	int numOfPixels;
	int imgW = t_img->width();
	int imgH = t_img->height();
	for (int w = 0; w < imgW; w++)
	{
		for (int h = 0; h < imgH; h++)
		{
			pixel = t_img->pixel(w, h);
			R = pixel.red();

			if ( t_maxLumLevel <= R )
			{
				R = t_maxLumLevel;
			}

			numOfPixels = pixelsPerLum.at(R);
			numOfPixels++;
			pixelsPerLum.replace(R, numOfPixels);
		}
	}

	return pixelsPerLum;
}
