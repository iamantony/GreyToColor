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

	double SKO = BEST_SKO;
	int pixNum = t_luminances.size();
	for ( int pix = 0; pix < pixNum; pix++ )
	{
		double diff = t_centralPixLum - t_luminances.at(pix);
		SKO += pow(diff, 2);
	}

	// Pixels in mask: all pixels in mask - central pixel
	int pixInMask = pixNum;
	SKO /= pixInMask;
	SKO = pow(SKO, 0.5);

	return SKO;
}

// Calc SKO of two image passports
// @input:
// - QList<double> - unempty passport of one image
// - QList<double> - unempty passport of another image
// @output:
// - ERROR - can't calc SKO
// - double - positive value of input passports SKO
double CalculatorSKO::PassportsSKO(const QList<double> &t_first, const QList<double> &t_second)
{
	if ( (true == t_first.isEmpty()) ||
		 (true == t_second.isEmpty()) ||
		 (t_first.size() != t_second.size()) )
	{
		qDebug() << "PassportsSKO(): Error - invalid arguments";
		return ERROR;
	}

	double resultSKO = BEST_SKO;
	const int numOfValues = t_first.size();
	for (int value = 0; value < numOfValues; value++)
	{
		double diff = pow( (t_first.at(value) - t_second.at(value)), 2 );
		resultSKO += diff;
	}

	resultSKO /= (double)numOfValues;
	resultSKO = pow(resultSKO, 0.5);

	return resultSKO;
}

// Calc SKO of two images
// @input:
// - QImage - unnull image
// - QImage - unnull image
// @output:
// - ERROR - can't calc SKO
// - double - positive value of input images SKO
double CalculatorSKO::ImagesSKO(const QImage &t_firstImg, const QImage &t_secondImg)
{
	if ( (true == t_firstImg.isNull()) || (true == t_secondImg.isNull()) )
	{
		qDebug() << "ImagesSKO(): Error - invalid arguments";
		return ERROR;
	}

	const int firstWdt = t_firstImg.width();
	const int firstHgt = t_firstImg.height();
	const int secondWdt = t_secondImg.width();
	const int secondHgt = t_secondImg.height();

	if ( (firstWdt != secondWdt) || (firstHgt != secondHgt) )
	{
		qDebug() << "ImagesSKO(): Error - images has different size";
		return ERROR;
	}

	double SKO = BEST_SKO;
	for (int width = 0; width < firstWdt; width++)
	{
		for (int height = 0; height < firstHgt; height++)
		{
			QRgb firstImgPix = t_firstImg.pixel(width, height);
			QRgb secondImgPix = t_secondImg.pixel(width, height);

			double redFirst = (double)qRed(firstImgPix);
			double redSecond = (double)qRed(secondImgPix);
			double diffRed = pow( (redFirst - redSecond), 2 );

			double greenFirst = (double)qGreen(firstImgPix);
			double greenSecond = (double)qGreen(secondImgPix);
			double diffGreen = pow( (greenFirst - greenSecond), 2 );

			double blueFirst = (double)qBlue(firstImgPix);
			double blueSecond = (double)qBlue(secondImgPix);
			double diffBlue = pow( (blueFirst - blueSecond), 2 );

			SKO += diffRed + diffGreen + diffBlue;
		}
	}

	SKO = SKO / (firstWdt * firstHgt);
	SKO = pow(SKO, 0.5);

	return SKO;
}
