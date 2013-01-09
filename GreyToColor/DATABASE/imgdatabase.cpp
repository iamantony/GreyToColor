#include "imgdatabase.h"

ImgDataBase::ImgDataBase(QObject *parent) :
	QObject(parent)
{
	bool idbExist = CheckIDBExist();
	if ( false == idbExist )
	{
		bool dbCreated = CreateIDB();
		if ( false == dbCreated )
		{
			qDebug() << "AddEntriesToIDB(): error - can't create DB";
		}
	}
	else
	{
		IDB = QSqlDatabase::addDatabase("QSQLITE");
		QString path = FormIDBFullName();
		IDB.setDatabaseName(path);
	}
}

ImgDataBase::~ImgDataBase()
{
	IDB.close();
}

//bool ImgDataBase::CreateIDB()
//{

//	IDB = QSqlDatabase::addDatabase("QSQLITE");
//	QString path;
//	QDir dir;
//	path.append(dir.absolutePath());
//	path.append("/idb/idb.sqlite");
//	IDB.setDatabaseName(path);

//	bool openIDB = IDB.open();
//	qDebug() << openIDB;

//	QSqlQuery query(IDB);
//	bool result = query.exec("create table test (id integer primary key, string varchar(30), passport BLOB)");
//	if ( false == result )
//		qDebug() << query.lastError();

//	QString str;
//	str.append("this is string");

//	QByteArray list;
//	list.append(100);
//	list.append(101);
//	list.append(102);
//	list.append(103);

//	query.prepare("INSERT INTO test (string, passport) VALUES (?, ?)");
//	for (int i = 0; i < 5; ++i)
//	{
////		query.bindValue(0, i);
//		query.bindValue(0, str);
//		query.bindValue(1, list);

//		if (!query.exec())
//			qWarning() << query.lastError();
//	}

//	query.exec(QString("delete from test where id=%1").arg(2));

//	qDebug() << "Now get info from database";

//	query.prepare("SELECT id, string, passport FROM test");
//	if (query.exec())
//	{
//		while ( query.next() )
//		{
//			qDebug() << query.isActive();
//			qDebug() << query.isValid();
//			qDebug() << query.value(0).toInt();
//			qDebug() << query.value(1).toString();
//			QVariant var = query.value(2);
//			QByteArray newList =var.toByteArray();
//			qDebug() << newList.size();
//		}
//	}
//	else
//		qDebug() << query.lastError();

//	IDB.close();

//	return true;
//}

bool ImgDataBase::CreateIDB()
{
	IDB = QSqlDatabase::addDatabase("QSQLITE");

	QString path = FormIDBFullName();

	FileOperations removeFile;
	removeFile.RemoveFileIfExist(path);

	IDB.setDatabaseName(path);
	bool openIDB = IDB.open();
	if ( false == openIDB )
	{
		qDebug() << "CreateIDB(): error - can't open database";
		return false;
	}

	QString command;
	command.append("create table idb (");
	command.append("id integer primary key");
	command.append(", imgname varchar(100)");
	command.append(", passport_0 BLOB");
//	command.append(", passport_1 BLOB");
//	command.append(", passport_2 BLOB");
//	command.append(", passport_3 BLOB");
	command.append(")");

	QSqlQuery query(IDB);
	bool result = query.exec(command);
	if ( false == result )
	{
		qDebug() << "CreateIDB(): error - can't create database";
		return false;
	}

	IDB.close();

	return true;
}

QString ImgDataBase::FormIDBFullName()
{
	FileOperations fileName;
	QString partOfPath(PROJECT_DB_NAME);
	QString fullIDBName = fileName.FormFullName(partOfPath);
	return fullIDBName;
}

bool ImgDataBase::AddEntriesToIDB(QMap<QString, QList<QByteArray> > &t_entries)
{
	if ( t_entries.isEmpty() )
	{
		return true;
	}

	bool openIDB = IDB.open();
	if ( false == openIDB )
	{
		qDebug() << "AddEntriesToIDB(): error - can't open database";
		return false;
	}

	QSqlQuery query(IDB);
	query.prepare("INSERT INTO idb (imgname, passport_0) VALUES (?, ?)");

	QMap<QString, QList<QByteArray> >::iterator iter = t_entries.begin();
	while( iter != t_entries.end() )
	{
		QString imgName = iter.key();
		QList<QByteArray> imgPassports = iter.value();

		query.bindValue(0, imgName);
		query.bindValue(1, imgPassports.at(0));

		bool entryAppended = query.exec();
		if ( false == entryAppended )
		{
			qDebug() << "AddEntriesToIDB(): error - can't append to database image" << imgName;
			qWarning() << query.lastError();
		}

		++iter;
	}

	IDB.close();

	ReadAllEntries();

	return true;
}

bool ImgDataBase::CheckIDBExist()
{
	QString path = FormIDBFullName();
	FileOperations file;
	return file.CheckFileExistance(path);
}

QMap<QString, QByteArray> ImgDataBase::GetImagesPassport(int t_passportType)
{
	QMap<QString, QByteArray> imgsPassports;

	// TODO: use enums and namespace instead of defines!
	if ( (t_passportType < FIRST_PASSPORT) && (LAST_PASSPORT < t_passportType) )
	{
		qDebug() << "GetImagesPassport(): error - passport out of range";
		return imgsPassports;
	}

	bool openIDB = IDB.open();
	if ( false == openIDB )
	{
		qDebug() << "GetImagesPassport(): error - can't open database";
		return imgsPassports;
	}

	QSqlQuery query(IDB);
	query.prepare("SELECT imgname, passport_0 FROM idb");
	if (query.exec())
	{
		while ( query.next() )
		{
			QVariant var = query.value(1);
			imgsPassports.insert(query.value(0).toString(), var.toByteArray());
		}
	}
	else
		qDebug() << query.lastError();

	IDB.close();

	return imgsPassports;
}

bool ImgDataBase::LoadIDB()
{
	return true;
}

void ImgDataBase::UpdateIDB()
{

}

void ImgDataBase::ReadAllEntries()
{
	bool openIDB = IDB.open();
	if ( false == openIDB )
	{
		qDebug() << "ReadAllEntries(): error - can't open database";
		return;
	}

	QSqlQuery query(IDB);
	query.prepare("SELECT id, imgname, passport_0 FROM idb");
	if (query.exec())
	{
		while ( query.next() )
		{
			qDebug() << query.value(0).toInt();
			qDebug() << query.value(1).toString();
			QVariant var = query.value(2);
			QByteArray newList =var.toByteArray();
			qDebug() << newList.size();
		}
	}
	else
		qDebug() << query.lastError();

	IDB.close();
}
