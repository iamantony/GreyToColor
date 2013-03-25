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

#include "colorizator.h"

Colorizator::Colorizator()
{
	Clear();
}

Colorizator::~Colorizator()
{
	Clear();
}

// Clear all info
// @input:
// @output:
void Colorizator::Clear()
{
	m_target = NULL;
	m_source = NULL;
}

// Scale Target Image luminance
// @input:
// - LumEqualization::Type - exist Luminance Equalization type
// @output:
// - true -
bool Colorizator::EquliseTargetImgLum(const LumEqualization::Type &t_type)
{
	ImgLumScaler scaler;
	bool targImgLumScaled = scaler.ScaleTargetImgLum(t_type,
													 m_target,
													 m_source);

	return targImgLumScaled;
}
