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

	m_originalLum = ERROR;
	SetUncolored();
}

// Set pixel as grey variant of input RGB pixel
// @input:
// - RGB - color from RGB space
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
// - RGB - unnull color
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
		int red = t_color.GetRed();
		int green = t_color.GetGreen();
		int blue = t_color.GetBlue();

		RGB greyColor(red, green, blue);
		greyColor.ToGrey();

		SetRGB(greyColor);
	}

}

// Scale luminance with some factor
// @input:
// - double - positive scale factor
// @output:
// - true - luminance scaled
// - false - can't scale luminance with that factor
bool TargetPixel::ScaleLum(const double &t_factor)
{
	if ( t_factor <= 0 )
	{
		return false;
	}

	// We don't want to scale luminance of pixel twice
	RestoreLum();

	double scaledLum = m_originalLum * t_factor;
	if ( LAB_MAX_LUM < scaledLum )
	{
		scaledLum = LAB_MAX_LUM;
	}
	else if ( scaledLum < 0 )
	{
		scaledLum = 0;
	}

	bool lumSet = SetChL(scaledLum);
	if ( false == lumSet )
	{
		return false;
	}

	return true;
}

// Set normalised luminance
// @input:
// - double - positive value of LAB luminance
// @output:
// - true - luminance restored
// - false - can't restore luminance
bool TargetPixel::SetNormalizedLum(const double &t_newLum)
{
	if ( t_newLum < 0 )
	{
		return false;
	}

	// If pixel was not previously set or scaled or normalised, we need to save pixels orignal lumiance value
	if ( m_originalLum < 0 )
	{
		m_originalLum = GetChL();
	}

	bool lumSet = SetChL(t_newLum);
	if ( false == lumSet )
	{
		return false;
	}

	return true;
}

// Restore original luminance
// @input:
// @output:
// - true - luminance restored
// - false - can't restore luminance
bool TargetPixel::RestoreLum()
{
	// If pixel was not previously set or scaled or normalised, we need to save pixels orignal lumiance value
	if ( m_originalLum < 0 )
	{
		m_originalLum = GetChL();
		return true;
	}

	bool lumSet = SetChL(m_originalLum);
	if ( false == lumSet )
	{
		return false;
	}

	return true;
}

// Set prefered color for pixel
// @input:
// - RGB - prefered color for this pixel
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

// TODO:
// how we would know what prefered color have pixel?

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

// Save current LAB luminance as original
// @input:
// @output:
void TargetPixel::SaveOriginalLum()
{
	m_originalLum = GetChL();
}

// Test function SetAsGrey()
void TargetPixel::TestSetAsGrey()
{
	// http://en.wikipedia.org/wiki/Grayscales
	// Random color
	const int red = 50;
	const int green = 128;
	const int blue = 203;
	const double calcs = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
	const int grey = (int)floor(calcs + 0.5);

	qDebug() << endl << "TestSetAsGrey(): random RGB color";
	qDebug() << "RGB:" << red << green << blue;
	qDebug() << "Grey:" << grey;

	RGB color(red, green, blue);
	SetAsGrey(color);

	RGB greyResult1 = GetRGB();
	qDebug() << "Result:" << greyResult1.GetRed() << greyResult1.GetGreen() << greyResult1.GetBlue();

	// Grey color
	const int greyChannel = 50;

	qDebug() << endl << "TestSetAsGrey(): grey RGB color";
	qDebug() << "Grey RGB:" << greyChannel;

	RGB greyColor(greyChannel, greyChannel, greyChannel);
	SetAsGrey(greyColor);

	RGB greyResult2 = GetRGB();
	qDebug() << "Result:" << greyResult2.GetRed() << greyResult2.GetGreen() << greyResult2.GetBlue();
}

// Test function for scaling and unscaling luminance
void TargetPixel::TestScaleLum()
{
	const int red = 50;
	const int green = 128;
	const int blue = 203;

	qDebug() << endl << "TestScaleLum()";
	qDebug() << "RGB:" << red << green << blue;

	RGB color(red, green, blue);
	SetRGB(color);

	TransformRGB2LAB();

	ScaleLum(1.243);
	RestoreLum();

	TransformLAB2RGB();

	RGB resultColor = GetRGB();
	qDebug() << "Result:" << resultColor.GetRed() << resultColor.GetGreen() << resultColor.GetBlue();
}
