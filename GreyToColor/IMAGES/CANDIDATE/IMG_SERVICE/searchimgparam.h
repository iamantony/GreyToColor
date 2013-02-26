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

#ifndef SEARCHIMGPARAM_H
#define SEARCHIMGPARAM_H

#include <QImage>
#include <QDebug>
#include "../../COMMON/PIXELS/rgb.h"
#include "./DEFINES/global.h"

class SearchImgParam
{
	// == DATA ==

	// == METHODS ==
public:
	SearchImgParam();

	int FindMaxLum(const QImage &t_img);
	int FindMinLum(const QImage &t_img);

private:
	int ColorImgMaxLum(const QImage &t_img);
	int ColorImgMinLum(const QImage &t_img);
	int GreyImgMaxLum(const QImage &t_img);
	int GreyImgMinLum(const QImage &t_img);
};

#endif // SEARCHIMGPARAM_H
