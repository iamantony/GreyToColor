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

#ifndef IMAGES_H
#define IMAGES_H

#define PROJECT_IMG_PATH		"/img/"

#define PASSPORT_LENGTH 256
#define SAMPLES_ON_FACET 16

namespace ImageFormat
{
	enum FormatType
	{
		BMP = 0,
		PNG,
		TIFF,
		JPG,
		JPEG,
		DEFAULT_LAST
	};
}

namespace Passport
{
	enum Type
	{
		LUM_HISTOGRAM = 0,
		LUM_SUBSAMPLE,
		LUM_AND_GRAD,
		LUM_AND_GRAD_SUBSAMPLE,
		DEFAULT_LAST
	};
}

#endif // IMAGES_H
