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

#include "idbfilesservice.h"

IDBFilesService::IDBFilesService()
{
}

// Remove ImageDataBase
// @input:
// - QString - unempty full path to IDB
// @output:
// - true - IDB deleted
// - false - can't delete IDB
bool IDBFilesService::RemoveIDB(const QString &t_idbPath)
{
	return RemoveFile(t_idbPath);
}

// Check if in input path exist IDB
// @input:
// - QString - unempty full path to IDB
// @output:
// - true - IDB exist
// - false - IDB not exist on input path
bool IDBFilesService::CheckIDBExist(const QString &t_idbPath)
{
	return CheckFileExistance(t_idbPath);
}

// Get full path for IDB name
// @input:
// - QString - unempty name of IDB, which is located in project path. In string there must be not only file name,
// but relative path to that file
// @output:
// - empty QString - can't form full path for IDB
// - QString - full path for IDB
QString IDBFilesService::FormIDBFullPath (const QString &t_idbName)
{
	return FormFullPath(t_idbName);
}
