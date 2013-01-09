#include "imgtransform.h"

ImgTransform::ImgTransform(QObject *parent) :
	QObject(parent)
{
}

void ImgTransform::TransColorImgToGrayImg(QImage *t_img)
{
	if ( NULL == t_img )
	{
		return;
	}

	QColor pixel;
	int R, G, B;
	int width = t_img->width();
	int height = t_img->height();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			pixel = t_img->pixel(x, y);
			R = pixel.red();
			G = pixel.green();
			B = pixel.blue();

			R = 0.299*R + 0.587*G + 0.114*B;

			if(R<0)	R = 0;
			if(R>255) R = 255;

			G = B = R;

			pixel.setRed(R);
			pixel.setGreen(G);
			pixel.setBlue(B);

			t_img->setPixel(x, y, pixel.rgb());
		}
	}
}

bool ImgTransform::NormaliseImg(QImage *t_img)
{
	if ( NULL == t_img )
	{
		qDebug() << "NormaliseImg(): error - invalid arguments";
		return false;
	}

	ImgSearchParams imgSearch;
	int maxLum = imgSearch.FindMaxLuminanceInGrayImg(t_img);
	if ( ERROR == maxLum )
	{
		qDebug() << "GetImgPassports(): error - failed to get image max luminance";
		return false;
	}

	int minLum = imgSearch.FindMinLuminanceInGrayImg(t_img);
	if ( ERROR == minLum )
	{
		qDebug() << "GetImgPassports(): error - failed to get image min luminance";
		return false;
	}

//	qDebug() << "max =" << maxLum;
//	qDebug() << "min =" << minLum;

	QColor pixel;
	int R;
	int imgW = t_img->width();
	int imgH = t_img->height();
	for (int w = 0; w < imgW; w++)
	{
		for (int h = 0; h < imgH; h++)
		{
			pixel = t_img->pixel(w, h);
			R = pixel.red();

			int differenceLum = maxLum - minLum;
			if ( 0 >= differenceLum )
			{
				differenceLum = 1;
			}

			R = (R - minLum)*( (NEW_MAX_LUM - NEW_MIN_LUM) / differenceLum ) + NEW_MIN_LUM;

			pixel.setRed(R);
			pixel.setGreen(R);
			pixel.setBlue(R);

			t_img->setPixel(w, h, pixel.rgb());
		}
	}

//	t_img->save("normalized.bmp");

	return true;
}

bool ImgTransform::LevelLuminanceOfImg(QImage *t_img, int t_levelNum)
{
	if ( NULL == t_img )
	{
		qDebug() << "LevelLuminanceOfImg(): error - invalid arguments";
		return false;
	}

	int divider = (NEW_MAX_LUM + 1)/t_levelNum;
	QColor pixel;
	int R;
	int imgW = t_img->width();
	int imgH = t_img->height();
	for (int w = 0; w < imgW; w++)
	{
		for (int h = 0; h < imgH; h++)
		{
			pixel = t_img->pixel(w, h);
			R = pixel.red();

			R /= divider;

			pixel.setRed(R);
			pixel.setGreen(R);
			pixel.setBlue(R);

			t_img->setPixel(w, h, pixel.rgb());
		}
	}

	t_img->save("leveled.bmp");

	return true;
}
