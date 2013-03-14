/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2013, Antony Cherepanov <antony.cherepanov@gmail.com>
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

#include "imgpassport.h"

ImgPassport::ImgPassport()
{
	Clear();
}

ImgPassport::~ImgPassport()
{
	Clear();
}

// Clear all info
// @input:
// @output:
void ImgPassport::Clear()
{
	m_type = Passport::DEFAULT_LAST;
	m_imgPassport.clear();
}

// Check if image passport is empty
// @input:
// @output:
// - true - passport is empty and can't be used
// - false - passport has information
bool ImgPassport::IsEmpty() const
{
	if ( (Passport::DEFAULT_LAST == m_type) || (true == m_imgPassport.isEmpty()) )
	{
		return true;
	}

	return false;
}

// Set image passport as list
// @input:
// - Passport::Type - exist image passport type
// - QList<double> - unempty image passport
// @output:
// - true - passport set
// - false - can't set passport
bool ImgPassport::SetPassport(const Passport::Type &t_type, const QList<double> &t_passport)
{
	if ( (Passport::DEFAULT_LAST == t_type) || (true == t_passport.isEmpty()) )
	{
		qDebug() << "SetPassport(): Error - invalid arguments";
		return false;
	}

	m_type = t_type;

	m_imgPassport.clear();
	m_imgPassport = t_passport;

	return true;
}

// Set passport as array of bytes
// @input:
// - Passport::Type - exist image passport type
// - QByteArray - unempty image passport
// @output:
// - true - passport set
// - false - can't set passport
bool ImgPassport::SetPassport(const Passport::Type &t_type, const QByteArray &t_passport)
{
	if ( (Passport::DEFAULT_LAST == t_type) || (true == t_passport.isEmpty()) )
	{
		qDebug() << "SetPassport(): Error - invalid arguments";
		return false;
	}

	m_type = t_type;

	QList<double> convertedPassport = FromArrayToList(t_passport);
	if ( true == convertedPassport.isEmpty() )
	{
		qDebug() << "SetPassport(): Error - can't perform passport conversion";
		return false;
	}

	m_imgPassport.clear();
	m_imgPassport = convertedPassport;

	return true;
}

// Get passport type
// @input:
// @output:
// - Passport::DEFAULT_LAST - image passport not set
// - Passport::Type - image passport type
Passport::Type ImgPassport::GetPassportType() const
{
	return m_type;
}

// Get image passport as list
// @input:
// @output:
// - empty QList<double> - ther is no passport
// - QList<double> - image passport
QList<double> ImgPassport::GetPassportAsList() const
{
	return m_imgPassport;
}

// Get image passport as array of bytes
// @input:
// @output:
// - empty QByteArray - ther is no passport
// - QByteArray - image passport as array of bytes
QByteArray ImgPassport::GetPassportAsArray() const
{
	QByteArray passport = FromListToArray(m_imgPassport);
	if ( true == passport.isEmpty() )
	{
		qDebug() << "GetPassport(): Error - passport conversion fail";
	}

	return passport;
}

// Convert image passport from array of bytes to list
// @input:
// - QByteArray - unempty image passport as array of bytes
// @output:
// - empty QList<double> - passport conversion failed
// - QList<double> - converted passport
QList<double> ImgPassport::FromArrayToList(const QByteArray &t_passport) const
{
	if ( true == t_passport.isEmpty() )
	{
		qDebug() << "FromArrayToList(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	int modulo = t_passport.size()%sizeof(double);
	if ( 0 < modulo )
	{
		qDebug() << "FromArrayToList(): Error - passport has invalid size";
		QList<double> empty;
		return empty;
	}

	QByteArray passportArray = t_passport;
	QList<double> convertedPassport;
	int numOfEntries = passportArray.size()/sizeof(double);
	double *number = reinterpret_cast<double*>(passportArray.data());
	for (int entry = 0; entry < numOfEntries; entry++)
	{
		convertedPassport.append(*number);
		number++;
	}

	return convertedPassport;
}

// Convert image passport from list to array of bytes
// @input:
// - QList<double> - unempty image passport as list
// @output:
// - empty QByteArray - passport conversion failed
// - QByteArray - converted passport as array of bytes
QByteArray ImgPassport::FromListToArray(const QList<double> &t_passport) const
{
	if ( true == t_passport.isEmpty() )
	{
		qDebug() << "FromListToArray(): Error - invalid arguments";
		QByteArray empty;
		return empty;
	}

	QByteArray convertedPassport;
	int numOfEntries = t_passport.size();
	for ( int entry = 0; entry < numOfEntries; entry++ )
	{
		double passportEntry = t_passport.at(entry);
		convertedPassport.append(reinterpret_cast<char*>(&passportEntry), sizeof(double));
	}

	return convertedPassport;
}
