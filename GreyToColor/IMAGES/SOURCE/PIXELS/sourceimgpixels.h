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

#ifndef SOURCEIMGPIXELS_H
#define SOURCEIMGPIXELS_H

#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include "../../COMMON/PIXELS/imagepixels.h"
#include "colorpixel.h"
#include "./SERVICE/calculatorsko.h"

class SourceImgPixels : public ImagePixels
{
	// == DATA ==

	// == METHODS ==
public:
	SourceImgPixels();
	~SourceImgPixels();

	// Clear info about pixels (call this function before deleting object SourceImgPixels!)
	virtual void Clear();
	// Save all pixels from input QImage as custom pixels
	virtual bool FormImgPixels(const QImage &t_img);
	// Calc for each pixel in image it's SKO
	void CalcPixelsSKO();
	// Get SKO of pixel with certain coords
	double GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const;

	// Test functions
	void TestFunctionality();

private:
	// Calc for certain pixel in image it's SKO
	void CalcPixSKO(const unsigned int &t_width, const unsigned int &t_height);
};

#endif // SOURCEIMGPIXELS_H
