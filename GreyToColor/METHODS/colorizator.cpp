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
	switch(t_type)
	{
		case LumEqualization::SCALE_BY_MAX:
			targImgLumScaled = ScaleTargetImgLumByMax();
			break;

		case LumEqualization::SCALE_BY_AVERAGE:
			targImgLumScaled = ScaleTargetImgLumByAverage();
			break;

		case LumEqualization::NORMALIZE_LUM_BORDER:
			targImgLumScaled = NormalizeTargetImgByBorder();
			break;

		case LumEqualization::NORMALIZE_LUM_CENTER:
			targImgLumScaled = NormalizeTargetImgByCenter();
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

// Scale Target Image pixels luminances by Max luminance value of Source Image
// @input:
// @output:
bool Colorizator::ScaleTargetImgLumByMax()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) )
	{
		qDebug() << "ScaleTargetImgLumByMax(): Error - invalid arguments";
		return false;
	}

	const double targMaxLum = m_target->GetMaxLABLum();
	const double sourceMaxLum = m_source->GetMaxLABLum();
	const double scaleFactor = sourceMaxLum / targMaxLum;
	bool lumScaled = m_target->ScaleLABLum(scaleFactor);
	if ( false == lumScaled )
	{
		qDebug() << "ScaleTargetImgLumByMax(): Error - can't scale luminance of Target image";
		return false;
	}

	return true;
}

// Scale Target Image pixels luminances by Average luminance value of Source Image
// @input:
// @output:
bool Colorizator::ScaleTargetImgLumByAverage()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) )
	{
		qDebug() << "ScaleTargetImgLumByAverage(): Error - invalid arguments";
		return false;
	}

	const double targAverLum = m_target->GetAverageLABLum();
	const double sourceAverLum = m_source->GetAverageLABLum();
	const double scaleFactor = sourceAverLum / targAverLum;
	bool lumScaled = m_target->ScaleLABLum(scaleFactor);
	if ( false == lumScaled )
	{
		qDebug() << "ScaleTargetImgLumByAverage(): Error - can't scale luminance of Target image";
		return false;
	}

	return true;
}

// Normalize Target Image pixels luminances using min/max luminances of Source Image
// @input:
// @output:
bool Colorizator::NormalizeTargetImgByBorder()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) )
	{
		qDebug() << "NormalizeTargetImg(): Error - invalid arguments";
		return false;
	}

	const double sourceMinLum = m_source->GetMinLABLum();
	const double sourceMaxLum = m_source->GetMaxLABLum();
	bool lumNormalised = m_target->NormaliseLABLumByBorders(sourceMinLum, sourceMaxLum);
	if ( false == lumNormalised )
	{
		qDebug() << "NormalizeTargetImg(): Error - can't normalise luminance of Target image";
		return false;
	}

	return true;
}

// Normalize Target Image pixels luminance using min, max and central luminances of Source Imge
// @input:
// @output:
bool Colorizator::NormalizeTargetImgByCenter()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) )
	{
		qDebug() << "NormalizeTargetImg(): Error - invalid arguments";
		return false;
	}

	const double sourceMinLum = m_source->GetMinLABLum();
	const double sourceMaxLum = m_source->GetMaxLABLum();
	const double sourceCommonLum = m_source->GetCommonLABLum();
	bool lumNormalised = m_target->NormaliseLABLumByCenter(sourceMinLum,
														   sourceCommonLum,
														   sourceMaxLum);
	if ( false == lumNormalised )
	{
		qDebug() << "NormalizeTargetImgByCenter(): Error - can't normalise luminance of Target image";
		return false;
	}

	return true;
}
