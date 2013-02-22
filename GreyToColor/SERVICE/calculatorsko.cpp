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

#include "calculatorsko.h"

CalculatorSKO::CalculatorSKO(QObject *parent) :
	QObject(parent)
{

}

// Calc SKO for a pixel mask
// @input:
// - double - positive luminance of central masks pixel
// - QList<double> - unempty list of pixels luminances
// @output:
// - ERROR - can't calc SKO
// - double - positive value of pixels luminance SKO
double CalculatorSKO::PixelMaskSKO(const double t_centralPixLum, const QList<double> &t_luminances)
{
	if ( (t_centralPixLum < 0) || (true == t_luminances.isEmpty()) )
	{
		qDebug() << "CalcPixelMaskSKO(): Error - invalid arguments";
		return ERROR;
	}

	double SKO = 0;
	for ( int pix = 0; pix < t_luminances.size(); pix++ )
	{
		double diff = t_centralPixLum - t_luminances.at(pix);
		SKO += pow(diff, 2);
	}

	SKO = pow(SKO, 0.5);

	return SKO;
}
