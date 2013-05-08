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
	this->ClearColor();

	m_prefColor.ClearColor();

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

// Scale relative luminance with some factor
// @input:
// - double - positive scale factor
// @output:
// - true - luminance scaled
// - false - can't scale luminance with that factor
bool TargetPixel::ScaleRelLum(const double &t_factor)
{
	if ( t_factor <= 0 )
	{
		return false;
	}

	// We don't want to scale luminance of pixel twice
	RestoreRelLum();

	const double relativeLum = GetRelativeLum();
	double scaledLum = relativeLum * t_factor;
	if ( RELATIVE_MAX < scaledLum )
	{
		scaledLum = RELATIVE_MAX;
	}

	bool isLumSet = SetRelativeLum(scaledLum);

	return isLumSet;
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
// - double - value of relative LAB luminance
// @output:
// - true - normalized relative luminance set
// - false - can't set relative luminance
bool TargetPixel::SetNormalizedRelLum(const double &t_newLum)
{
	if ( t_newLum < 0 )
	{
		return false;
	}

	bool isLumSet = SetRelativeLum(t_newLum);

	return isLumSet;
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

// Get prefered color
// @input:
// @output:
// - RGB - pixels prefered color
RGB TargetPixel::GetPreferedColor()
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
	CalcRelativeLum();

	qDebug() << "Relative luminance =" << GetRelativeLum();

	const double scaleFactor = 1.243;
	qDebug() << "Scale Factor =" << scaleFactor;

	ScaleRelLum(scaleFactor);

	qDebug() << "Relative luminance after scale =" << GetRelativeLum();

	RestoreRelLum();

	qDebug() << "Relative luminance after restore =" << GetRelativeLum();
}
