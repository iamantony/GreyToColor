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
#include "SERVICE/IMAGES/imgpassportcomparer.h"
#include "SERVICE/FILES/imgfilesservice.h"
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

private:
	// Get all passports of image
	QList<QByteArray> CreateImgPasports(const QString &t_imgPath);
	// Get for image passport of certain type
	ImgPassport GetImgPassport(const Image &t_img, const Passport::Type &t_type);
	// Get from IDB passport of certain type
	QMap<QString, ImgPassport> GetPassportsFromIDB(const Passport::Type &t_type);

signals:
	void SignalIDBStatus(const bool &t_status);
	void SignalSimilarImg(const QString &t_name);
	void SignalCurrentProc(const Program::Status &);
	void SignalProcDone();
	void SignalProcError(const QString &);
	void SignalProcFatalError();

public slots:
	// Check if IDB is set up and ready to work
	void SlotCheckIDBSet();
	// Get name for new IDB and create it
	void SlotCreateNewIDB(const QString &t_name);
	// Open exist IDB
	void SlotOpenIDB(const QString &t_name);
	// Add to current database new image entries
	void SlotAddImagesToIDB(const QStringList &t_names);
	// Find for input image similar pixture from IDB
	void SlotFindSimilar(const Image &t_img);
};

#endif // IDBHANDLER_H
