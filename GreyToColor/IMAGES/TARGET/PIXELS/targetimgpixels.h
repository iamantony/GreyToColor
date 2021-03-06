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

#include "../../SOURCE/PIXELS/sourceimgpixels.h"
#include "targetpixel.h"

class TargetImgPixels : public SourceImgPixels
{
	// == DATA ==

	// == METHODS ==
public:
	TargetImgPixels();
	virtual ~TargetImgPixels();

	// Clear info about pixels (call this function before deleting object TragetImgPixels!)
	virtual void Clear();
	// Save all pixels from input QImage as custom pixels
	virtual bool FormImgPixels(const QImage &t_img);
	// Scale relative luminance of all pixels in image with certain scale factor
	bool ScaleRelLum(const double &t_scaleFactor);
	// Restore original relative luminance of all pixels in image
	void RestoreRelLum();
	// Normalise pixels relative luminances by min/max borders
	bool NormaliseRelLumByBorders(const double &t_newMinRelLum, const double &t_newMaxRelLum);
	// Normalise pixels relative luminance by center
	bool NormaliseRelLumByCenter(const double &t_newMinRelLum,
								  const double &t_newCenterRelLum,
								  const double &t_newMaxRelLum);

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
};

#endif // TRAGETIMGPIXELS_H
