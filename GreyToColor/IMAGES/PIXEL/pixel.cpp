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
	m_pixel.SetColor(0, 0, 0);
	m_chL = 0;
	m_chA = 0;
	m_chB = 0;
}

Pixel::~Pixel()
{
	m_pixel.SetColor(0, 0, 0);
	m_chL = 0;
	m_chA = 0;
	m_chB = 0;
}

// Set RGB color for pixel
// @input:
// - t_rgbColor - exist color in RGB color space
// @output:
void Pixel::SetRGB(const RGB &t_rgbColor)
{
	m_pixel = t_rgbColor;
	qDebug() << "Color:" << m_pixel.GetRed() << m_pixel.GetGreen() << m_pixel.GetBlue();

	bool result = m_pixel.SetColor(-10, 255, 256);
	qDebug() << "Color:" << m_pixel.GetRed() << m_pixel.GetGreen() << m_pixel.GetBlue();
	qDebug() << result;
}
