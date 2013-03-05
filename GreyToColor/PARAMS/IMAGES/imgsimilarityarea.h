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

#ifndef IMGSIMILARITYAREA_H
#define IMGSIMILARITYAREA_H

#include <QRect>
#include <QDebug>
#include "./DEFINES/global.h"

class ImgSimilarityArea
{
	// == DATA ==
private:
	unsigned int m_id;
	QRect m_area;

	// == METHODS ==
public:
	ImgSimilarityArea();
	~ImgSimilarityArea();

	// Clear info
	void Clear();
	// Setup image area parameters
	bool SetArea(const unsigned int &t_id, const QRect &t_area);
	// Get image area ID
	unsigned int GetAreaID() const;
	// Get image area size and position
	QRect GetAreaRect() const;
	// Check if image area has valid params
	bool IsValid() const;
};

#endif // IMGSIMILARITYAREA_H
