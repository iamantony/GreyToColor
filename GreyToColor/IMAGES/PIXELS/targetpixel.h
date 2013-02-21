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

#ifndef TARGETPIXEL_H
#define TARGETPIXEL_H

#include <QDebug>
#include "colorpixel.h"
#include "preferedcolor.h"

#define DEFAULT_SCALE_LUM_FACTOR 1

class TargetPixel : public ColorPixel
{
	// == DATA ==
private:
	double m_lumScaleFactor;
	PreferedColor m_prefColor;

	// == METHODS ==
public:
	TargetPixel();
	~TargetPixel();

	// Clear all info about target pixel (set it to defaults)
	void ClearPixel();
	// Set pixel as grey variant of input RGB pixel
	void SetAsGrey(const RGB &t_color);
	// Set current pixel as grey
	void SetAsGrey();
	// Scale luminance with some factor
	bool ScaleLum(const double &t_factor);
	// Unscale luminance
	bool UnScaleLum();
	// Set prefered color for pixel
	void SetPreferedColor(const RGB &t_prefColor);
	// Check if pixel has prefered color
	bool HasPreferedColor() const;

private:
	// Transform pixel to grey color
	void ToGrey(const RGB &t_color);

	// == TESTS ==
public:
	void TestSetAsGrey();
	void TestScaleLum();
};

#endif // TARGETPIXEL_H
