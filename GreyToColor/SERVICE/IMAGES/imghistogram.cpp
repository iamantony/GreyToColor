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

#include "imghistogram.h"

ImgHistogram::ImgHistogram()
{

}

// Get image luminance histogram (in percent)
// @input:
// - Image - unnull image (color/grey)
// @output:
// - empty QList<unsigned int> - failed to form histogram
// - QList<unsigned int> - images luminance histogram
QList<double> ImgHistogram::LuminanceHistogram(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "LuminanceHistogram(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	ImgTransform imgTransformer;
	Image greyImg = imgTransformer.ToGrey(t_img);
	if ( true == greyImg.IsNull() )
	{
		qDebug() << "LuminanceHistogram(): Error - can't greyscale image";
		QList<double> empty;
		return empty;
	}

	QImage greyscaledImg = greyImg.GetImg();
	QList< QList<double> > lumHist = CalcRGBHistogram(greyscaledImg);
	if ( true == lumHist.isEmpty() )
	{
		qDebug() << "LuminanceHistogram(): Error - can't form luminance histogram";
		QList<double> empty;
		return empty;
	}

	// All histograms of greyscaled image are the same. You can return any one.
	return lumHist.at(RED);
}

// Get image channels histogram (in percent)
// @input:
// - Image - unnull image (color/grey)
// @output:
// - empty QList< QList<unsigned int> > - failed to form RGB channels histogram
// - QList< QList<unsigned int> > - histograms of all image channels
QList<QList<double> > ImgHistogram::RGBHistogram(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "RGBHistogram(): Error - invalid arguments";
		QList< QList<double> > empty;
		return empty;
	}

	QImage processingImg = t_img.GetImg();
	QList< QList<double> > rgbHist = CalcRGBHistogram(processingImg);
	if ( true == rgbHist.isEmpty() )
	{
		qDebug() << "RGBHistogram(): Error - can't form images' channels histogram";
		QList< QList<double> > empty;
		return empty;
	}

	return rgbHist;
}

// Get RGB image channels histogram (in percent)
// @input:
// - QImage - unnull image (color/grey)
// @output:
// - empty QList< QList<unsigned int> > - failed to form RGB channels histogram
// - QList< QList<unsigned int> > - histograms of all images' channels
QList<QList<double> > ImgHistogram::CalcRGBHistogram(const QImage &t_img)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "CalcRGBHistogram(): Error - invalid arguments";
		QList< QList<double> > empty;
		return empty;
	}

	QList< QList<double> > rgbStatHist = CalcRGBChannStatistic(t_img);
	if ( true == rgbStatHist.isEmpty() )
	{
		qDebug() << "CalcRGBHistogram(): Error - can't calc channels statistic";
		QList< QList<double> > empty;
		return empty;
	}

	QList< QList<double> > rgbHistInPercent = FormStatHistInPercent(rgbStatHist);

	return rgbHistInPercent;
}

// Calc images' channels statistics
// @input:
// - QImage - unnull image (color/grey)
// @output:
// - empty QList< QList<unsigned int> > - failed to form RGB channels histogram statistic
// - QList< QList<unsigned int> > - statistic histograms of all RGB images' channels
QList< QList<double> > ImgHistogram::CalcRGBChannStatistic(const QImage &t_img)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "CalcRGBHistogram(): Error - invalid arguments";
		QList< QList<double> > empty;
		return empty;
	}

	QList< QList<double> > rgbHistogram = FormZeroRGBHist();

	const bool imgIsGrey = t_img.isGrayscale();
	const int imgW = t_img.width();
	const int imgH = t_img.height();
	for (int wdt = 0; wdt < imgW; wdt++)
	{
		for (int hgt = 0; hgt < imgH; hgt++)
		{
			QRgb pixel = t_img.pixel(wdt, hgt);

			int redValue = qRed(pixel);
			rgbHistogram[RED][redValue]++;

			if ( false == imgIsGrey )
			{
				int greenValue = qGreen(pixel);
				rgbHistogram[GREEN][greenValue]++;

				int blueValue = qBlue(pixel);
				rgbHistogram[BLUE][blueValue]++;
			}
		}
	}

	if ( true == imgIsGrey )
	{
		QList<double> redChannelHist = rgbHistogram.at(RED);
		rgbHistogram.replace(GREEN, redChannelHist);
		rgbHistogram.replace(BLUE, redChannelHist);
	}

	return rgbHistogram;
}

// Get zero RGB histogram
// @input:
// @output:
// - QList< QList<unsigned int> > - zero RGB histograms
QList<QList<double> > ImgHistogram::FormZeroRGBHist()
{
	QList< QList<double> > zeroRGBHist;
	QList<double> channelHistogram;
	for ( int color = MIN_RGB_LUM; color <= MAX_RGB_LUM; color++ )
	{
		channelHistogram.append(0);
	}

	for ( int channel = 0; channel < NUM_OF_RGB_CHANN; channel++ )
	{
		zeroRGBHist.append(channelHistogram);
	}

	return zeroRGBHist;
}

// NOTE:
// - maybe we should use other charactrictic which will better describe our statistic?

// Transform statistic histogram to statistic histogram in percent
// @input:
// - QList< QList<unsigned int> > - unempty statistic histogram of some image
// @output:
// - empty QList< QList<unsigned int> > - failed to form statistic histogram in percent
// - QList< QList<unsigned int> > - statistic histogram in percent
QList<QList<double> > ImgHistogram::FormStatHistInPercent(const QList<QList<double> > &t_statHist)
{
	if ( true == t_statHist.isEmpty() )
	{
		qDebug() << "FormStatHistInPercent(): Error - invalid arguments";
		QList< QList<double> > empty;
		return empty;
	}

	QList< QList<double> > statHistInPercent;
	const int numOfHist = t_statHist.size();
	for ( int hist = 0; hist < numOfHist; hist++ )
	{
		double summOfAllValues = 0;
		const int sizeOfHist = t_statHist.at(hist).size();
		for ( int value = 0; value < sizeOfHist; value++ )
		{
			summOfAllValues += t_statHist[hist][value];
		}

		// Chesk if channel fromed by zero values
		if ( summOfAllValues < 1 )
		{
			summOfAllValues = 1;
		}

		// Transform to percent
		QList<double> channelHistInPercent;
		for( int value = 0; value < sizeOfHist; value++ )
		{
			double channelValue = t_statHist[hist][value];
			double valueInPercent = (channelValue * (double)MAX_PERCENT) / summOfAllValues;

			channelHistInPercent.append(valueInPercent);
		}

		statHistInPercent.append(channelHistInPercent);
	}

	return statHistInPercent;
}

// Test of forming image histogram
void ImgHistogram::TestRGBHist()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												 "Open target image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	Image testImg;
	testImg.LoadImg(imgName);

	QList< QList<double> > hist = RGBHistogram(testImg);
	if ( true == hist.isEmpty() )
	{
		qDebug() << "TestRGBHist(): Fail - no histogram";
		return;
	}

	QList<double> lumHist = LuminanceHistogram(testImg);
	if ( true == lumHist.isEmpty() )
	{
		qDebug() << "TestRGBHist(): Fail - no lum histogram";
		return;
	}
}
