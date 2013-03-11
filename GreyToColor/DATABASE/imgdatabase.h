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

#ifndef IMGDATABASE_H
#define IMGDATABASE_H

#include <QString>
#include <QByteArray>
#include <QVariant>
#include <QImage>
#include <QDir>
#include <QFileInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include "SERVICE/FILES/idbfilesservice.h"
#include "DEFINES/global.h"
#include "DEFINES/idbs.h"

class ImgDatabase
{
	// == DATA ==
	QString m_path;
	QSqlDatabase m_idb;

	// == METHODS ==
public:
	ImgDatabase();
	~ImgDatabase();

	// Clear all info
	void Clear();
	// Set up exist database
	bool SetIDB(const QString &t_path);
	// Create new default image database
	bool CreateDefaultIDB();

private:
	// Check if type of database is SQLite
	bool IsSQLite(const QString &t_path);
	// Form full path to default IDB
	QString FormDefaultIDBFullName();
};

#endif // IMGDATABASE_H
