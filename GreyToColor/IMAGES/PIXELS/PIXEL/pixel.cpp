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

#include "pixel.h"

Pixel::Pixel(QObject *parent) :
	QObject(parent)
{
	Clear();
}

Pixel::~Pixel()
{
	Clear();
}

// Set RGB color for as black pixel
// @input:
// @output:
void Pixel::Clear()
{
	m_pixelInRGB.SetColor(0,
						  0,
						  0);

	m_pixelInLAB.SetColor(0,
						  0,
						  0);
}

// Set RGB color for pixel
// @input:
// - RGB - exist color in RGB color space
// @output:
void Pixel::SetRGB(const RGB &t_rgbColor)
{
	m_pixelInRGB = t_rgbColor;
}

// Get color of pixel in RGB color space
// @input:
// @output:
// - RGB - current pixel in RGB
RGB Pixel::GetRGB() const
{
	return m_pixelInRGB;
}

// Check if current RGB color is a grey color
// @input:
// @output:
// - true - pixel is grey (all RGB channels have same value)
// - false - pixel is not monochrome (grey)
bool Pixel::IsGrey() const
{
	return m_pixelInRGB.IsGreyColor();
}

// Setup new luminance value for pixel
// @input:
// - double - positive new luminance value
// @output:
// - true - value set
// - false - impossible value
bool Pixel::SetChL(const double &t_lum)
{
	bool lumSet = m_pixelInLAB.SetChL(t_lum);
	if ( false == lumSet )
	{
		return false;
	}

	return true;
}

// Setup new value of channel A for pixel
// @input:
// - double - new channel A value
// @output:
void Pixel::SetChA(const double &t_a)
{
	m_pixelInLAB.SetChA(t_a);
}

// Setup new value of channel B for pixel
// @input:
// - double - new channel B value
// @output:
void Pixel::SetChB(const double &t_b)
{
	m_pixelInLAB.SetChB(t_b);
}

// Return Luminance channel value
// @input:
// @output:
// - double - value >= 0 of Luminance channel
double Pixel::GetChL() const
{
	return m_pixelInLAB.GetChL();
}

// Return A-channel value
// @input:
// @output:
// - double - value of A channel
double Pixel::GetChA() const
{
	return m_pixelInLAB.GetChA();
}

// Return B-channel value
// @input:
// @output:
// - double - value of B channel
double Pixel::GetChB() const
{
	return m_pixelInLAB.GetChB();
}

// Transform current pixels RGB coords to LAB coords
// @input:
// @output:
void Pixel::TransformRGB2LAB()
{
	RGBLAB transformer;
	m_pixelInLAB = transformer.RGB2LAB(m_pixelInRGB);
}

// Transform current pixels LAB coords to RGB coords
// @input:
// @output:
void Pixel::TransformLAB2RGB()
{
	RGBLAB transformer;
	m_pixelInRGB = transformer.LAB2RGB(m_pixelInLAB);
}
