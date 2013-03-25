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
bool Colorizator::ScaleTargetImgLum(const LumEqualization::Type &t_type)
{
	bool targImgLumScaled = false;
	ImgLumScaler scaler;
	switch(t_type)
	{
		case LumEqualization::SCALE_BY_MAX:
			targImgLumScaled = scaler.ScaleTargetImgLumByMax(m_target, m_source);
			break;

		case LumEqualization::SCALE_BY_AVERAGE:
			targImgLumScaled = scaler.ScaleTargetImgLumByAverage(m_target, m_source);
			break;

		case LumEqualization::NORMALIZE_LUM_BORDER:
			targImgLumScaled = scaler.NormalizeTargetImgByBorder(m_target, m_source);
			break;

		case LumEqualization::NORMALIZE_LUM_CENTER:
			targImgLumScaled = scaler.NormalizeTargetImgByCenter(m_target, m_source);
			break;

		case LumEqualization::DEFAULT_LAST:
		default:
		{
			qDebug() << "ScaleTargetImgLum(): Error - invalid arguments";
			return false;
		}
	}

	return targImgLumScaled;
}
