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

#include "targetpixel.h"

TargetPixel::TargetPixel()
{
	m_lumScaleFactor = 1;
}

TargetPixel::~TargetPixel()
{
	m_lumScaleFactor = 1;
}

// Method for check if pixel is monochrome
bool TargetPixel::IsGrey() const
{
	return true;
}

// Set pixel as grey
void TargetPixel::SetAsGrey(const RGB &t_color)
{

}

// Transform pixel to grey color
void TargetPixel::ToGrey()
{

}

// Scale luminance with some factor
// @input:
// - t_factor - positive scale factor
// @output:
// - true - luminance scaled
// - false - can't scale luminance with that factor
bool TargetPixel::ScaleLum(const double &t_factor)
{
	if ( t_factor <= 0 )
	{
		return false;
	}

	m_lumScaleFactor = t_factor;

	// TODO:
	// scale luminance!

	return true;
}

// Unscale luminance
void TargetPixel::UnScaleLum()
{

}

// Set prefered color for pixel
void TargetPixel::SetPreferedColor(const RGB &t_prefColor)
{

}

// Check if pixel has prefered color
bool TargetPixel::HasPreferedColor() const
{
	return true;
}
