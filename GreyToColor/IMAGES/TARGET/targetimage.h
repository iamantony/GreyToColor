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

#include "./IMAGES/COMMON/processingimage.h"
#include "./IMAGES/SOURCE/sourceimage.h"
#include "../TARGET/PIXELS/targetimgpixels.h"
#include "../COMMON/PIXELS/rgb.h"

// TODO
// Check functions in TargetImage class

// Class TargetImage
// This class represents an image, that we colorize in colorization process
// This class derived form SourceImage class, so it also consist an real uploaded color image and array
// of pixels with some parameters. Class provides functionality for scaling image luminance (relative LAB luminance)
class TargetImage : public SourceImage
{
	// == DATA ==

	// == METHODS ==
public:
	TargetImage();
	virtual ~TargetImage();

	// Clear all info
	virtual void Clear();
//	// Transform custom pixels from RGB to LAB
//	virtual void TransformImgRGB2LAB();
//	// Get relative luminance of pixel with certain coords
//	double GetPixelsRelLum(const unsigned int &t_width, const unsigned int &t_height) const;
//	// Calc for each pixel in image it's SKO
//	void CalcPixelsSKO();
//	// Get SKO of pixel with certain coords
//	double GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const;
//	// Calc for each pixel in image it's Entropy
//	void CalcPixelsEntropy();
//	// Get Entropy of pixel with certain coords
//	double GetPixelsEntropy(const unsigned int &t_width, const unsigned int &t_height) const;
//	// Get maximum value of relative LAB luminance in image
//	double GetMaxRelLum();
//	// Get minimum value of relative LAB luminance in image
//	double GetMinRelLum();
//	// Get average value of relative LAB luminance in image
//	double GetAverageRelLum();
//	// Get most common value of relative LAB luminance in image
//	double GetMostCommonRelLum();
	// Scale relative luminance of all pixels in image with certain scale factor
	bool ScaleLABRelLum(const double &t_scaleFactor);
	// Unscale relative luminance of all pixels in image
	void RestoreLABRelLum();
	// Normalise relative luminance of all pixels in image by min/max borders
	bool NormaliseLABRelLumByBorders(const double &t_newMinLABRelLum, const double &t_newMaxLABRelLum);
	// Normalise relative luminance of all pixels in image by center
	bool NormaliseLABRelLumByCenter(const double &t_newMinLABRelLum,
									const double &t_newCenterLABRelLum,
									const double &t_newMaxLABRelLum);


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
};

#endif // TARGETIMAGE_H
