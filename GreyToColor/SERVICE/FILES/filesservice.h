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

#ifndef FILESSERVICE_H
#define FILESSERVICE_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>

class FilesService
{
	// == DATA ==

	// == METHODS ==
public:
	FilesService();

	// Remove file
	bool RemoveFile(const QString &t_filePath);
	// Check if file exist
	bool CheckFileExistance(const QString &t_filePath);
	// Form for file it's full path
	QString FormFullPath(const QString &t_fileName);
	// Get file name from it's full path
	QString GetFileName(const QString &t_filePath);
};

#endif // FILESSERVICE_H
