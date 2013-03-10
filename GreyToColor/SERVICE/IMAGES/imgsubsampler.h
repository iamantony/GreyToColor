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

#ifndef IMGSUBSAMPLER_H
#define IMGSUBSAMPLER_H

#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include <math.h>
#include "./IMAGES/COMMON/image.h"
#include "imgtransform.h"
#include "DEFINES/imgservice.h"

class ImgSubsampler
{
	// == DATA ==

	// == METHODS ==
public:
	ImgSubsampler();

	// Subsample image and get RGB luminances of each sample
	QList<double> SubsampleImg(const Image &t_img, const int &t_numOfSamplesOnFacet);

private:
	// Get greyscale image
	QImage GetGreyImg(const Image &t_img);
	// Get images samples rectangulars coordinates
	QList<QRect> GetSamplesRects(const int &t_numOfSamplesOnFacet,
								 const int &t_imgWidth,
								 const int &t_imgHeight);
};

#endif // IMGSUBSAMPLER_H
