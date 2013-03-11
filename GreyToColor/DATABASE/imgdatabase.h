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
#include "DEFINES/images.h"
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
	// Check if database set (name, driver) and ready to work
	bool IsSet();
	// Set up exist database
	bool SetIDB(const QString &t_path);
	// Create new image database
	bool CreateNewIDB(const QString &t_name);
	// Add new entry (image name and it's passports) to IDB
	bool AddEntries(const QMap<QString, QList<QByteArray> > &t_entries);
	// Get passports of certain type from all images in IDB
	QMap<QString, QByteArray> GetImagesPassport(const Passport::Type &t_passType);
	// Get all passports from all images in IDB
	QMap<QString, QList<QByteArray> > GetAllPassport();

private:
	// Check if type of database is SQLite
	bool IsSQLite(const QString &t_path) const;
	// Form full path to IDB
	QString FormIDBFullName(const QString &t_name) const;
};

#endif // IMGDATABASE_H
