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

// Check if database set (name, driver) and ready to work
// @input:
// @output:
// - true - database ready
// - false - database not set yet
bool ImgDatabase::IsSet()
{
	if ( (true == m_path.isEmpty()) || (false == m_idb.isValid()) )
	{
		return false;
	}

	return true;
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

	m_idb = QSqlDatabase::addDatabase("QSQLITE");
	m_idb.setDatabaseName(t_path);
	if ( false == m_idb.isValid() )
	{
		qDebug() << "SetIDB(): Error - can't set up database";
		return false;
	}

	bool idbOpened = m_idb.open();
	if ( false == idbOpened )
	{
		qDebug() << "SetIDB(): Error - can't open database";
		return false;
	}

	// TODO:
	// - check if name of IDN is idb. SELECT?

	m_idb.close();
	m_path = t_path;

	return true;
}

// Check if type of database is SQLite
// @input:
// - QString - unempty path to exist database
// @output:
// - true - database is SQLite
// - false  - databes is not SQLite
bool ImgDatabase::IsSQLite(const QString &t_path) const
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

	QString sqliteSuffix(SQLITE_SUFFIX);
	// Remove "dot" (.) from suffix
	sqliteSuffix.remove(0, 1);

	if ( sqliteSuffix != suffix )
	{
		return false;
	}

	return true;
}

// Create new default image database
// @input:
// - QString - unempty name for new database (without suffix)
// @output:
// - true - new IDB created
// - false - can't create new IDB
bool ImgDatabase::CreateNewIDB(const QString &t_name)
{
	QString path = FormIDBFullName(t_name);
	if ( true == path.isEmpty() )
	{
		qDebug() << "CreateDefaultIDB(): Error - no name for new IDB";
		return false;
	}

	IDBFilesService idbService;
	bool prevIDBRemoved = idbService.RemoveIDB(path);
	if ( false == prevIDBRemoved )
	{
		qDebug() << "CreateDefaultIDB(): Error - can't delete previous IDB with name" << path;
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
	command.append("id integer primary key, ");
	command.append("imgname varchar(1000), ");
	command.append("imgPassLumHist BLOB, ");
	command.append("imgPassLumSub BLOB, ");
	command.append("imgPassLumGradHist BLOB, ");
	command.append("imgPassLumGradSub BLOB");
	command.append(")");

	QSqlQuery query(m_idb);
	bool result = query.exec(command);
	if ( false == result )
	{
		qDebug() << "CreateIDB(): Error - can't create database";
		idbService.RemoveIDB(path);
		return false;
	}

	m_idb.close();
	m_path = path;

	return true;
}

// Form full path to IDB
// @input:
// - QString - unempty name for new database (without suffix)
// @output:
// - empty QString - can't form path
// - QString - full path to default IDB
QString ImgDatabase::FormIDBFullName(const QString &t_name) const
{
	QString partOfPath;
	partOfPath.append(DEFAULT_IDB_FOLDER);

	if ( true == t_name.isEmpty() )
	{
		partOfPath.append(DEFAULT_IDB_NAME);
	}
	else
	{
		partOfPath.append(t_name);
	}

	partOfPath.append(SQLITE_SUFFIX);

	IDBFilesService idbService;
	QString defPath = idbService.FormIDBFullPath(partOfPath);
	return defPath;
}

// Add new entry (image name and it's passports) to IDB
// @input:
// - QMap<QString, QList<QByteArray> > - unempty map of entries (full name of image and it's passports)
// @output:.
// - true - entries have been added
// - false - failed to add entries
bool ImgDatabase::AddEntries(const QMap<QString, QList<QByteArray> > &t_entries)
{
	if ( true == t_entries.isEmpty() )
	{
		qDebug() << "AddEntries(): Error - invalid arguments";
		return false;
	}

	// TODO:
	// - check if entry with the same image path already exist in IDB. If yes - delete it

	bool idbOpened = m_idb.open();
	if ( false == idbOpened )
	{
		qDebug() << "AddEntries(): Error - can't open database";
		return false;
	}

	QSqlQuery query(m_idb);
	query.prepare("INSERT INTO idb (imgname, imgPassLumHist, imgPassLumSub, imgPassLumGradHist, imgPassLumGradSub) "
				  "VALUES (?, ?, ?, ?, ?)");

	QMap<QString, QList<QByteArray> >::const_iterator entry = t_entries.begin();
	while( entry != t_entries.end() )
	{
		QString imgName = entry.key();
		QList<QByteArray> imgPassports = entry.value();
		if ( PASSPORTS_NUM != imgPassports.size() )
		{
			qDebug() << "AddEntries(): Error - can't add to database image" << imgName;
		}
		else
		{
			query.bindValue(0, imgName);
			query.bindValue(1, imgPassports.at(0));
			query.bindValue(2, imgPassports.at(1));
			query.bindValue(3, imgPassports.at(2));
			query.bindValue(4, imgPassports.at(3));

			bool entryAppended = query.exec();
			if ( false == entryAppended )
			{
				qDebug() << "AddEntries(): error - failed to append to database image" << imgName;
				qDebug() << query.lastError();
			}
		}

		++entry;
	}

	m_idb.close();

	return true;
}

// Get passports of certain type from all images in IDB
// @input:
// - Passport::Type - exist passport type
// @output:
// - empty QMap<QString, QByteArray> - failed to get image passports
// - QMap<QString, QByteArray> - passports of images in IDB
QMap<QString, QByteArray> ImgDatabase::GetImagesPassport(const Passport::Type &t_passType)
{
	if ( Passport::DEFAULT_LAST == t_passType )
	{
		qDebug() << "GetImagesPassport(): Error - invalid passport type";
		QMap<QString, QByteArray> empty;
		return empty;
	}

	bool idbOpened = m_idb.open();
	if ( false == idbOpened )
	{
		qDebug() << "GetImagesPassport(): Error - can't open database";
		QMap<QString, QByteArray> empty;
		return empty;
	}

	QMap<QString, QByteArray> imgsPassports;

	QString passportName;
	switch(t_passType)
	{
		case Passport::LUM_HISTOGRAM:
			passportName.append("imgPassLumHist");
			break;

		case Passport::LUM_SUBSAMPLE:
			passportName.append("imgPassLumSub");
			break;

		case Passport::LUM_AND_GRAD_HIST:
			passportName.append("imgPassLumGradHist");
			break;

		case Passport::LUM_AND_GRAD_SUB:
			passportName.append("imgPassLumGradSub");
			break;

		case Passport::DEFAULT_LAST:
		default:
		{
			qDebug() << "GetImagesPassport(): Error - invalid passport type";
			QMap<QString, QByteArray> empty;
			return empty;
		}
	}

	// TODO: names for passports in idb

	QSqlQuery query(m_idb);
	QString idbRequest = QString("SELECT imgname, %1 FROM idb").arg(passportName);
	query.prepare(idbRequest);
	if ( true == query.exec() )
	{
		while ( true == query.next() )
		{
			QString imgPath(query.value(0).toString());
			QByteArray passport = query.value(1).toByteArray();
			imgsPassports.insert(imgPath, passport);
		}
	}
	else
	{
		qDebug() << "GetImagesPassport(): Error - SELECT from IDB failed";
		qDebug() << query.lastError();
	}

	m_idb.close();

	return imgsPassports;
}

// Get all passports from all images in IDB
// @input:
// @output:
// - empty QMap<QString, QList<QByteArray> > - failed to get image passports
// - QMap<QString, QList<QByteArray> > - passports of images in IDB
QMap<QString, QList<QByteArray> > ImgDatabase::GetAllPassport()
{
	bool idbOpened = m_idb.open();
	if ( false == idbOpened )
	{
		qDebug() << "GetAllPassport(): Error - can't open database";
		QMap<QString, QList<QByteArray> > empty;
		return empty;
	}

	QMap<QString, QList<QByteArray> > imgsPassports;

	QSqlQuery query(m_idb);
	query.prepare("SELECT imgname, passport_0, passport_1, passport_2, passport_3 FROM idb");
	if ( true == query.exec() )
	{
		while ( true == query.next() )
		{
			QString imgPath(query.value(0).toString());
			QList<QByteArray> passports;
			for ( int val = 1; val < PASSPORTS_NUM + 1; val++ )
			{
				QVariant var = query.value(val);
				passports.append(var.toByteArray());
			}

			imgsPassports.insert(imgPath, passports);
		}
	}
	else
	{
		qDebug() << "GetAllPassport(): Error - SELECT from IDB failed";
		qDebug() << query.lastError();
	}

	m_idb.close();

	return imgsPassports;
}
