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

#ifndef IMGSEARCHPARAM_H
#define IMGSEARCHPARAM_H

#include <QImage>
#include <QPair>
#include <QDebug>
#include "./IMAGES/COMMON/image.h"
#include "imgtransform.h"
#include "./DEFINES/global.h"
#include "./DEFINES/pixels.h"

class ImgSearchParam
{
	// == DATA ==

	// == METHODS ==
public:
	ImgSearchParam();

	// Find min RGB luminance in image
	int FindMinLum(const Image &t_img);
	// Find max RGB luminance in image
	int FindMaxLum(const Image &t_img);
	// Find min and max RGB luminances in image
	QPair<int, int> FindMinMaxLum(const Image &t_img);
};

#endif // IMGSEARCHPARAM_H
