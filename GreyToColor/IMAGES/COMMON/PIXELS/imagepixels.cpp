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

#include "imagepixels.h"

ImagePixels::ImagePixels(QObject *parent) :
	QObject(parent)
{
	Clear();
}

ImagePixels::~ImagePixels()
{
	Clear();
}


// Clear all info (set to defaults)
// @input:
// @output:
void ImagePixels::Clear()
{
	m_width = 0;
	m_height = 0;
}

// Check if we have pixel with such coords
// @input:
// - unsigned int - width (x) position of pixel
// - unsigned int - height (y) position of pixel
// @output:
// - true - pixels with such coords exist
// - false - pixel don't exist
bool ImagePixels::IsPixelExist(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( (m_width <= t_width) || (m_height <= t_height) )
	{
		return false;
	}

	return true;
}

// Check if we have pixels of image
// @input:
// @output:
// - true - yes, we have pixels
// - false - no, we don't have pixels
bool ImagePixels::HasPixels() const
{
	if ( (0 == m_width) || (0 == m_height) )
	{
		return false;
	}

	return true;
}

//void ImagePixels::CalcPixelsSKO()
//{
//	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
//	{
//		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
//		{
//			CalcPixSKO(wdt, hgt);
//		}
//	}
//}
