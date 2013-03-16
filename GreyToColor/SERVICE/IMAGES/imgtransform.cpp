/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2013, Antony Cherepanov <antony.cherepanov@gmail.com>
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
//		qDebug() << "ToGrey(): image is already greyscale";
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
// - Image - normalised greyscaled image
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
// - Image - normalied greyscaled image
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

// Level image luminance up to maximum luminance level
// @input:
// - Image - unnull image (color/greyscale)
// - int - positive value of image new RGB max luminance [0, 255]
// @output:
// - null Image - can't level image luminance
// - Image - normalied greyscale image
Image ImgTransform::LevelLuminance(const Image &t_img, const int &t_maxLum)
{
	if ( (true == t_img.IsNull()) ||
		 (t_maxLum < 0) ||
		 (255 < t_maxLum))
	{
		qDebug() << "LevelLuminance(): Error - invalid arguments";
		Image empty;
		return empty;
	}

	Image greyImg = ToGrey(t_img);
	if ( true == greyImg.IsNull() )
	{
		qDebug() << "LevelLuminance(): Error - can't greyscale image";
		Image empty;
		return empty;
	}

	Image leveledImg = PerformLumLeveling(greyImg, t_maxLum);
	if ( true == leveledImg.IsNull() )
	{
		qDebug() << "LevelLuminance(): Error - can't level image luminance";
		Image empty;
		return empty;
	}

	return leveledImg;
}

// Create image with leveled luminance
// @input:
// - Image - unnull greyscale image
// - int - positive value of image new RGB max luminance [0, 255]
// @output:
// - null Image - can't level image luminance
// - Image - normalied greyscale image
Image ImgTransform::PerformLumLeveling(const Image &t_greyImg, const int &t_maxLum) const
{
	if ( (true == t_greyImg.IsNull()) ||
		 (t_maxLum < 0) ||
		 (255 < t_maxLum))
	{
		qDebug() << "PerformLumLeveling(): Error - invalid arguments";
		Image empty;
		return empty;
	}

	Image greyImage = t_greyImg;
	QImage processingImg = greyImage.GetImg();
	if ( true == processingImg.isNull() )
	{
		qDebug() << "PerformLumLeveling(): Error - no image";
		Image empty;
		return empty;
	}

	const double scaleFactor = (double)t_maxLum / (double)MAX_RGB_LUM;
	const int imgW = processingImg.width();
	const int imgH = processingImg.height();
	for (int wdt = 0; wdt < imgW; wdt++)
	{
		for (int hgt = 0; hgt < imgH; hgt++)
		{
			QRgb pixel = processingImg.pixel(wdt, hgt);
			double lum = (double)qRed(pixel);

			lum *= scaleFactor;

			int newLum = (int)floor(lum + 0.5);
			QRgb leveledPixel = qRgb(newLum, newLum, newLum);
			processingImg.setPixel(wdt, hgt, leveledPixel);
		}
	}

	Image leveledImg = t_greyImg;
	leveledImg.SetImage(processingImg);

	return leveledImg;
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

// Test image luminance leveling function
void ImgTransform::TestLumLeveling()
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

	Image leveledImg = LevelLuminance(testImg, 200);
	if ( true == leveledImg.IsNull() )
	{
		qDebug() << "TestLumLeveling(): Fail - leveled image is NULL";
		return;
	}

	QString pathToSave = QFileDialog::getSaveFileName(&wdt,
													  "Save as...",
													  QDir::currentPath(),
													  "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	leveledImg.SetImgPath(pathToSave);
	leveledImg.SaveImg();
}
