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

#ifndef SOURCEIMAGE_H
#define SOURCEIMAGE_H

#include <QFileDialog>
#include "../COMMON/processingimage.h"
#include "../SOURCE/PIXELS/sourceimgpixels.h"
#include "./DEFINES/images.h"

class SourceImage : public ProcessingImage
{
	// == DATA ==

	// == METHODS ==
public:
	SourceImage();
	~SourceImage();

	// Clear all info
	virtual void Clear();
	// Calc for each pixel in image it's SKO
	void CalcPixelsSKO();
	// Get SKO of pixel with certain coords
	double GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const;

	// Test initialising
	void TestInit();

private:
	// Construct custom pixels of loaded image
	virtual void ConstructImgPixels();
};

#endif // SOURCEIMAGE_H