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

#include "imgpassportcomparer.h"

ImgPassportComparer::ImgPassportComparer()
{

}

// Find the most similar image passport
// @input:
// - ImgPassport - unempty reference image passport
// - QMap<QString, ImgPassport> - map of images and it's passports
// @output:
// - QString - path to the most similar image for reference image
QString ImgPassportComparer::FindMostSimilar(const ImgPassport &t_reference,
											 const QMap<QString, ImgPassport> &t_variants)
{
	if ( (true == t_reference.IsEmpty()) || (true == t_variants.isEmpty()) )
	{
		qDebug() << "FindMostSimilar(): Error - invalid arguments";
		QString empty;
		return empty;
	}

	CalculatorSKO calc;
	QString nameOfSimilar;
	double minSKO = DEFAULT_SKO;
	const QList<double> refPass = t_reference.GetPassportAsList();

	QMap<QString, ImgPassport>::const_iterator var = t_variants.begin();
	while( var != t_variants.end() )
	{
		ImgPassport passport = var.value();
		QList<double> varPass = passport.GetPassportAsList();

		double passSKO = calc.PassportsSKO(refPass, varPass);
		if ( passSKO < minSKO )
		{
			minSKO = passSKO;
			nameOfSimilar = var.key();
		}

		++var;
	}

	return nameOfSimilar;
}
