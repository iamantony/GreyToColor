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
#include "rgb.h"

RGB::RGB(const int &t_red,
		 const int &t_green,
		 const int &t_blue)
{
	SetColor(t_red,
			 t_green,
			 t_blue);
}

RGB::~RGB()
{
	m_red = 0;
	m_green = 0;
	m_blue = 0;
}

// Set RGB color
// @input:
// - t_red - value [0, 255] for red RGB channel
// - t_green - value [0, 255] for green RGB channel
// - t_blue - value [0, 255] for blue RGB channel
// @output:
// - true - color is set
// - false - not all of the input values are possible RGB color space
bool RGB::SetColor(const int &t_red,
				   const int &t_green,
				   const int &t_blue)
{
	bool result = true;

	bool redIsPossible = CheckChannelValue(t_red);
	if ( true == redIsPossible )
	{
		m_red = t_red;
	}
	else
	{
		m_red = 0;
		result = false;
	}

	bool greenIsPossible = CheckChannelValue(t_green);
	if ( true == greenIsPossible )
	{
		m_green = t_green;
	}
	else
	{
		m_green = 0;
		result = false;
	}

	bool blueIsPossible = CheckChannelValue(t_blue);
	if ( true == blueIsPossible )
	{
		m_blue = t_blue;
	}
	else
	{
		m_blue = 0;
		result = false;
	}

	return result;
}

// Check if value for one of the RGB channels is possible
// @input:
// - t_value - positive value [0, 255] for RGB channel
// @output:
// - true - value is possible
// - false - RGB channel can't have such value
bool RGB::CheckChannelValue(const int &t_value) const
{
	if ( (t_value < 0) || (255 < t_value) )
	{
		qDebug() << "CheckChannelValue(): Error - RGB color is impossible:" <<
					t_value;
		return false;
	}

	return true;
}

// Get red channel value
// @input:
// @output:
// - int - value [0, 255] of red RGB channel
int RGB::GetRed() const
{
	return m_red;
}

// Get green channel value
// @input:
// @output:
// - int - value [0, 255] of green RGB channel
int RGB::GetGreen() const
{
	return m_green;
}

// Get blue channel value
// @input:
// @output:
// - int - value [0, 255] of blue RGB channel
int RGB::GetBlue() const
{
	return m_blue;
}

// Check if color is grey
// @input:
// @output:
// - true - this is a grey color (all RGB channels have same value)
// - false - this is not a grey color
bool RGB::IsGreyColor() const
{
	if ( (m_red == m_green) && ( m_red == m_blue ) )
	{
		return true;
	}

	return false;
}

// Transform to grey color
// @input:
// @output:
void RGB::ToGrey()
{
	if ( true == IsGreyColor() )
	{
		return;
	}

	// http://en.wikipedia.org/wiki/Grayscale
	double greyLum = 0.2126 * m_red + 0.7152 * m_green + 0.0722 * m_blue;
	int grey = (int)floor(greyLum + 0.5);

	m_red = grey;
	m_green = grey;
	m_blue = grey;
}
