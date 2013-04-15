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

#ifndef PIXEL_H
#define PIXEL_H

#include <QColor>
#include <QDebug>

#include "rgb.h"
#include "lab.h"
#include "COLOR_SPACE/rgblab.h"

class Pixel
{
	// == DATA ==
private:
	RGB m_pixelInRGB;
	LAB m_pixelInLAB;

	// == METHODS ==
public:
	explicit Pixel();
	~Pixel();

	// Set RGB color for pixel
	void SetRGB(const RGB &t_rgbColor);
	// Get color of pixel in RGB color space
	RGB GetRGB() const;
	// Check if current RGB color is a grey color
	bool IsGrey() const;
	// Setup new luminance value for pixel
	bool SetChL(const double &t_lum);
	// Setup new value of channel A for pixel
	void SetChA(const double &t_a);
	// Setup new value of channel B for pixel
	void SetChB(const double &t_b);
	// Return Luminance channel value
	double GetChL() const;
	// Return A-channel value
	double GetChA() const;
	// Return B-channel value
	double GetChB() const;
	// Transform current pixels RGB coords to LAB coords
	void TransformRGB2LAB();
	// Transform current pixels LAB coords to RGB coords
	void TransformLAB2RGB();

protected:
	// Set RGB color for as black pixel
	void Clear();
};

#endif // PIXEL_H
