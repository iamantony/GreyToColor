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
