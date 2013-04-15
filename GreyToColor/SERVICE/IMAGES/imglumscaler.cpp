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
		case LumEqualization::NO_SCALE:
			targImgLumScaled = RestoreTargImgLum(t_target);
			break;

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

// Restore Target image default LAB Luminance
// @input:
// - TargetImage - unnull, unempty Target Image
// @output:
// - true - LAB Luminance of target image restored
// - false - can't restore LAB Luminance of Target Image
bool ImgLumScaler::RestoreTargImgLum(TargetImage *t_target)
{
	if ( (NULL == t_target) || (false == t_target->HasImage()) )
	{
		qDebug() << "RestoreTargImgLum(): Error - invalid arguments";
		return false;
	}

	t_target->RestoreLABRelLum();
	return true;
}

// Scale Target Image pixels relative luminances by Max relative luminance value of Source Image
// @input:
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - relative luminance of target image scaled
// - false - can't scale relative luminance of Target Image
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

	const double targMaxRelLum = t_target->GetMaxRelLum();
	const double sourceMaxRelLum = t_source->GetMaxRelLum();
	const double scaleFactor = sourceMaxRelLum / targMaxRelLum;
	bool lumScaled = t_target->ScaleLABRelLum(scaleFactor);
	if ( false == lumScaled )
	{
		qDebug() << "ScaleTargetImgLumByMax(): Error - can't scale relative luminance of Target image";
		return false;
	}

	return true;
}

// Scale Target Image pixels relative luminances by Average relative luminance value of Source Image
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - relative luminance of target image scaled
// - false - can't scale relative luminance of Target Image
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

	const double targAverLum = t_target->GetAverageRelLum();
	const double sourceAverLum = t_source->GetAverageRelLum();
	const double scaleFactor = sourceAverLum / targAverLum;
	bool lumScaled = t_target->ScaleLABRelLum(scaleFactor);
	if ( false == lumScaled )
	{
		qDebug() << "ScaleTargetImgLumByAverage(): Error - can't scale relative luminance of Target image";
		return false;
	}

	return true;
}

// Normalize Target Image pixels relative luminances using min/max relative luminances of Source Image
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - relative luminance of target image normalized
// - false - can't normalize relative luminance of Target Image
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

	const double sourceMinLum = t_source->GetMinRelLum();
	const double sourceMaxLum = t_source->GetMaxRelLum();
	bool lumNormalised = t_target->NormaliseLABRelLumByBorders(sourceMinLum, sourceMaxLum);
	if ( false == lumNormalised )
	{
		qDebug() << "NormalizeTargetImgByBorder(): Error - can't normalize relative luminance of Target image";
		return false;
	}

	return true;
}

// Normalize Target Image pixels reltive luminance using min, max and central relative luminances of Source Imge
// - TargetImage - unnull, unempty Target Image
// - SourceImage - unnull, unempty Source Image
// @output:
// - true - relative luminance of target image normalized
// - false - can't normalize relative luminance of Target Image
bool ImgLumScaler::NormalizeTargetImgByCenter(TargetImage *t_target, SourceImage *t_source)
{
	if ( (NULL == t_target) ||
		 (NULL == t_source) ||
		 (false == t_target->HasImage()) ||
		 (false == t_source->HasImage()) )
	{
		qDebug() << "NormalizeTargetImgByCenter(): Error - invalid arguments";
		return false;
	}

	const double sourceMinLum = t_source->GetMinRelLum();
	const double sourceMaxLum = t_source->GetMaxRelLum();
	const double sourceCommonLum = t_source->GetMostCommonRelLum();
	bool lumNormalised = t_target->NormaliseLABRelLumByCenter(sourceMinLum,
															  sourceCommonLum,
															  sourceMaxLum);

	if ( false == lumNormalised )
	{
		qDebug() << "NormalizeTargetImgByCenter(): Error - can't normalize relative luminance of Target image";
		return false;
	}

	return true;
}
