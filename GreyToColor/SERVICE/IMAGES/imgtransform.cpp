/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012, Antony Cherepanov <antony.cherepanov@gmail.com>
 *
 *	GreyToColor is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	GreyToColor is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with GreyToColor. If not, see <http://www.gnu.org/licenses/>.
 */

#include "imgtransform.h"

ImgTransform::ImgTransform()
{

}

// Transform color image to grey image
// @input:
// - Image - unnull image (color/grey)
// @output:
// - null Image - can't transform to grey
// - Image - grey image-copy of input image
Image ImgTransform::ToGrey(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "ToGrey(): Error - invalid arguments";
		Image empty;
		return empty;
	}

	QImage colorImage = t_img.GetImg();
	if ( true == colorImage.isNull() )
	{
		qDebug() << "ToGrey(): Error - no image";
		Image empty;
		return empty;
	}

	if ( true == colorImage.isGrayscale() )
	{
		qDebug() << "ToGrey(): image is already greyscale";
		return t_img;
	}

	QImage greyImage = GreyscaleImg(colorImage);
	if ( true == greyImage.isNull() )
	{
		qDebug() << "ToGrey(): Error - can't transform image to greyscale";
		Image empty;
		return empty;
	}

	Image greyOutImg;
	// Save all info from input image
	greyOutImg = t_img;
	greyOutImg.SetImage(greyImage);

	return greyOutImg;
}

// Create greyscale image-copy of input image
// @input:
// - QImage - unnull color image
// @output:
// - null QImage - can't transform to grey
// - QImage - grey image-copy of input image
QImage ImgTransform::GreyscaleImg(const QImage &t_colorImg)
{
	if ( true == t_colorImg.isNull() )
	{
		qDebug() << "GreyscaleImg(): Error - invalid arguments";
		QImage empty;
		return empty;
	}

	QImage greyImage;
	greyImage = t_colorImg;

	// Transform all image pixels to grey
	QRgb defaultColor;
	defaultColor = qRgb(0, 0, 0);

	QRgb imgPixelColor;
	QRgb newGreyPixel;
	RGB pixelRGB;

	const int width = greyImage.width();
	const int height = greyImage.height();
	for ( int wdt = 0; wdt < width; wdt++ )
	{
		for ( int hgt = 0; hgt < height; hgt++ )
		{
			imgPixelColor = greyImage.pixel(wdt, hgt);
			bool colorSet = pixelRGB.SetColor(qRed(imgPixelColor),
											  qGreen(imgPixelColor),
											  qBlue(imgPixelColor));

			if ( false == colorSet )
			{
				qDebug() << "GreyscaleImg(): Warning - pixel [" << width << height << "] set to default";
				greyImage.setPixel(wdt, hgt, defaultColor);
				continue;
			}

			pixelRGB.ToGrey();
			newGreyPixel = qRgb(pixelRGB.GetRed(),
								pixelRGB.GetGreen(),
								pixelRGB.GetBlue());

			greyImage.setPixel(wdt, hgt, newGreyPixel);
		}
	}

	return greyImage;
}

// Normalise image histogram
// @input:
// - Image - unnull image (color/greyscale)
// @output:
// - null Image - can't normalise histogram
// - Image - normalised image
Image ImgTransform::NormaliseImgHistogram(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "NormaliseImgHistogram(): Error - invalid arguments";
		Image empty;
		return empty;
	}

	Image greyImg = ToGrey(t_img);
	if ( true == greyImg.IsNull() )
	{
		qDebug() << "NormaliseImgHistogram(): Error - can't greyscale image";
		Image empty;
		return empty;
	}

	Image normalisedImg = PerformImgNormalisation(greyImg);
	if ( true == normalisedImg.IsNull() )
	{
		qDebug() << "NormaliseImgHistogram(): Error - can't normalise image histogram";
		Image empty;
		return empty;
	}

	return normalisedImg;
}

// Create normalised image
// @input:
// - Image - unnull greyscale image
// @output:
// - null Image - can't normalise image
// - Image - normalied image
Image ImgTransform::PerformImgNormalisation(const Image &t_greyImg) const
{
	if ( true == t_greyImg.IsNull() )
	{
		qDebug() << "PerformImgNormalisation(): Error - invalid arguments";
		Image empty;
		return empty;
	}

	Image greyImage = t_greyImg;

	ImgSearchParam imgSearch;
	const QPair<int, int> minMaxLum = imgSearch.FindMinMaxLum(greyImage);
	if ( (ERROR == minMaxLum.first) || (ERROR == minMaxLum.second) )
	{
		qDebug() << "PerformImgNormalisation(): Error - can't find min-max luminance of image";
		Image empty;
		return empty;
	}

	QImage processingImg = greyImage.GetImg();
	if ( true == processingImg.isNull() )
	{
		qDebug() << "PerformImgNormalisation(): Error - no image";
		Image empty;
		return empty;
	}

	const double minLum = (double)minMaxLum.first;
	const double maxLum = (double)minMaxLum.second;

	double diffLum = abs( maxLum - minLum );
	if ( diffLum <= 0 )
	{
		diffLum = 1;
	}

	double scaleFactor = (MAX_RGB_LUM - MIN_RGB_LUM) / diffLum;
	if ( scaleFactor <= 0 )
	{
		scaleFactor = 1;
	}

	const int imgW = processingImg.width();
	const int imgH = processingImg.height();
	for (int wdt = 0; wdt < imgW; wdt++)
	{
		for (int hgt = 0; hgt < imgH; hgt++)
		{
			QRgb pixel = processingImg.pixel(wdt, hgt);
			double lum = (double)qRed(pixel);

			lum = (lum - minLum) * scaleFactor + (double)MIN_RGB_LUM;

			int newLum = (int)floor(lum + 0.5);
			QRgb normalizedPixel = qRgb(newLum, newLum, newLum);
			processingImg.setPixel(wdt, hgt, normalizedPixel);
		}
	}

	Image normalizedImg = t_greyImg;
	normalizedImg.SetImage(processingImg);

	return normalizedImg;
}

// Test image normalization function
void ImgTransform::TestNormalization()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												 "Open target image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	Image testImg;
	testImg.LoadImg(imgName);

	Image greyscaled = ToGrey(testImg);
	QString pathToSaveGrey = QFileDialog::getSaveFileName(&wdt,
														  "Save as...",
														  QDir::currentPath(),
														  "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	greyscaled.SetImgPath(pathToSaveGrey);
	greyscaled.SaveImg();

	Image normalizedImg = NormaliseImgHistogram(testImg);
	if ( true == normalizedImg.IsNull() )
	{
		qDebug() << "TestNormalization(): Fail - normalised image is NULL";
		return;
	}

	QString pathToSave = QFileDialog::getSaveFileName(&wdt,
													  "Save as...",
													  QDir::currentPath(),
													  "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	normalizedImg.SetImgPath(pathToSave);
	normalizedImg.SaveImg();
}

//bool ImgTransform::NormaliseImg(QImage *t_img)
//{
//	if ( NULL == t_img )
//	{
//		qDebug() << "NormaliseImg(): error - invalid arguments";
//		return false;
//	}

//	ImgSearchParams imgSearch;
//	int maxLum = imgSearch.FindMaxLuminanceInGrayImg(t_img);
//	if ( ERROR == maxLum )
//	{
//		qDebug() << "GetImgPassports(): error - failed to get image max luminance";
//		return false;
//	}

//	int minLum = imgSearch.FindMinLuminanceInGrayImg(t_img);
//	if ( ERROR == minLum )
//	{
//		qDebug() << "GetImgPassports(): error - failed to get image min luminance";
//		return false;
//	}

////	qDebug() << "max =" << maxLum;
////	qDebug() << "min =" << minLum;

//	QColor pixel;
//	int R;
//	int imgW = t_img->width();
//	int imgH = t_img->height();
//	for (int w = 0; w < imgW; w++)
//	{
//		for (int h = 0; h < imgH; h++)
//		{
//			pixel = t_img->pixel(w, h);
//			R = pixel.red();

//			int differenceLum = maxLum - minLum;
//			if ( 0 >= differenceLum )
//			{
//				differenceLum = 1;
//			}

//			R = (R - minLum)*( (NEW_MAX_LUM - NEW_MIN_LUM) / differenceLum ) + NEW_MIN_LUM;

//			pixel.setRed(R);
//			pixel.setGreen(R);
//			pixel.setBlue(R);

//			t_img->setPixel(w, h, pixel.rgb());
//		}
//	}

////	t_img->save("normalized.bmp");

//	return true;
//}

//bool ImgTransform::LevelLuminanceOfImg(QImage *t_img, int t_levelNum)
//{
//	if ( NULL == t_img )
//	{
//		qDebug() << "LevelLuminanceOfImg(): error - invalid arguments";
//		return false;
//	}

//	int divider = (NEW_MAX_LUM + 1)/t_levelNum;
//	QColor pixel;
//	int R;
//	int imgW = t_img->width();
//	int imgH = t_img->height();
//	for (int w = 0; w < imgW; w++)
//	{
//		for (int h = 0; h < imgH; h++)
//		{
//			pixel = t_img->pixel(w, h);
//			R = pixel.red();

//			R /= divider;

//			pixel.setRed(R);
//			pixel.setGreen(R);
//			pixel.setBlue(R);

//			t_img->setPixel(w, h, pixel.rgb());
//		}
//	}

//	t_img->save("leveled.bmp");

//	return true;
//}
