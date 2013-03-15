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
	QList<double> SubsampleImg(const Image &t_img,
							   const int &t_samplesOnHorizFacet,
							   const int &t_samplesOnVerticFacet);

	// Test image dividing to samples
	void TestDivide();
	// Test subsampling image
	void TestSubsampling();

private:
	// Get greyscale image
	QImage GetGreyImg(const Image &t_img);
	// Get images samples rectangulars coordinates
	QList<QRect> GetSamplesRects(const int &t_samplesOnHorizontal,
								 const int &t_samplesOnVertical,
								 const int &t_imgWidth,
								 const int &t_imgHeight);

	// Devide facet of image to samples
	QList< QPair<int, int> > DivideFacet(const int &t_length, const int &t_samplesNum);
	// Calc RGB luminance for each images subsample
	QList<double> CalcSamplesLum(const QImage &t_greyImg, const QList<QRect> &t_samples);
};

#endif // IMGSUBSAMPLER_H
