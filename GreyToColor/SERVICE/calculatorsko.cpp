/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2014, Antony Cherepanov <antony.cherepanov@gmail.com>
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
// - t_centralPixLum - positive relative luminance of central masks pixel
// - t_luminances - unempty list of pixels relative luminances
// @output:
// - double - positive value of pixels relative luminance SKO
// - double < 0 - can't calc SKO
double CalculatorSKO::PixelMaskSKO(const double t_centralPixLum,
								   const std::vector<double> &t_luminances) const
{
	if ( (t_centralPixLum < 0.0) || (true == t_luminances.empty()) )
	{
		qDebug() << "PixelMaskSKO(): Error - invalid arguments";
		return ERROR_FP;
	}

	double sko = BEST_SKO;
	unsigned int pixNum = t_luminances.size();
	for ( unsigned int pix = 0; pix < pixNum; ++pix )
	{
		double diff = t_centralPixLum - t_luminances[pix];
		sko += pow(diff, 2);
	}

	// Pixels in mask: all pixels in mask - central pixel
	int pixInMask = pixNum;
	sko /= pixInMask;
	sko = pow(sko, 0.5);

	return sko;
}

// Calc SKO of two image passports
// @input:
// - t_first - unempty passport of first image
// - t_second - unempty passport of second image
// @output:
// - double - positive value of input passports SKO
// - double < 0 - can't calc SKO
double CalculatorSKO::PassportsSKO(const QList<double> &t_first,
								   const QList<double> &t_second) const
{
	if ( (true == t_first.isEmpty()) ||
		 (true == t_second.isEmpty()) ||
		 (t_first.size() != t_second.size()) )
	{
		qDebug() << "PassportsSKO(): Error - invalid arguments";
		return ERROR_FP;
	}

	double resultSKO = BEST_SKO;
	const unsigned int numOfValues = t_first.size();
	for ( unsigned int value = 0; value < numOfValues; ++value )
	{
		double diff = pow( (t_first[value] - t_second[value]), 2 );
		resultSKO += diff;
	}

	resultSKO /= (double)numOfValues;
	resultSKO = pow(resultSKO, 0.5);

	return resultSKO;
}

// Calc SKO of two images
// @input:
// - t_firstImg - unnull image
// - t_secondImg - unnull image
// @output:
// - double - positive value of input images SKO
// - double < 0 - can't calc SKO
double CalculatorSKO::ImagesSKO(const QImage &t_firstImg,
								const QImage &t_secondImg) const
{
	if ( (true == t_firstImg.isNull()) || (true == t_secondImg.isNull()) )
	{
		qDebug() << "ImagesSKO(): Error - invalid arguments";
		return ERROR_FP;
	}

	const int firstWdt = t_firstImg.width();
	const int firstHgt = t_firstImg.height();
	const int secondWdt = t_secondImg.width();
	const int secondHgt = t_secondImg.height();

	if ( (firstWdt != secondWdt) || (firstHgt != secondHgt) )
	{
		qDebug() << "ImagesSKO(): Error - images has different size";
		return ERROR_FP;
	}

	double SKO = BEST_SKO;
	for (int width = 0; width < firstWdt; ++width)
	{
		for (int height = 0; height < firstHgt; ++height)
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
