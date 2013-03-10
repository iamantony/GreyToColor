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

#include "imgsubsampler.h"

ImgSubsampler::ImgSubsampler()
{

}

// Subsample image and get RGB luminances of each sample
// @input:
// - Image - unnul image (color/grey)
// - unsigned int - num of samples we should divide input image
// @output:
// - empty QList<double> - failed to subsample image
// - QList<double> - RGB luminances of each sample of subsampled image
QList<double> ImgSubsampler::SubsampleImg(const Image &t_img, const int &t_numOfSamplesOnFacet)
{
	if ( (true == t_img.IsNull()) || (t_numOfSamplesOnFacet <= 0) )
	{
		qDebug() << "SubsampleImg(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	QImage greyImg = GetGreyImg(t_img);
	if ( true == greyImg.isNull() )
	{
		qDebug() << "SubsampleImg(): Error - no grey image";
		QList<double> empty;
		return empty;
	}

	// TODO:
	// - even and odd number of samples
	// - what if size of input image is not divided in samples
}

// Get greyscale image
// @input:
// - Image - unnul image
// @output:
// - null QImage - failed to greyscale image
// - QImage - grey image
QImage ImgSubsampler::GetGreyImg(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "GetGreyImg(): Error - invalid arguments";
		QImage empty;
		return empty;
	}

	ImgTransform imgTransformer;
	Image greyImg = imgTransformer.ToGrey(t_img);
	if ( true == greyImg.IsNull() )
	{
		qDebug() << "GetGreyImg(): Error - can't greyscale image";
		QImage empty;
		return empty;
	}

	QImage greyscaledImg = greyImg.GetImg();
	if ( true == greyscaledImg.isNull() )
	{
		qDebug() << "GetGreyImg(): Error - can't get grey image";
		QImage empty;
		return empty;
	}

	return greyscaledImg;
}

// Get images samples rectangulars coordinates
// @input:
// - int - positive image width
// - int - positive image height
// @output:
// - empty QList<QRect> - failed calc rects of samples
// - QList<QRect> - samples coords
QList<QRect> ImgSubsampler::GetSamplesRects(const int &t_numOfSamplesOnFacet,
											const int &t_imgWidth,
											const int &t_imgHeight)
{
	if ( (t_numOfSamples <= 0) ||
		 (t_imgWidth <= 0) ||
		 (t_imgHeight <= 0) )
	{
		qDebug() << "GetSamplesRects(): Error - invalid arguments";
		QList<QRect> empty;
		return empty;
	}

	// Number of samples must be even
	unsigned int numOfSamples = t_numOfSamples;
	unsigned int modulo = numOfSamples % 2;
	if ( (1 == modulo) && (1 < numOfSamples) )
	{
		numOfSamples--;
	}

//	unsigned int numOfRows = t_imgWidth / numOfSamples;
//	if ( t_imgWidth < numOfSamples )
//	{
//		numOfRows = 1;
//	}

//	unsigned int moduloRow = t_imgWidth % numOfSamples;
//	if ( 0 != moduloRow )
//	{
//		unsigned int rowLenth = t_imgWidth
//		if (  )
//	}

	QList<QRect> empty;
	return empty;
}
