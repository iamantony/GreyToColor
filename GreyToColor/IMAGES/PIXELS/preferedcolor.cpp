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

#include "preferedcolor.h"

PreferedColor::PreferedColor()
{
	m_hasColor = false;
}

PreferedColor::~PreferedColor()
{
	m_hasColor = false;
}


// Check if we have prefered color for pixel
// @input:
// @output:
// - true - pixel has preferd color
// - false - no prefered color
bool PreferedColor::HasColor() const
{
	return m_hasColor;
}

// Set prefered RGB color
// @input:
// - t_color - RGB color
// @output:
void PreferedColor::SetPreferedColor(const RGB &t_color)
{
	this->SetRGB(t_color);
	m_hasColor = true;
}

// Get prefered color
// @input:
// @output:
// - RGB - pixels prefered color
RGB PreferedColor::GetPreferedColor() const
{
	return this->GetRGB();
}

// Clear prefered color
// @input:
// @output:
void PreferedColor::ClearColor()
{
	this->Clear();
	m_hasColor = false;
}
