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

#ifndef TARGETIMAGE_H
#define TARGETIMAGE_H

#include "../COMMON/processingimage.h"
#include "../TARGET/PIXELS/targetimgpixels.h"
#include "../COMMON/PIXELS/rgb.h"
#include "./DEFINES/images.h"

class TargetImage : public ProcessingImage
{
	// == DATA ==

	// == METHODS ==
public:
	TargetImage();
	~TargetImage();

	// Clear all info
	virtual void Clear();
	// Calc for each pixel in image it's SKO
	void CalcPixelsSKO();
	// Get SKO of pixel with certain coords
	double GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const;
	// Calc for each pixel in image it's Entropy
	void CalcPixelsEntropy();
	// Get Entropy of pixel with certain coords
	double GetPixelsEntropy(const unsigned int &t_width, const unsigned int &t_height) const;
	// Scale luminance of all pixels in image with certain scale factor
	bool ScaleLABLum(const double &t_scaleFactor);
	// Normalise luminance of all pixels in image by min/max borders
	bool NormaliseLABLumByBorders(const double &t_newMinLABLum, const double &t_newMaxLABLum);
	// Normalise luminance of all pixels in image by center
	bool NormaliseLABLumByCenter(const double &t_newMinLABLum,
											 const double &t_newCenterLABLum,
											 const double &t_newMaxLABLum);

	// Unscale luminance of all pixels in image
	void RestoreLABLum();
	// Set prefered color for certain pixel
	void SetPixPrefColor(const unsigned int &t_width,
						 const unsigned int &t_height,
						 const RGB &t_prefColor);

	// Set flag that pixel colored
	void SetPixColoured(const unsigned int &t_width, const unsigned int &t_height);
	// Set flag that all pixels uncolored
	void SetPixelsUncoloured();
	// Check if pixel is colored
	bool IsPixColoured(const unsigned int &t_width, const unsigned int &t_height) const;
	// Get result image. It could be colorized (if we perform colorization) or
	// greyscale as original target (if we have not performed colorizztion yet).
	Image GetResultImage();

private:
	// Construct custom pixels of loaded image
	virtual void ConstructImgPixels();
	// Save current LAB luminance of pixels as original luminance
	void SetOrigLum();
};

#endif // TARGETIMAGE_H
