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

#include "filesservice.h"

FilesService::FilesService()
{
}

// Remove file
// @input:
// - QString - unempty string with full file path
// @output:
// - true - file deleted
// - false - can't delete file
bool FilesService::RemoveFile(const QString &t_filePath)
{
	if ( true == t_filePath.isEmpty() )
	{
		qDebug() << "RemoveFile(): Error - invalid arguments";
		return false;
	}

	bool fileExist = CheckFileExistance(t_filePath);
	if ( false == fileExist )
	{
		return true;
	}

	bool fileRemoved = QFile::remove(t_filePath);
	if ( false == fileRemoved )
	{
		qDebug() << "RemoveFile(): Error - can't remove file" << t_filePath;
		return false;
	}

	return true;
}

// Check if file exist
// @input:
// - QString - unempty string with full file path
// @output:
// - true - file exist
// - false - can't check file existance or file don't exist
bool FilesService::CheckFileExistance(const QString &t_filePath)
{
	if ( true == t_filePath.isEmpty() )
	{
		qDebug() << "CheckFileExistance(): Error - invalid arguments";
		return false;
	}

	bool fileExist = QFile::exists(t_filePath);
	return fileExist;
}

// TODO:
// - do we really need this function - FormFullPath()? If yes, we should defenately make it better

// Form for file it's full path
// @input:
// - QString - unempty file name, which is located in project path. In string there must be not only file name,
// but relative path to that file
// @output:
// - empty QString - can't form full path for this file
// - QString - full path for input file
QString FilesService::FormFullPath(const QString &t_fileName)
{
	if ( true == t_fileName.isEmpty() )
	{
		qDebug() << "FormFullPath(): Error - invalid arguments";
		QString empty;
		return empty;
	}

	QString fullName;
	QDir dir;
	fullName.append(dir.absolutePath());
	fullName.append(t_fileName);
	fullName = dir.toNativeSeparators(fullName);

	bool fileExist = QFile::exists(fullName);
	if ( false == fileExist )
	{
		qDebug() << "FormFullPath(): Error - can't form full path for file" << t_fileName;
		QString empty;
		return empty;
	}

	return fullName;
}

// Get file name from it's full path
// @input:
// - QString - unempty full file path
// @output:
// - empty QString - can't get file name
// - QString - file name with suffix
QString FilesService::GetFileName(const QString &t_filePath)
{
	if ( true == t_filePath.isEmpty() )
	{
		qDebug() << "GetFileName(): Error - invalid arguments";
		QString empty;
		return empty;
	}

	QString fileName;
	QFileInfo fileInfo(t_filePath);
	fileName = fileInfo.baseName() + "." + fileInfo.completeSuffix();

	return fileName;
}
