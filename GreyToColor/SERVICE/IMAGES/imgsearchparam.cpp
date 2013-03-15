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

#include "imgsearchparam.h"

ImgSearchParam::ImgSearchParam()
{

}

// Find min RGB luminance in image
// @input:
// - Image - unnull image (color/grey)
// @output:
// - ERROR - can't find min luminance in image
// - int [0, 255] - found luminance
// - 0 < int > 255 - invalid output
int ImgSearchParam::FindMinLum(const Image &t_img)
{
	QPair<int, int> luminancesRGB = FindMinMaxLum(t_img);
	return luminancesRGB.first;
}

// Find max RGB luminance in image
// @input:
// - Image - unnull image (color/grey)
// @output:
// - ERROR - can't find max luminance in image
// - int [0, 255] - found luminance
// - int > 255 - invalid output
int ImgSearchParam::FindMaxLum(const Image &t_img)
{
	QPair<int, int> luminancesRGB = FindMinMaxLum(t_img);
	return luminancesRGB.second;
}

// Find min and max RGB luminances in image
// @input:
// - Image - unnull image (color/grey)
// @output:
// - QPair<int, int> - min and max luminances
// -- ERROR - can't find such luminance in image
// -- int [0, 255] - found luminance
// -- 0 < int > 255 - invalid output
QPair<int, int> ImgSearchParam::FindMinMaxLum(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "FindMinMaxLum(): Error - invalid arguments";
		QPair<int, int> error(ERROR, ERROR);
		return error;
	}

	ImgTransform imgTransformer;
	Image transformedGreyImg = imgTransformer.ToGrey(t_img);
	if ( true == transformedGreyImg.IsNull() )
	{
		qDebug() << "FindMinMaxLum(): Error - can't find max luminance in that image";
		QPair<int, int> error(ERROR, ERROR);
		return error;
	}

	QImage greyImage = transformedGreyImg.GetImg();
	if ( true == greyImage.isNull() )
	{
		qDebug() << "FindMinMaxLum(): Error - can't find max luminance in that image";
		QPair<int, int> error(ERROR, ERROR);
		return error;
	}

	QRgb pixel;
	int pixelLum;
	int minLum = DEFAULT_MIN_RGB_LUM;
	int maxLum = DEFAULT_MAX_RGB_LUM;
	const int width = greyImage.width();
	const int height = greyImage.height();
	for ( int wdt = 0; wdt < width; wdt++ )
	{
		for ( int hgt = 0; hgt < height; hgt++ )
		{
			pixel = greyImage.pixel(wdt, hgt);
			pixelLum = qRed(pixel);

			if ( pixelLum < minLum )
			{
				minLum = pixelLum;
			}

			if ( maxLum < pixelLum )
			{
				maxLum = pixelLum;
			}
		}
	}

	QPair<int, int> luminances(minLum, maxLum);
	return luminances;
}
