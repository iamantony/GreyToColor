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

#ifndef CALCULATORSKO_H
#define CALCULATORSKO_H

#include <QObject>
#include <QDebug>
#include <math.h>
#include "./DEFINES/global.h"
#include "./DEFINES/calcsko.h"

class CalculatorSKO : public QObject
{
	Q_OBJECT

	// == DATA ==

	// == METHODS ==
public:
	explicit CalculatorSKO(QObject *parent = 0);

	// Calc SKO of two images
	double ImagesSKO(/*const Image &t_first, const Image &t_second*/);
	// Calc SKO of two image passports
	double PassportsSKO(const QList<double> &t_first, const QList<double> &t_second);
	// Calc SKO for a pixel mask
	double PixelMaskSKO(const double t_centralPixLum, const QList<double> &t_luminances);
};

#endif // CALCULATORSKO_H
