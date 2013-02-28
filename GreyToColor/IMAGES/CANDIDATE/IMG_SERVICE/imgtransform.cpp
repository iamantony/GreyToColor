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
