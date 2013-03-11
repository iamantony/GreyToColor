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

#ifndef IDBHANDLER_H
#define IDBHANDLER_H

#include <QObject>
#include "IMAGES/COMMON/image.h"
#include "IMAGES/CANDIDATE/candidateimage.h"
#include "PARAMS/IMAGES/imgpassport.h"
#include "DATABASE/imgdatabase.h"
#include "DEFINES/global.h"
#include "DEFINES/programstatus.h"

class IDBHandler : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	ImgDatabase m_idb;

	// == METHODS ==
public:
	explicit IDBHandler(QObject *parent = 0);
	~IDBHandler();

	// Clear all info
	void Clear();
//	+ bool AddImgToIDB( QString )
//	+ bool AddImagesToIDB( QStringList )
//	+ QString FindSimilarImg( Image, Passport::Type )

signals:
	void SignalIDBStatus(const bool &t_status);
	void SignalCurrentProc(const Program::Status &);
	void SignalProcDone();
	void SignalProcError(const QString &);
	void SignalProcFatalError();

public slots:
	// Check if IDB is set up and ready to work
	void SlotCheckIDBSet();
	// Get name for new IDB and create it
	void SlotCreateNewIDB(const QString &t_name);
};

#endif // IDBHANDLER_H
