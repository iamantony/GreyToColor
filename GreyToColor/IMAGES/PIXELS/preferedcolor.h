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

#ifndef PREFEREDCOLOR_H
#define PREFEREDCOLOR_H

#include <QDebug>
#include "PIXEL/pixel.h"

class PreferedColor : public Pixel
{
	// == DATA ==
private:
	bool m_hasColor;

	// == METHODS ==
public:
	PreferedColor();
	~PreferedColor();

	// Check if we have prefered color for pixel
	bool HasColor() const;
	// Set prefered RGB color
	void SetPreferedColor(const RGB &t_color);
	// Get prefered color
	RGB GetPreferedColor() const;
	// Clear prefered color
	void ClearColor();
};

#endif // PREFEREDCOLOR_H
