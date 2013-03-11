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

#include "imgdatabase.h"

ImgDatabase::ImgDatabase()
{
	Clear();
}

ImgDatabase::~ImgDatabase()
{
	Clear();
}

// Clear all info
// @input:
// @output:
void ImgDatabase::Clear()
{
	m_idb.close();
	m_path.clear();
}

// Set up exist database
// @input:
// - QString - unempty path to exist database
// @output:
// - true - database set up
// - false  - can't set up database
bool ImgDatabase::SetIDB(const QString &t_path)
{
	if ( true == t_path.isEmpty() )
	{
		qDebug() << "SetIDB(): Error - invalid arguments";
		return false;
	}

	IDBFilesService idbService;
	bool idbExist = idbService.CheckIDBExist(t_path);
	if ( false == idbExist )
	{
		qDebug() << "SetIDB(): Error - image database with such name don't exist";
		return false;
	}

	bool isSQLite = IsSQLite(t_path);
	if ( false == isSQLite )
	{
		qDebug() << "SetIDB(): Error - type of image database is not a SQLite";
		return false;
	}

	m_path = t_path;
	m_idb = QSqlDatabase::addDatabase("QSQLITE");
	m_idb.setDatabaseName(m_path);

	if ( false == m_idb.isValid() )
	{
		qDebug() << "SetIDB(): Error - can't set up database";
		Clear();
		return false;
	}

	return true;
}

// Check if type of database is SQLite
// @input:
// - QString - unempty path to exist database
// @output:
// - true - database is SQLite
// - false  - databes is not SQLite
bool ImgDatabase::IsSQLite(const QString &t_path)
{
	if ( true == t_path.isEmpty() )
	{
		qDebug() << "IsSQLite(): Error - invalid arguments";
		return false;
	}

	QFileInfo idbInfo(t_path);
	QString suffix = idbInfo.completeSuffix();
	if ( true == suffix.isEmpty() )
	{
		qDebug() << "IsSQLite(): Error - no suffix";
		return false;
	}

	if ( SQLITE_SUFFIX != suffix )
	{
		return false;
	}

	return true;
}

// Create new default image database
// @input:
// @output:
// - true - new IDB created
// - false - can't create new IDB
bool ImgDatabase::CreateDefaultIDB()
{
	QString path = FormDefaultIDBFullName();
	if ( true == path.isEmpty() )
	{
		qDebug() << "CreateDefaultIDB(): Error - no default name for IDB";
		return false;
	}

	IDBFilesService idbService;
	bool prevIDBRemoved = idbService.RemoveIDB(path);
	if ( false == prevIDBRemoved )
	{
		qDebug() << "CreateDefaultIDB(): Error - can't delete previous default IDB";
		return false;
	}

	m_idb = QSqlDatabase::addDatabase("QSQLITE");
	m_idb.setDatabaseName(path);
	bool idbOpened = m_idb.open();
	if ( false == idbOpened )
	{
		qDebug() << "CreateDefaultIDB(): Error - can't open database";
		return false;
	}

	QString command;
	command.append("create table idb (");
	command.append("id integer primary key");
	command.append(", imgname varchar(1000)");
	command.append(", passport_0 BLOB");
	command.append(", passport_1 BLOB");
//	command.append(", passport_2 BLOB");
//	command.append(", passport_3 BLOB");
	command.append(")");

	QSqlQuery query(m_idb);
	bool result = query.exec(command);
	if ( false == result )
	{
		qDebug() << "CreateIDB(): Error - can't create database";
		return false;
	}

	m_idb.close();

	return true;
}

// Form full path to default IDB
// @input:
// @output:
// - empty QString - can't form path
// - QString - full path to default IDB
QString ImgDatabase::FormDefaultIDBFullName()
{
	IDBFilesService idbService;
	QString defPath = idbService.FormIDBFullPath(DEFAULT_IDB_NAME);
	return defPath;
}
