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

#include "idbhandler.h"

IDBHandler::IDBHandler(QObject *parent) :
	QObject(parent)
{
	Clear();
}

IDBHandler::~IDBHandler()
{
	Clear();
}

// Clear all info
// @input:
// @output:
void IDBHandler::Clear()
{
	m_idb.Clear();
}

// Check if IDB is set up and ready to work
// @input:
// @output:
void IDBHandler::SlotCheckIDBSet()
{
	bool idbReady = m_idb.IsSet();
	emit SignalIDBStatus(idbReady);
}

// Get name for new IDB and create it
// @input:
// - QString - unempty string with name for new IDB
// @output:
void IDBHandler::SlotCreateNewIDB(const QString &t_name)
{
	if ( true == t_name.isEmpty() )
	{
		qDebug() << "SlotCreateNewIDB(): Error - invalid arguments";
		return;
	}

	bool newIDBCreated = m_idb.CreateNewIDB(t_name);
	if ( false == newIDBCreated )
	{
		emit SignalProcError(tr("Can't create new image database"));
	}
}

// Open exist IDB
// @input:
// - QString - unempty string with name of IDB
// @output:
void IDBHandler::SlotOpenIDB(const QString &t_name)
{
	if ( true == t_name.isEmpty() )
	{
		qDebug() << "SlotOpenIDB(): Error - invalid arguments";
		return;
	}

	bool idbSet = m_idb.SetIDB(t_name);
	if ( false == idbSet )
	{
		emit SignalProcError(tr("Can't open image database"));
	}
}

// Add to current database new image entries
// @input:
// - QStringList - unempty list of strings with names of exist images
// @output:
void IDBHandler::SlotAddImagesToIDB(const QStringList &t_names)
{
	if ( true == t_names.isEmpty() )
	{
		qDebug() << "SlotAddImagesToIDB(): Error - invalid arguments";
		return;
	}

	emit SignalCurrentProc(Program::DB_FORMING);

	if ( false == m_idb.IsSet() )
	{
		emit SignalProcError(tr("Image database is not set yet"));
		return;
	}

	QMap<QString, QList<QByteArray> > newEntries;
	const int imagesNum = t_names.size();
	for( int img = 0; img < imagesNum; img++ )
	{
		qDebug() << "Processing image:" << t_names.at(img);

		QList<QByteArray> passports = CreateImgPasports(t_names.at(img));
		if ( true == passports.isEmpty() )
		{
			qDebug() << "SlotAddImagesToIDB(): Warning - failed to get passports for image #" << img << ":"
					 << t_names.at(img);

			continue;
		}

		newEntries.insert(t_names.at(img), passports);
	}

	bool imagesAdded = m_idb.AddEntries(newEntries);
	if ( false == imagesAdded )
	{
		emit SignalProcError(tr("Can't add images database"));
		return;
	}

	emit SignalProcDone();
}

// Get all passports of image
// @input:
// - QString - unempty path to exist image
// @output:
// - empty QList<QByteArray> - failed to form passports
// - QList<QByteArray> - image passports
QList<QByteArray> IDBHandler::CreateImgPasports(const QString &t_imgPath)
{
	if ( true == t_imgPath.isEmpty() )
	{
		qDebug() << "CreateImgPasports(): Error - invalid arguments";
		QList<QByteArray> empty;
		return empty;
	}

	CandidateImage procImg;
	bool imgLoaded = procImg.LoadColorImg(t_imgPath);
	if ( false == imgLoaded )
	{
		qDebug() << "CreateImgPasports(): can't load image :" << t_imgPath;
		QList<QByteArray> empty;
		return empty;
	}

	bool passportsFormed = procImg.FormAllPassports();
	if ( false == passportsFormed )
	{
		qDebug() << "CreateImgPasports(): can't form passports for image:" << t_imgPath;
		QList<QByteArray> empty;
		return empty;
	}

	QList<ImgPassport> imgPassports = procImg.GetAllPassports();
	if ( true == imgPassports.isEmpty() )
	{
		qDebug() << "CreateImgPasports(): can't form passports for image:" << t_imgPath;
		QList<QByteArray> empty;
		return empty;
	}

	QList<QByteArray> passportsArrays;
	const int passportsNum = imgPassports.size();
	for ( int pass = 0; pass < passportsNum; pass++ )
	{
		QByteArray arrayPass = imgPassports.at(pass).GetPassportAsArray();
		passportsArrays.append(arrayPass);
	}

	return passportsArrays;
}
