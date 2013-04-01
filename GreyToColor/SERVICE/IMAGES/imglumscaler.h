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

#ifndef IMGLUMSCALER_H
#define IMGLUMSCALER_H

#include <QDebug>
#include "IMAGES/TARGET/targetimage.h"
#include "IMAGES/SOURCE/sourceimage.h"
#include "./DEFINES/imgservice.h"

class ImgLumScaler
{
	// == DATA ==

	// == METHODS ==
public:
	ImgLumScaler();

	// Scale target image LAB luminance by some equalisation rule
	bool ScaleTargetImgLum(const LumEqualization::Type &t_type,
						   TargetImage *t_target,
						   SourceImage *t_source);

private:
	// Restore Target image default LAB Luminance
	bool RestoreTargImgLum(TargetImage *t_target);
	// Scale Target Image pixels luminances by Max luminance value of Source Image
	bool ScaleTargetImgLumByMax(TargetImage *t_target, SourceImage *t_source);
	// Scale Target Image pixels luminances by Average luminance value of Source Image
	bool ScaleTargetImgLumByAverage(TargetImage *t_target, SourceImage *t_source);
	// Normalize Target Image pixels luminances using min/max luminances of Source Image
	bool NormalizeTargetImgByBorder(TargetImage *t_target, SourceImage *t_source);
	// Normalize Target Image pixels luminance using min, max and central luminances of Source Imge
	bool NormalizeTargetImgByCenter(TargetImage *t_target, SourceImage *t_source);
};

#endif // IMGLUMSCALER_H
