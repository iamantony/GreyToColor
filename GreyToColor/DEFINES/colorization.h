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

#ifndef COLORIZATION_H
#define COLORIZATION_H

namespace Methods
{
	enum Type
	{
		WALSH_SIMPLE = 0,
		WALSH_NEIGHBOR,
		WALSH_NEIGHBOR_NORAND,
		WALSH_NEIGHBOR_ONERAND,
		DEFAULT_LAST
	};
}

namespace LumEqualization
{
	enum Type
	{
		SCALE_BY_MAX = 0,
		SCALE_BY_AVERAGE,
		NORMALIZE_LUM,
		DEFAULT_LAST
	};
}

#define DEFAULT_LUM 999999
#define DEFAULT_SKO 999999
#define LUM_TRESHOLD 0.001
#define SKO_TRESHOLD 0.001

#define NUM_OF_ATTEMPTS 200

#endif // COLORIZATION_H
