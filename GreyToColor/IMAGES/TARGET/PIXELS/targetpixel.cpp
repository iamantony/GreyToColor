/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2014, Antony Cherepanov <antony.cherepanov@gmail.com>
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

#include <math.h>
#include <QDebug>
#include "targetpixel.h"
#include "./DEFINES/pixels.h"

TargetPixel::TargetPixel(const RGB *t_rgbColor) : ColorPixel(t_rgbColor)
{

}

TargetPixel::~TargetPixel()
{
	ClearPixel();
}

// Clear all info about target pixel (set it to defaults)
// @input:
// @output:
void TargetPixel::ClearPixel()
{
	m_prefColor.ClearColor();
	SetUncolored();
}

// Set pixel as grey variant of input RGB pixel
// @input:
// - t_color - color from RGB space
// @output:
void TargetPixel::SetAsGrey(const RGB &t_color)
{
	ToGrey(t_color);
}

// Set current pixel as grey
// @input:
// @output:
void TargetPixel::SetAsGrey()
{
	RGB currColor = GetRGB();
	ToGrey(currColor);
}

// Transform pixel to grey color
// @input:
// - t_color - valid RGB color
// @output:
void TargetPixel::ToGrey(const RGB &t_color)
{
	bool pixelIsGrey = t_color.IsGreyColor();
	if ( true == pixelIsGrey )
	{
		SetRGB(t_color);
	}
	else
	{
		RGB greyColor = t_color;
		greyColor.ToGrey();

		SetRGB(greyColor);
	}
}

// Scale relative luminance with some factor
// @input:
// - t_factor - positive scale factor
// @output:
// - true - luminance scaled
// - false - can't scale luminance with that factor
bool TargetPixel::ScaleRelLum(const double &t_factor)
{
	if ( t_factor <= 0.0 )
	{
		return false;
	}

	// Protection from scaling luminance twice
	RestoreRelLum();

	const double relativeLum = GetRelativeLum();
	double scaledLum = relativeLum * t_factor;
	if ( RELATIVE_MAX < scaledLum )
	{
		scaledLum = RELATIVE_MAX;
	}

	return SetRelativeLum(scaledLum);
}

// Restore relative luminance value
// @input:
// @output:
void TargetPixel::RestoreRelLum()
{
	CalcRelativeLum();
}

// Set normalised relative luminance
// @input:
// - t_newLum - value of relative LAB luminance
// @output:
// - true - normalized relative luminance set
// - false - can't set relative luminance
bool TargetPixel::SetNormalizedRelLum(const double &t_newLum)
{
	if ( t_newLum < 0.0 )
	{
		return false;
	}

	return SetRelativeLum(t_newLum);
}

// Set prefered color for pixel
// @input:
// - t_prefColor - prefered color for this pixel
// @output:
void TargetPixel::SetPreferedColor(const RGB &t_prefColor)
{
	m_prefColor.SetPreferedColor(t_prefColor);
}

// Check if pixel has prefered color
// @input:
// @output:
// - true - pixel has prefered color
// - false - pixel doesn't have prefered color
bool TargetPixel::HasPreferedColor() const
{
	return m_prefColor.HasColor();
}

// Get prefered color
// @input:
// @output:
// - RGB - pixels prefered color
RGB TargetPixel::GetPreferedColor() const
{
	return m_prefColor.GetPreferedColor();
}

// Set that pixel colorized (has color)
// @input:
// @output:
void TargetPixel::SetColored()
{
	m_colored = true;
}

// Set that pixel not colorized (has not color)
// @input:
// @output:
void TargetPixel::SetUncolored()
{
	m_colored = false;
}

// Check if pixel colorized
// @input:
// @output:
bool TargetPixel::IsColored() const
{
	return m_colored;
}
