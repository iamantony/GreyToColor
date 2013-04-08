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

#ifndef TRAGETIMGPIXELS_H
#define TRAGETIMGPIXELS_H

#include <QFileDialog>
#include <QElapsedTimer>
#include "../../COMMON/PIXELS/imagepixels.h"
#include "targetpixel.h"
#include "./SERVICE/calculatorsko.h"

class TargetImgPixels : public ImagePixels
{
	// == DATA ==

	// == METHODS ==
public:
	TargetImgPixels();
	~TargetImgPixels();

	// Clear info about pixels (call this function before deleting object TragetImgPixels!)
	virtual void Clear();
	// Save all pixels from input QImage as custom pixels
	virtual bool FormImgPixels(const QImage &t_img);
	// Set current LAB luminance as original
	void SetOriginalLuminance();
	// Calc for each pixel in image it's SKO
	void CalcPixelsSKO();
	// Get SKO of pixel with certain coords
	double GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const;
	// Calc for each pixel in image it's Entropy
	void CalcPixelsEntropy();
	// Get Entropy of pixel with certain coords
	double GetPixelsEntropy(const unsigned int &t_width, const unsigned int &t_height) const;
	// Scale luminance of all pixels in image with certain scale factor
	bool ScaleLum(const double &t_scaleFactor);
	// Normalise pixels luminances by min/max borders
	bool NormaliseLumByBorders(const double &t_newMinLum, const double &t_newMaxLum);
	// Normalise pixels luminance by center
	bool NormaliseLumByCenter(const double &t_newMinLum,
							  const double &t_newCenterLum,
							  const double &t_newMaxLum);

	// Restore original luminance of all pixels in image
	void RestoreLum();
	// Set prefered color for certain pixel
	void SetPixPreferedColor(const unsigned int &t_width,
							 const unsigned int &t_height,
							 const RGB &t_prefColor);

	// Set flag that pixel coloured
	void SetPixColoured(const unsigned int &t_width, const unsigned int &t_height);
	// Set flag that all pixels uncoloured
	void SetPixelsUncoloured();
	// Check if pixel is coloured
	bool IsPixColoured(const unsigned int &t_width, const unsigned int &t_height) const;
	// Form from current pixels values entire QImage
	QImage FormImage();

	// Test functions
	void TestFunctionality();
	// Test Calc SKO
	void TestSKO();

private:
	// Calc for certain pixel in image it's SKO
	void CalcPixSKO(const unsigned int &t_width, const unsigned int &t_height);
	// Calc for certain pixel in image it's entropy
	void CalcPixsEntropy(const unsigned int &t_width, const unsigned int &t_height);
};

#endif // TRAGETIMGPIXELS_H
