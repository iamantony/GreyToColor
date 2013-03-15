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

#ifndef PROGRAMSTATUS_H
#define PROGRAMSTATUS_H

namespace Program
{
	enum Status
	{
		OK = 0,
		LOAD_TARGET,
		LOAD_SOURCE,
		CALC_TARGET,
		CALC_SOURCE,
		COLORIZATION,
		SEARCHING_IMAGE_IN_DB,
		DB_FORMING,
		SAVING,
		ERR,
		DEFAULT_LAST
	};
}

Q_DECLARE_METATYPE(Program::Status);

#endif // PROGRAMSTATUS_H
