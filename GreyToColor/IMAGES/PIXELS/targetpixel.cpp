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
	ClearPixel();
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
	// Clear pixels and SKO
	this->ClearColor();
	m_prefColor.ClearColor();

	m_lumScaleFactor = DEFAULT_SCALE_LUM_FACTOR;
}

// Set pixel as grey
// @input:
// - t_color - 0 or color from RGB space
// @output:
void TargetPixel::SetAsGrey(const RGB &t_color)
{
	if ( NULL == t_color )
	{
		qDebug() << "No color in arguments";
		RGB currColor = GetRGB();
		ToGrey(currColor);

		return;
	}

	ToGrey(t_color);
}

// Transform pixel to grey color
void TargetPixel::ToGrey(const RGB &t_color)
{
	bool pixelIsGrey = t_color.IsGreyColor();
	if ( true == pixelIsGrey )
	{
		SetRGB(t_color);
	}
	else
	{
		// TODO:
		// - take all channels from t_color
		// - transform them to RGB (see Wiki)
		// - set as current color
	}

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
	m_lumScaleFactor = DEFAULT_SCALE_LUM_FACTOR;
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
