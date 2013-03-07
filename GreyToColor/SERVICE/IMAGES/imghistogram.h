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

#ifndef IMGHISTOGRAM_H
#define IMGHISTOGRAM_H

#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include "./IMAGES/COMMON/image.h"
#include "imgtransform.h"
#include "DEFINES/imgservice.h"

class ImgHistogram
{
	// == DATA ==

	// == METHODS ==
public:
	ImgHistogram();

	// Get image luminance histogram (in percent)
	QList<double> LuminanceHistogram(const Image &t_img);
	// Get image channels histogram (in percent)
	QList< QList<double> > RGBHistogram(const Image &t_img);

	// Test of forming image histogram
	void TestRGBHist();

private:
	// Get RGB image channels histogram (in percent)
	QList< QList<double> > CalcRGBHistogram(const QImage &t_img);
	// Calc images' channels statistics
	QList< QList<double> > CalcRGBChannStatistic(const QImage &t_img);
	// Get zero RGB histogram
	QList< QList<double> > FormZeroRGBHist();
	// Transform statistic histogram to statistic histogram in percent
	QList< QList<double> > FormStatHistInPercent(const QList< QList<double> > &t_statHist);
};

#endif // IMGHISTOGRAM_H
