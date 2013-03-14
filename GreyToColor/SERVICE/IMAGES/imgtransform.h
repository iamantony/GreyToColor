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

#ifndef IMGTRANSFORM_H
#define IMGTRANSFORM_H

#include <QFileDialog>
#include <QImage>
#include <QPair>
#include <QDebug>
#include <math.h>
#include "./IMAGES/COMMON/image.h"
#include "./IMAGES/COMMON/PIXELS/rgb.h"
#include "imgsearchparam.h"
#include "./DEFINES/imgservice.h"

class ImgTransform
{
	// == DATA ==

	// == METHODS ==
public:
	ImgTransform();

	// Transform color image to grey image
	Image ToGrey(const Image &t_img);
	// Normalise image histogram
	Image NormaliseImgHistogram(const Image &t_img);
	// Level image luminance up to maximum luminance level
	Image LevelLuminance(const Image &t_img, const int &t_maxLum);

	// Test image normalization function
	void TestNormalization();
	// Test image luminance leveling function
	void TestLumLeveling();

private:
	// Create greyscale image-copy of input image
	QImage GreyscaleImg(const QImage &t_colorImg);
	// Create normalised image
	Image PerformImgNormalisation(const Image &t_greyImg) const;
	// Create image with leveled luminance
	Image PerformLumLeveling(const Image &t_greyImg, const int &t_maxLum) const;
};

#endif // IMGTRANSFORM_H
