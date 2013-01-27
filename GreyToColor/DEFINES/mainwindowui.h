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

#ifndef MAINWINDOWUI_H
#define MAINWINDOWUI_H

#define DEFAULT_TARGET_IMG_PATH "./UI/target_image.png"
#define DEFAULT_RESULT_IMG_PATH "./UI/result_image.png"
#define DEFAULT_SOURCE_IMG_PATH "./UI/source_image.png"

namespace Images
{
	enum Types
	{
		TARGET = 0,
		RESULT,
		SOURCE,
		DEFAULT_LAST
	};
}

#endif // MAINWINDOWUI_H
