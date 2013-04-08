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

#include "colorpixel.h"

ColorPixel::ColorPixel()
{
	m_sko = 0;
}

ColorPixel::~ColorPixel()
{
	m_sko = 0;
}

// Set SKO for pixel of image
// @input:
// - double - positive SKO value
// @output:
bool ColorPixel::SetSKO(const double &t_sko)
{
	if ( t_sko < 0 )
	{
		qDebug() << "SetSKO(): Error - invalid arguments:" << t_sko;
		return false;
	}

	m_sko = t_sko;

	return true;
}

// Set SKO for pixel of image
// @input:
// @output:
// - double - positive SKO of this pixel
double ColorPixel::GetSKO() const
{
	return m_sko;
}

// Set entropy for pixel of image
// @input:
// - double - entropy value
// @output:
void ColorPixel::SetEntropy(const double &t_entropy)
{
	m_entropy = t_entropy;
}

// Set entropy for pixel of image
// @input:
// @output:
// - double - entropy value of this pixel
double ColorPixel::GetEntropy() const
{
	return m_entropy;
}

// Clear color pixel
// @input:
// @output:
void ColorPixel::ClearColor()
{
	this->Clear();
	m_sko = 0;
}
