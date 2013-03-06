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

#ifndef PASSPORT_H
#define PASSPORT_H

#include <QList>
#include <QByteArray>
#include <QDebug>
#include "./DEFINES/global.h"
#include "./DEFINES/images.h"

// NOTE:
// - passport can't be empty
// - size of passport is not fixed
// - you can compare passports with equal size and type

class ImgPassport
{
	// == DATA ==
private:
	Passport::Type m_type;
	QList<double> m_imgPassport;

	// == METHODS ==
public:
	ImgPassport();
	~ImgPassport();

	// Clear all info
	void Clear();
	// Check if image passport is empty
	bool IsEmpty();
	// Set image passport as list
	bool SetPassport(const Passport::Type &t_type, const QList<double> &t_passport);
	// Set passport as array of bytes
	bool SetPassport(const Passport::Type &t_type, const QByteArray &t_passport);
	// Get passport type
	Passport::Type GetPassportType() const;
	// Get image passport as list
	QList<double> GetPassportAsList() const;
	// Get image passport as array of bytes
	QByteArray GetPassportAsArray() const;

private:
	// Convert image passport from array of bytes to list
	QList<double> FromArrayToList(const QByteArray &t_passport) const;
	// Convert image passport from list to array of bytes
	QByteArray FromListToArray(const QList<double> &t_passport) const;
};

#endif // PASSPORT_H
