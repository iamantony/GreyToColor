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

#include "imghistogram.h"

ImgHistogram::ImgHistogram()
{

}

// Get image luminance histogram (in percent)
// @input:
// - Image - unnull image (color/grey)
// - int - size of histogram (power of 2, [0, 256])
// @output:
// - empty QList<double> - failed to form histogram
// - QList<double> - images luminance histogram
QList<double> ImgHistogram::RGBLumHistogram(const Image &t_img, const int t_size)
{
	if ( (true == t_img.IsNull()) || (false == CheckHistSize(t_size)) )
	{
		qDebug() << "RGBLumHistogram(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	ImgTransform imgTransformer;
	Image greyImg = imgTransformer.ToGrey(t_img);
	if ( true == greyImg.IsNull() )
	{
		qDebug() << "RGBLumHistogram(): Error - can't greyscale image";
		QList<double> empty;
		return empty;
	}

	QImage greyscaledImg = greyImg.GetImg();
	QList< QList<double> > lumHist = CalcRGBHistogram(greyscaledImg);
	if ( true == lumHist.isEmpty() )
	{
		qDebug() << "RGBLumHistogram(): Error - can't form luminance histogram";
		QList<double> empty;
		return empty;
	}

	QList< QList<double> > shrinkedHist = ShrinkHistogram(lumHist, t_size);
	if ( true == shrinkedHist.isEmpty() )
	{
		qDebug() << "RGBLumHistogram(): Error - can't shrink luminance histogram";
		QList<double> empty;
		return empty;
	}

	// All histograms of greyscaled image are the same. You can return any one.
	return shrinkedHist.at(Histogram::RED);
}

// Get image channels histogram (in percent)
// @input:
// - Image - unnull image (color/grey)
// - int - size of histogram (power of 2, [0, 256])
// @output:
// - empty QList< QList<double> > - failed to form RGB channels histogram
// - QList< QList<double> > - histograms of all image channels
QList< QList<double> > ImgHistogram::RGBHistogram(const Image &t_img, const int t_size)
{
	if ( (true == t_img.IsNull()) || (false == CheckHistSize(t_size)) )
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

	QList< QList<double> > shrinkHist = ShrinkHistogram(rgbHist, t_size);
	if ( true == shrinkHist.isEmpty() )
	{
		qDebug() << "RGBHistogram(): Error - can't shrink images' channels histogram";
		QList< QList<double> > empty;
		return empty;
	}

	return shrinkHist;
}

// Check histogram size
// @input:
// - int - size of histogram (power of 2, [0, 256])
// @output:
// - true - size is OK
// - false - size is not OK
bool ImgHistogram::CheckHistSize(const int &t_size)
{
	for ( int power = 0; power < 9; power++ )
	{
		int poweredTwo = pow(2, power);
		if ( t_size == poweredTwo )
		{
			return true;
		}
	}

	return false;
}

// Get RGB image channels histogram (in percent)
// @input:
// - QImage - unnull image (color/grey)
// @output:
// - empty QList< QList<double> > - failed to form RGB channels histogram
// - QList< QList<double> > - histograms of all images' channels
QList< QList<double> > ImgHistogram::CalcRGBHistogram(const QImage &t_img)
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
// - empty QList< QList<double> > - failed to form RGB channels histogram statistic
// - QList< QList<double> > - statistic histograms of all RGB images' channels
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
			rgbHistogram[Histogram::RED][redValue]++;

			if ( false == imgIsGrey )
			{
				int greenValue = qGreen(pixel);
				rgbHistogram[Histogram::GREEN][greenValue]++;

				int blueValue = qBlue(pixel);
				rgbHistogram[Histogram::BLUE][blueValue]++;
			}
		}
	}

	if ( true == imgIsGrey )
	{
		QList<double> redChannelHist = rgbHistogram.at(Histogram::RED);
		rgbHistogram.replace(Histogram::GREEN, redChannelHist);
		rgbHistogram.replace(Histogram::BLUE, redChannelHist);
	}

	return rgbHistogram;
}

// Get zero RGB histogram
// @input:
// @output:
// - QList< QList<double> > - zero RGB histograms
QList< QList<double> > ImgHistogram::FormZeroRGBHist()
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

// Transform statistic histogram to statistic histogram in percent
// @input:
// - QList< QList<unsigned int> > - unempty statistic histogram of some image
// @output:
// - empty QList< QList<double> > - failed to form statistic histogram in percent
// - QList< QList<double> > - statistic histogram in percent
QList< QList<double> > ImgHistogram::FormStatHistInPercent(const QList<QList<double> > &t_statHist)
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
			double valueInPercent = ( channelValue * (double)MAX_PERCENT ) / summOfAllValues;

			channelHistInPercent.append(valueInPercent);
		}

		statHistInPercent.append(channelHistInPercent);
	}

	return statHistInPercent;
}

// Shrink histogram
// @input:
// - QList<QList<double> > - unempty formed image histogram
// - int - new size of histograms (power of 2, [0, 256])
// @output:
// - empty QList< QList<double> > - failed to shrink RGB channels histogram
// - QList< QList<double> > - shrinked histograms of all image channels
QList< QList<double> > ImgHistogram::ShrinkHistogram(const QList< QList<double> > &t_hists, const int &t_newSize)
{
	if ( (true == t_hists.isEmpty()) || (false == CheckHistSize(t_newSize)) )
	{
		qDebug() << "ShrinkHistogram(): Error - invalid arguments";
		QList< QList<double> > empty;
		return empty;
	}

	const int shrinkFactor = t_hists.at(Histogram::RED).size() / t_newSize;
	if ( shrinkFactor <= 1 )
	{
		return t_hists;
	}

	QList< QList<double> > shrinkedHists;
	for (int hist = Histogram::RED; hist < Histogram::DEFAULT_LAST; hist++)
	{
		QList<double> channelHist;
		const int histSize = t_hists.at(hist).size();
		int valuesCounter = 0;
		double summ = 0;
		for (int val = 0; val < histSize; val++)
		{
			summ += t_hists.at(hist).at(val);
			valuesCounter++;
			if ( shrinkFactor == valuesCounter )
			{
				channelHist.append(summ);
				valuesCounter = 0;
				summ = 0;
			}
		}

		shrinkedHists.append(channelHist);
	}

	return shrinkedHists;
}

// Get images histogram of luminance L channel of LAB color space
// @input:
// - TargetImage - unnull Target image
// @output:
// - empty QList<double> - failed to form histogram
// - QList<double> - images luminance histogram
QList<double> ImgHistogram::LABLumHistogram(SourceImage *t_img)
{
	if ( false == t_img->HasImage() )
	{
		qDebug() << "LABLumHistogram(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	QList<double> lumHist = FormZeroLABLumHist();
	const unsigned int imgWdt = t_img->GetImageWidth();
	const unsigned int imgHgt = t_img->GetImageHeight();
	for ( unsigned int width = 0; width < imgWdt; width++ )
	{
		for( unsigned int height = 0; height < imgHgt; height++ )
		{
			double luminance = t_img->PixelChLum(width, height);
			int stepNum = (int)floor( luminance / LAB_LUM_HIST_DIVIDER );
			lumHist[stepNum]++;
		}
	}

	return lumHist;
}

// Get zero LAB histogram for channel L
// @input:
// @output:
// - QList<double> - zero LAB histograms
QList<double> ImgHistogram::FormZeroLABLumHist()
{
	QList<double> zeroLABLumHist;
	unsigned int numOfSteps = LAB_MAX_LUM / LAB_LUM_HIST_DIVIDER;
	for ( unsigned int step = 0; step < numOfSteps; step++ )
	{
		zeroLABLumHist.append(0.0);
	}

	return zeroLABLumHist;
}

// Get images histogram of relative LAB luminance
// @input:
// - TargetImage - unnull Target image
// @output:
// - empty QList<double> - failed to form histogram
// - QList<double> - images relative luminance histogram
QList<double> ImgHistogram::RelLumHistogram(SourceImage *t_img)
{
	if ( false == t_img->HasImage() )
	{
		qDebug() << "RelLumHistogram(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	QList<double> lumHist = FormZeroRelLumHist();

	const int maxRelLumStep = lumHist.size() -1;
	const unsigned int imgWdt = t_img->GetImageWidth();
	const unsigned int imgHgt = t_img->GetImageHeight();
	for ( unsigned int width = 0; width < imgWdt; width++ )
	{
		for( unsigned int height = 0; height < imgHgt; height++ )
		{
			double relLum = t_img->GetPixelsRelLum(width, height);
			double lumLvl = relLum / RELATIVE_DIVIDER;
			int stepNum = (int)floor(lumLvl);

			if ( maxRelLumStep < stepNum)
			{
				stepNum = maxRelLumStep;
			}

			++lumHist[stepNum];
		}
	}

	return lumHist;
}

// Get zero histogram for relative luminance
// @input:
// @output:
// - QList<double> - zero LAB histograms
QList<double> ImgHistogram::FormZeroRelLumHist()
{
	QList<double> zeroRelLumHist;
	unsigned int numOfSteps = (unsigned int)( RELATIVE_MAX / RELATIVE_DIVIDER );
	for ( unsigned int step = 0; step < numOfSteps; step++ )
	{
		zeroRelLumHist.append(0.0);
	}

	return zeroRelLumHist;
}

// Histogram for image mask (relative LAB luminance)
// @input:
// - t_mask - unempty image mask with LAB luminance values
// @output:
// - std::vector<double> - mask histogram
// - empty std::vector<double> - failed to form mask histogram
std::vector<double> ImgHistogram::MaskRelLumHistogram(const std::vector<double> &t_mask)
{
	if ( true == t_mask.empty() )
	{
		qDebug() << "MaskLumHistogram(): Error - invalid arguments";
		return std::vector<double>();
	}

	// TODO: use vector
	QList<double> lumHist = FormZeroRelLumHist();
	const int lumHistSize = lumHist.size();
	const unsigned int maskSize = t_mask.size();
	for ( unsigned int value = 0; value < maskSize; ++value )
	{
		int stepNum = (int)floor( t_mask[value] / RELATIVE_DIVIDER );
		if ( stepNum < 0 )
		{
			stepNum = 0;
		}
		else if ( lumHistSize <= stepNum )
		{
			stepNum = lumHistSize - 1;
		}

		++lumHist[stepNum];
	}

	return lumHist.toVector().toStdVector();
}
