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

#ifndef RGBLAB_H
#define RGBLAB_H

#include <QDebug>
#include <math.h>
#include "../PIXELS/PIXEL/rgb.h"
#include "../PIXELS/PIXEL/lab.h"
#include "./DEFINES/global.h"

class RGBLAB
{
// METHODS
public:
	explicit RGBLAB();

	LAB RGB2LAB(const RGB &t_rgbColor);
	RGB LAB2RGB(const LAB &t_labColor);
};

#endif // RGBLAB_H
