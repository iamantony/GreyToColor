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

#ifndef SOURCEIMAGE_H
#define SOURCEIMAGE_H

#include <QFileDialog>

#include "../COMMON/processingimage.h"
#include "../SOURCE/PIXELS/sourceimgpixels.h"
#include "./DEFINES/images.h"

// Class SourceImage
// This class represents an image, that in colorization process provides color information.
// This class derived form ProcessingImage class, so it also consist an real uploaded color image and array
// of pixels with some parameters.
class SourceImage : public ProcessingImage
{
	// == DATA ==

	// == METHODS ==
public:
	SourceImage();
	~SourceImage();

	// Clear all info
	virtual void Clear();
	// Transform custom pixels from RGB to LAB
	virtual void TransformImgRGB2LAB();
	// Calc for each pixel in image it's SKO
	void CalcPixelsSKO();
	// Get SKO of pixel with certain coords
	double GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const;
	// Calc for each pixel in image it's Entropy
	void CalcPixelsEntropy();
	// Get Entropy of pixel with certain coords
	double GetPixelsEntropy(const unsigned int &t_width, const unsigned int &t_height) const;
	// Get maximum value of relative LAB luminance in image
	double GetMaxRelLum();
	// Get minimum value of relative LAB luminance in image
	double GetMinRelLum();
	// Get average value of relative LAB luminance in image
	double GetAverageRelLum();
	// Get most common value of relative LAB luminance in image
	double GetMostCommonRelLum();

	// Test initialising
	void TestInit();
	// Test find LAB histogram central pixel
	void TestFindCentral();

private:
	// Construct custom pixels of loaded image
	virtual void ConstructImgPixels();
};

#endif // SOURCEIMAGE_H
