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

#ifndef IDBFILESSERVICE_H
#define IDBFILESSERVICE_H

#include "filesservice.h"

class IDBFilesService : public FilesService
{
	// == DATA ==

	// == METHODS ==
public:
	IDBFilesService();

	// Remove ImageDataBase
	bool RemoveIDB(const QString &t_idbPath);
	// Check if in input path exist IDB
	bool CheckIDBExist(const QString &t_idbPath);
	// Get full path for IDB name
	QString FormIDBFullPath (const QString &t_idbName);
};

#endif // IDBFILESSERVICE_H
