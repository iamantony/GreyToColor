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

#include <QDebug>
#include "pixel.h"

Pixel::Pixel()
{
	Clear();
}

Pixel::~Pixel()
{

}

// Set color of pixel as black pixel
// @input:
// @output:
void Pixel::Clear()
{
	m_pixelRGB.SetColor(0, 0, 0);
	m_pixelLAB.SetColor(0.0, 0.0, 0.0);
}

// Set RGB color for pixel
// @input:
// - t_rgbColor - existing color in RGB color space
// @output:
void Pixel::SetRGB(const RGB &t_rgbColor)
{
	m_pixelRGB = t_rgbColor;
}

// Get color of pixel in RGB color space
// @input:
// @output:
// - RGB - current pixel in RGB
RGB Pixel::GetRGB() const
{
	return m_pixelRGB;
}

// Check if current RGB color is a grey color
// @input:
// @output:
// - true - pixel is grey (all RGB channels have same value)
// - false - pixel is not monochrome (grey)
bool Pixel::IsGrey() const
{
	return m_pixelRGB.IsGreyColor();
}

// Setup new luminance value for pixel
// @input:
// - t_chLum - positive new luminance value
// @output:
// - true - value set
// - false - impossible value
bool Pixel::SetChL(const double &t_chLum)
{
	return m_pixelLAB.SetChL(t_chLum);
}

// Setup new value of channel A for pixel
// @input:
// - t_chA - new channel A value
// @output:
void Pixel::SetChA(const double &t_chA)
{
	m_pixelLAB.SetChA(t_chA);
}

// Setup new value of channel B for pixel
// @input:
// - t_chB - new channel B value
// @output:
void Pixel::SetChB(const double &t_chB)
{
	m_pixelLAB.SetChB(t_chB);
}

// Get Luminance channel value
// @input:
// @output:
// - double - value >= 0 of Luminance channel
double Pixel::GetChL() const
{
	return m_pixelLAB.GetChL();
}

// Get A-channel value
// @input:
// @output:
// - double - value of A channel
double Pixel::GetChA() const
{
	return m_pixelLAB.GetChA();
}

// Get B-channel value
// @input:
// @output:
// - double - value of B channel
double Pixel::GetChB() const
{
	return m_pixelLAB.GetChB();
}

// Transform current pixels RGB coords to LAB coords
// @input:
// @output:
void Pixel::TransformRGB2LAB()
{
	RGBLAB transformer;
	m_pixelLAB = transformer.RGB2LAB(m_pixelRGB);
}

// Transform current pixels LAB coords to RGB coords
// @input:
// @output:
void Pixel::TransformLAB2RGB()
{
	RGBLAB transformer;
	m_pixelRGB = transformer.LAB2RGB(m_pixelLAB);
}
