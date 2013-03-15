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

#include "imgsimilarityarea.h"

ImgSimilarityArea::ImgSimilarityArea()
{
	Clear();
}

ImgSimilarityArea::~ImgSimilarityArea()
{
	Clear();
}

// Clear info
// @input:
// @output:
void ImgSimilarityArea::Clear()
{
	m_id = 0;

	m_area.setX(0);
	m_area.setY(0);
	m_area.setWidth(0);
	m_area.setHeight(0);
}

// Setup image area parameters
// @input:
// - unsigned int - ID of the area
// - QRect - unempty, valid image area position and size (rectangular)
// @output:
// - true - area set
// - false - can't set area with such parameters
bool ImgSimilarityArea::SetArea(const unsigned int &t_id, const QRect &t_area)
{
	if ( (true == t_area.isEmpty()) || (false == t_area.isValid()) )
	{
		qDebug() << "SetArea(): Error - invalid arguments";
		return false;
	}

	m_id = t_id;
	m_area = t_area;

	return true;
}

// Get image area ID
// @input:
// @output:
// - unsigned int - ID of area
unsigned int ImgSimilarityArea::GetAreaID() const
{
	return m_id;
}

// Get image area size and position
// @input:
// @output:
// - QRect - image area position and size (rectangular) (could be invalid, empty)
QRect ImgSimilarityArea::GetAreaRect() const
{
	return m_area;
}

// Check if image area has valid params
// @input:
// @output:
// - true - area is valid
// - false - area is invalid. You should not use it
bool ImgSimilarityArea::IsValid() const
{
	if ( (true == m_area.isEmpty()) || (false == m_area.isValid()) )
	{
		return false;
	}

	return true;
}
