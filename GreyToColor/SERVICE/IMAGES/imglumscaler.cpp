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

#include "imglumscaler.h"

ImgLumScaler::ImgLumScaler()
{

}

// Scale target image LAB luminance by some equalisation rule
// @input:
// -LumEqualization::Type - exist type of luminance equalization
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - LAB Luminance of target image scaled
// - false - can't scale LAB Luminance of Target Image
bool ImgLumScaler::ScaleTargetImgLum(const LumEqualization::Type &t_type,
									 TargetImage *t_target,
									 SourceImage *t_source)
{
	if ( (NULL == t_target) ||
		 (NULL == t_source) ||
		 (false == t_target->HasImage()) ||
		 (false == t_source->HasImage()) )
	{
		qDebug() << "ScaleTargetImgLum(): Error - invalid arguments";
		return false;
	}

	bool targImgLumScaled = false;
	switch(t_type)
	{
		case LumEqualization::SCALE_BY_MAX:
			targImgLumScaled = ScaleTargetImgLumByMax(t_target, t_source);
			break;

		case LumEqualization::SCALE_BY_AVERAGE:
			targImgLumScaled = ScaleTargetImgLumByAverage(t_target, t_source);
			break;

		case LumEqualization::NORMALIZE_LUM_BORDER:
			targImgLumScaled = NormalizeTargetImgByBorder(t_target, t_source);
			break;

		case LumEqualization::NORMALIZE_LUM_CENTER:
			targImgLumScaled = NormalizeTargetImgByCenter(t_target, t_source);
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
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - LAB Luminance of target image scaled
// - false - can't scale LAB Luminance of Target Image
bool ImgLumScaler::ScaleTargetImgLumByMax(TargetImage *t_target, SourceImage *t_source)
{
	if ( (NULL == t_target) ||
		 (NULL == t_source) ||
		 (false == t_target->HasImage()) ||
		 (false == t_source->HasImage()))
	{
		qDebug() << "ScaleTargetImgLumByMax(): Error - invalid arguments";
		return false;
	}

	const double targMaxLum = t_target->GetMaxLABLum();
	const double sourceMaxLum = t_source->GetMaxLABLum();
	const double scaleFactor = sourceMaxLum / targMaxLum;
	bool lumScaled = t_target->ScaleLABLum(scaleFactor);
	if ( false == lumScaled )
	{
		qDebug() << "ScaleTargetImgLumByMax(): Error - can't scale luminance of Target image";
		return false;
	}

	return true;
}

// Scale Target Image pixels luminances by Average luminance value of Source Image
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - LAB Luminance of target image scaled
// - false - can't scale LAB Luminance of Target Image
bool ImgLumScaler::ScaleTargetImgLumByAverage(TargetImage *t_target, SourceImage *t_source)
{
	if ( (NULL == t_target) ||
		 (NULL == t_source) ||
		 (false == t_target->HasImage()) ||
		 (false == t_source->HasImage()))
	{
		qDebug() << "ScaleTargetImgLumByAverage(): Error - invalid arguments";
		return false;
	}

	const double targAverLum = t_target->GetAverageLABLum();
	const double sourceAverLum = t_source->GetAverageLABLum();
	const double scaleFactor = sourceAverLum / targAverLum;
	bool lumScaled = t_target->ScaleLABLum(scaleFactor);
	if ( false == lumScaled )
	{
		qDebug() << "ScaleTargetImgLumByAverage(): Error - can't scale luminance of Target image";
		return false;
	}

	return true;
}

// Normalize Target Image pixels luminances using min/max luminances of Source Image
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - LAB Luminance of target image normalised
// - false - can't normalise LAB Luminance of Target Image
bool ImgLumScaler::NormalizeTargetImgByBorder(TargetImage *t_target, SourceImage *t_source)
{
	if ( (NULL == t_target) ||
		 (NULL == t_source) ||
		 (false == t_target->HasImage()) ||
		 (false == t_source->HasImage()))
	{
		qDebug() << "NormalizeTargetImgByBorder(): Error - invalid arguments";
		return false;
	}

	const double sourceMinLum = t_source->GetMinLABLum();
	const double sourceMaxLum = t_source->GetMaxLABLum();
	bool lumNormalised = t_target->NormaliseLABLumByBorders(sourceMinLum, sourceMaxLum);
	if ( false == lumNormalised )
	{
		qDebug() << "NormalizeTargetImgByBorder(): Error - can't normalise luminance of Target image";
		return false;
	}

	return true;
}

// Normalize Target Image pixels luminance using min, max and central luminances of Source Imge
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - LAB Luminance of target image normalised
// - false - can't normalise LAB Luminance of Target Image
bool ImgLumScaler::NormalizeTargetImgByCenter(TargetImage *t_target, SourceImage *t_source)
{
	if ( (NULL == t_target) ||
		 (NULL == t_source) ||
		 (false == t_target->HasImage()) ||
		 (false == t_source->HasImage()))
	{
		qDebug() << "NormalizeTargetImgByCenter(): Error - invalid arguments";
		return false;
	}

	const double sourceMinLum = t_source->GetMinLABLum();
	const double sourceMaxLum = t_source->GetMaxLABLum();
	const double sourceCommonLum = t_source->GetCommonLABLum();
	bool lumNormalised = t_target->NormaliseLABLumByCenter(sourceMinLum,
														   sourceCommonLum,
														   sourceMaxLum);
	if ( false == lumNormalised )
	{
		qDebug() << "NormalizeTargetImgByCenter(): Error - can't normalise luminance of Target image";
		return false;
	}

	return true;
}
