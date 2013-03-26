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

#ifndef IMGSERVICE_H
#define IMGSERVICE_H

#define NUM_OF_RGB_CHANN 3
#define MIN_RGB_LUM 0
#define MAX_RGB_LUM 255

#define NUM_RGB_VALUES 256

namespace Histogram
{
	enum Type
	{
		RED = 0,
		GREEN,
		BLUE,
		DEFAULT_LAST
	};
}

namespace Kernel
{
	enum Type
	{
		SOBEL = 0,
		DEFAULT_LAST
	};
}

namespace LumEqualization
{
	enum Type
	{
		NO_SCALE = 0,
		SCALE_BY_MAX,
		SCALE_BY_AVERAGE,
		NORMALIZE_LUM_BORDER,
		NORMALIZE_LUM_CENTER,
		DEFAULT_LAST
	};
}

#endif // IMGSERVICE_H
