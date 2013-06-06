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

#include "sourceimgpixels.h"
#include "./SERVICE/IMAGES/imghistogram.h"

SourceImgPixels::SourceImgPixels()
{

}

SourceImgPixels::~SourceImgPixels()
{
	Clear();
}

// Clear info about pixels (call this function before deleting object SourceImgPixels!)
// @input:
// @output:
void SourceImgPixels::Clear()
{
	const int pixWidth = m_pixels.size();
	for ( int width = pixWidth - 1; width >= 0; --width )
	{
		int pixHeight = m_pixels.at(width).size();
		for ( int height = pixHeight - 1; height >= 0; --height )
		{
			ColorPixel *pix = (ColorPixel *)m_pixels[width][height];
			if ( NULL != pix )
			{
				delete pix;
			}
		}

		m_pixels[width].clear();
	}

	m_pixels.clear();
}

// Save all pixels from input QImage as custom pixels
// @input:
// - QImage - unnull image
// @output:
bool SourceImgPixels::FormImgPixels(const QImage &t_img)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "FormImgPixels(): Error - invalid arguments";
		return false;
	}

	m_width = t_img.width();
	m_height = t_img.height();

	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
	{
		QList<Pixel *> columnOfPixels;

		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
		{
			QRgb pixel = t_img.pixel(wdt, hgt);

			RGB rgbPixel;
			bool colorOK = rgbPixel.SetColor(qRed(pixel), qGreen(pixel), qBlue(pixel));
			if ( false == colorOK )
			{
				qDebug() << "FormImgPixels(): pixel with coords (" << wdt << "," << hgt <<
							") has problems with RGB channels: invalid value";
			}

			ColorPixel *colorPix = new ColorPixel;
			colorPix->SetRGB(rgbPixel);

			columnOfPixels.append(colorPix);
		}

		m_pixels.append(columnOfPixels);
	}

	return true;
}

// Transform all image pixels from RGB color space to LAB
// @input:
// @output:
void SourceImgPixels::TransAllPixRGB2LAB()
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TransformPixRGB2LAB(width, height);
			CalcPixRelativeLum(width, height);
		}
	}
}

// Calc relative LAB luminance
// @input:
// @output:
void SourceImgPixels::CalcPixRelativeLum(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixRelativeLum(): Error - invalid arguments";
		return;
	}

	ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	pixel->CalcRelativeLum();
}

// Get pixel relative luminance
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - double in range [0, 1] - pixels relative luminance
// - double < 0 - can't find such pixel
double SourceImgPixels::GetPixelsRelativeLum(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsRelativeLum(): Error - invalid arguments";
		return ERROR;
	}

	const ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	return pixel->GetRelativeLum();
}

// Calc for each pixel in image it's SKO
// @input:
// @output:
void SourceImgPixels::CalcPixelsSKO()
{
	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
	{
		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
		{
			CalcPixSKO(wdt, hgt);
		}
	}
}

// Calc for certain pixel in image it's SKO
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void SourceImgPixels::CalcPixSKO(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixSKO(): Error - invalid arguments";
		return;
	}

	QList<double> lumInMask = GetPixNeighborsRelLum(t_width,
													t_height,
													SKO_MASK_RECT_SIDE);
	if ( true == lumInMask.isEmpty() )
	{
		qDebug() << "CalcPixSKO(): Error - no pixels in mask";
		return;
	}

	ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	double pixelLum = pixel->GetRelativeLum();

	CalculatorSKO calc;
	double pixelSKO = calc.PixelMaskSKO(pixelLum, lumInMask);
	if ( pixelSKO < 0 )
	{
		qDebug() << "CalcPixSKO(): Error - can't calc SKO for pixel" << t_width << t_height;
		return;
	}

	pixel->SetSKO(pixelSKO);
}

// Get SKO of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - ERROR - can't find such pixel
// - double - pixels SKO
double SourceImgPixels::GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsSKO(): Error - invalid arguments";
		return ERROR;
	}

	const ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	return pixel->GetSKO();
}

// Calc for each pixel in image it's Entropy
// @input:
// @output:
void SourceImgPixels::CalcPixelsEntropy()
{
	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
	{
		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
		{
			CalcPixsEntropy(wdt, hgt);
		}
	}
}

// Calc for certain pixel in image it's entropy
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void SourceImgPixels::CalcPixsEntropy(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixsEntropy(): Error - invalid arguments";
		return;
	}

	QList<double> lumInMask = GetPixNeighborsRelLum(t_width,
													t_height,
													ENTROPY_MASK_RECT_SIDE);
	if ( true == lumInMask.isEmpty() )
	{
		qDebug() << "CalcPixsEntropy(): Error - no neighbor pixels";
		return;
	}

	ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	double pixelLum = pixel->GetRelativeLum();
	lumInMask.append(pixelLum);

	ImgHistogram histogramer;
	QList<double> maskHist = histogramer.MaskRelLumHistogram(lumInMask);

	double pixelEntropy = 0;
	int existLumNum = 0;
	const int maskSize = lumInMask.size();
	const int numOfLumValues = maskHist.size();
	for ( int lum = 0; lum < numOfLumValues; lum++ )
	{
		if ( maskHist.at(lum) <= 0.0 )
		{
			continue;
		}

		double relativeHistValue = maskHist.at(lum) / maskSize;
		pixelEntropy -= relativeHistValue * log2(relativeHistValue);

		++existLumNum;
	}

	if ( pixelEntropy < RELATIVE_MIN )
	{
		qDebug() << "CalcPixsEntropy(): negative entropy =" << pixelEntropy;
		pixelEntropy = RELATIVE_MIN;
	}

	pixelEntropy /= existLumNum;

	ColorPixel *centralPixel = (ColorPixel *)m_pixels[t_width][t_height];
	centralPixel->SetEntropy(pixelEntropy);
}

// Get Entropy of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - double - pixels entropy
double SourceImgPixels::GetPixelsEntropy(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsEntropy(): Error - invalid arguments";
		return RELATIVE_MIN;
	}

	const ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	return pixel->GetEntropy();
}

// Calc for each pixel in image it's Skewness and Kurtosis
// @input:
// @output:
void SourceImgPixels::CalcPixelsSkewAndKurt()
{
	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
	{
		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
		{
			CalcPixsSkewAndKurt(wdt, hgt);
		}
	}
}

// Calc for certain pixel in image it's Skewness and Kurtosis
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void SourceImgPixels::CalcPixsSkewAndKurt(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixsSkewAndKurt(): Error - invalid arguments";
		return;
	}

	QList<double> lumInMask = GetPixNeighborsRelLum(t_width,
													t_height,
													ENTROPY_MASK_RECT_SIDE);
	if ( true == lumInMask.isEmpty() )
	{
		qDebug() << "CalcPixsSkewAndKurt(): Error - no neighbor pixels";
		return;
	}

	ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	double pixelLum = pixel->GetRelativeLum();
	lumInMask.append(pixelLum);

	ImgHistogram histogramer;
	QList<double> maskHist = histogramer.MaskRelLumHistogram(lumInMask);

	const int maskSize = lumInMask.size();
	QList<double> relMaskHist = CalcRelativeMaskHist(maskHist, maskSize);

	double mean = CalcMaskHistMean(relMaskHist);
	double variance = CalcMaskHistVariance(relMaskHist, mean);

	double skewness = 0.0;
	double kurtosis = 0.0;
	const int relMaskHistSize = relMaskHist.size();
	for ( int val = 0; val < relMaskHistSize; ++val )
	{
		if ( relMaskHist.at(val) <= 0.0 )
		{
			continue;
		}

		double lumDiff = val * RELATIVE_DIVIDER - mean;

		skewness += pow(lumDiff, 3.0) * relMaskHist.at(val);
		kurtosis += pow(lumDiff, 4.0) * relMaskHist.at(val);
	}

	skewness = pow(variance, -3.0) * skewness;
	kurtosis = pow(variance, -4.0) * kurtosis;

	// If you change mask rectangular size you will shoud change SKEW_OFFSET and KURT_OFFSET!
	if ( NAN == skewness )
	{
		skewness = 0.5;
	}
	else
	{
		skewness = ( skewness + SKEW_OFFSET ) / (2 * SKEW_OFFSET );
		if ( skewness < RELATIVE_MIN )
		{
			qDebug() << "min skewness =" << skewness;
			skewness = RELATIVE_MIN;
		}
		else if ( RELATIVE_MAX < skewness )
		{
			qDebug() << "max skewness =" << skewness;
			skewness = RELATIVE_MAX;
		}
	}

	if ( NAN == kurtosis )
	{
		kurtosis = 0.0;
	}
	else
	{
		kurtosis = ( kurtosis + KURT_OFFSET ) / ( 2 * KURT_OFFSET );
		if ( kurtosis < RELATIVE_MIN )
		{
			qDebug() << "min kurtosis =" << kurtosis;
			kurtosis = RELATIVE_MIN;
		}
		else if ( RELATIVE_MAX < kurtosis )
		{
			qDebug() << "max kurtosis =" << kurtosis;
			kurtosis = RELATIVE_MAX;
		}
	}

	pixel->SetSkewness(skewness);
	pixel->SetKurtosis(kurtosis);
}

// Calc relative mask histogram
// @input:
// - QList<double> - unempty mask histogram
// - int - positive mask size
// @output:
// - QList<double> - mask histogram with relative values
// - empty QList<double> - failed to calc relative values
QList<double> SourceImgPixels::CalcRelativeMaskHist(const QList<double> &t_hist, const int &t_maskSize)
{
	if ( (true == t_hist.isEmpty()) || (t_maskSize <= 0) )
	{
		qDebug() << "CalcRelativeMaskHist(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	QList<double> relHist;
	const int histSize = t_hist.size();
	for ( int val = 0; val < histSize; ++val )
	{
		double relValue = t_hist.at(val) / t_maskSize;
		relHist.append(relValue);
	}

	return relHist;
}

// Calc relative mask histogram mean value
// @input:
// - QList<double> - unempty mask histogram
// @output:
// - double - mask histogram mean value
// - double < 0 - failed to calc mean
double SourceImgPixels::CalcMaskHistMean(const QList<double> &t_hist)
{
	if ( true == t_hist.isEmpty() )
	{
		qDebug() << "CalcMaskHistMean(): Error - invalid arguments";
		return ERROR;
	}

	double mean = 0.0;
	const int histSize = t_hist.size();
	for( int val = 0; val < histSize; ++val )
	{
		mean += val * RELATIVE_DIVIDER * t_hist.at(val);
	}

	return mean;
}

// Calc relative mask histogram variance value
// @input:
// - QList<double> - unempty mask histogram
// - double - positive mask histogram mean value
// @output:
// - double - mask histogram variance value
// - double < 0 - failed to calc variance
double SourceImgPixels::CalcMaskHistVariance(const QList<double> &t_hist, const double &t_histMean)
{
	if ( (true == t_hist.isEmpty()) || (t_histMean < 0.0) )
	{
		qDebug() << "CalcMaskHistVariance(): Error - invalid arguments";
		return ERROR;
	}

	double squareVariance = 0.0;
	const int histSize = t_hist.size();
	for( int val = 0; val < histSize; ++val )
	{
		double relLum = val * RELATIVE_DIVIDER;
		squareVariance += t_hist.at(val) * pow( relLum - t_histMean, 2 );
	}

	double variance = pow(squareVariance, 0.5);

	return variance;
}

// Get Skewness of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - double - pixels Skewness
double SourceImgPixels::GetPixelsSkewness(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsSkewness(): Error - invalid arguments";
		return RELATIVE_MIN;
	}

	const ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	return pixel->GetSkewness();
}

// Get Kurtosis of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - double - pixels Kurtosis
double SourceImgPixels::GetPixelsKurtosis(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsKurtosis(): Error - invalid arguments";
		return RELATIVE_MIN;
	}

	const ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	return pixel->GetKurtosis();
}

// Find among all pixels in image value of max relative luminance
// @input:
// @output:
// - double - positive found max relative luminance of images pixels
// - ERROR - can't find max relative luminance
double SourceImgPixels::FindMaxRelLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMaxLum(): Error - no pixels";
		return ERROR;
	}

	double maxLum = RELATIVE_MIN;
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			ColorPixel *pixel = (ColorPixel *)m_pixels[width][height];
			double pixelLum = pixel->GetRelativeLum();
			if ( maxLum < pixelLum )
			{
				maxLum = pixelLum;
			}
		}
	}

	return maxLum;
}

// Find among all pixels in image value of min relative luminance
// @input:
// @output:
// - double - positive found min relative luminance of images pixels
// - ERROR - can't find min relative luminance
double SourceImgPixels::FindMinRelLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMinLum(): Error - no pixels";
		return ERROR;
	}

	double minLum = RELATIVE_MAX;
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			ColorPixel *pixel = (ColorPixel *)m_pixels[width][height];
			double pixelLum = pixel->GetRelativeLum();
			if ( pixelLum < minLum )
			{
				minLum = pixelLum;
			}
		}
	}

	return minLum;
}

// Find average image relative luminance
// @input:
// @output:
// - double - positive found average relative luminance of images pixels
// - ERROR - can't find average relative luminance
double SourceImgPixels::FindAverageRelLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindAverageLum(): Error - no pixels";
		return ERROR;
	}

	double averageLum = 0.0;
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			ColorPixel *pixel = (ColorPixel *)m_pixels[width][height];
			averageLum += pixel->GetRelativeLum();
		}
	}

	averageLum /= m_width * m_height;

	return averageLum;
}

// Find most common relative luminance value
// @input:
// @output:
// - double - positive found most common relative luminance of images pixels
// - ERROR - can't find most common relative luminance
double SourceImgPixels::FindMostCommonRelLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMostCommonLum(): Error - no pixels";
		return ERROR;
	}

	// Create zero mass for statistic
	const int numberOfLevels = RELATIVE_MAX / RELATIVE_DIVIDER;
	QList<int> lumStatistic;
	for ( int lumLvl = 0; lumLvl < numberOfLevels; lumLvl++ )
	{
		lumStatistic.append(0);
	}

	// Form statistic
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			ColorPixel *pixel = (ColorPixel *)m_pixels[width][height];
			double pixLum = pixel->GetRelativeLum();
			double lumLvl = pixLum / RELATIVE_DIVIDER;
			int lvlNum = (int)floor(lumLvl);

			++lumStatistic[lvlNum];
		}
	}

	// Find number of most popular luminance level
	const int percentOffset = 0;
	const int lvlOffset = (numberOfLevels * percentOffset) / 100;
	int mostCommonLvl = 0;
	int maxNumInLvl = 0;
	for ( int lvl = lvlOffset; lvl < numberOfLevels - lvlOffset; ++lvl )
	{
		if ( maxNumInLvl < lumStatistic.at(lvl) )
		{
			maxNumInLvl = lumStatistic.at(lvl);
			mostCommonLvl = lvl;
		}
	}

	// Transform number of luminance level to relative LAB luminance value
	double mostCommonLum = mostCommonLvl * RELATIVE_DIVIDER;

	return mostCommonLum;
}

// Get list of relative luminances of neighbor pixels (to calc SKO, for example)
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// - unsigned int - get size of rectangle in which we will search neighbor pixels
// @output:
// - unempy QList<double> - luminances of neighbor pixels
// - empty QList<double> - don't have pixels
QList<double> SourceImgPixels::GetPixNeighborsRelLum(const unsigned int &t_width,
													 const unsigned int &t_height,
													 const unsigned int &t_maskRectSide) const
{
	if ( (false == IsPixelExist(t_width, t_height)) ||
		 (m_width <= t_maskRectSide) ||
		 (m_height <= t_maskRectSide) )
	{
		qDebug() << "GetPixNeighborsLum(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	// t_maskRectSide is a length of side of a rect, which is form a mask. Central pixel in mask is pixel with
	// input coords. Other pixels are neighbors of central pixel.
	// Calc offset to get to extreme pixels in mask
	int offset = (int)t_maskRectSide / 2;
	int minWidthCoord = (int)t_width - offset;
	int minHeightCoord = (int)t_height - offset;

	// Calc position of extreme pixels
	unsigned int widthStart = (unsigned int)qMax( 0, minWidthCoord );
	unsigned int widthEnd = qMin( m_width, t_width + (unsigned int)offset + 1 );
	unsigned int heightStart = (unsigned int)qMax( 0, minHeightCoord );
	unsigned int heightEnd = qMin( m_height, t_height + (unsigned int)offset + 1 );
	QList<double> luminances;
	for ( unsigned int width = widthStart; width < widthEnd; width++ )
	{
		for ( unsigned int height = heightStart; height < heightEnd; height++ )
		{
			if ( (width == t_width) && (height == t_height) )
			{
				// We take luminance of neighbor pixels, so we don't interested in value of luminance of current
				// (central) pixel
				continue;
			}

			ColorPixel *pixel = (ColorPixel *)m_pixels[width][height];
			double pixelLum = pixel->GetRelativeLum();
			luminances.append(pixelLum);
		}
	}

	return luminances;
}

// Test functions
void SourceImgPixels::TestFunctionality()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												 "Open target image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	QImage image(imgName);
	bool imgFormed = FormImgPixels(image);
	if ( false == imgFormed )
	{
		qDebug() << "Fail: Can't form image";
		return;
	}

	TransAllPixRGB2LAB();

	qDebug() << "Max Lum:" << FindMaxRelLum();
	qDebug() << "Min Lum:" << FindMinRelLum();

	CalcPixelsSKO();

	qDebug() << "After calculating:";
	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
	{
		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
		{
			qDebug() << wdt << hgt << GetPixelsSKO(wdt, hgt);
		}
	}

	TransAllPixLAB2RGB();
}

// Find out what min and max values for skewness
void SourceImgPixels::TestFindMaxSkewness()
{
	const int numOfLumLvl = (int)( RELATIVE_MAX / RELATIVE_DIVIDER );
//	const int numPixels = 121;
//	int step = numOfLumLvl / numPixels;

	QList<double> relMaskHist;
//	int counter = 0;
	for ( int i = 0; i < numOfLumLvl; ++i )
	{
		if ( i == 500 )
		{
			relMaskHist.append(109.0 / 121.0);
		}
		else if ( i == 901 )
		{
			relMaskHist.append(10.0 / 121.0);
		}
		else if ( i == 499 )
		{
			relMaskHist.append(1.0 / 121.0);
		}
//		else if ( i == 3 )
//		{
//			relMaskHist.append(0.05);
//		}
		else
		{
			relMaskHist.append(0.0);
		}

//		++counter;
//		if ( step == counter )
//		{
//			counter = 0;
//			relMaskHist.append(1.0 / 121.0);
//		}
//		else
//		{
//			relMaskHist.append(0.0);
//		}
	}

	double mean = CalcMaskHistMean(relMaskHist);
	double variance = CalcMaskHistVariance(relMaskHist, mean);

	double skewness = 0.0;
	double kurtosis = 0.0;
	int existLumNum = 0;
	const int relMaskHistSize = relMaskHist.size();
	for ( int val = 0; val < relMaskHistSize; ++val )
	{
		if ( relMaskHist.at(val) <= 0.0 )
		{
			continue;
		}

		double lumDiff = val * RELATIVE_DIVIDER - mean;

		skewness += pow(lumDiff, 3.0) * relMaskHist.at(val);
		kurtosis += pow(lumDiff, 4.0) * relMaskHist.at(val);

		++existLumNum;
	}

	skewness = pow(variance, -3.0) * skewness;
	kurtosis = pow(variance, -4.0) * kurtosis;

	qDebug() << "skewness =" << skewness;
	qDebug() << "kurtosis =" << kurtosis;
}

// Save ime LAB luminance statistic
void SourceImgPixels::TestStatistic(const QList<int> t_stat) const
{
	QFile histFile;
	histFile.setFileName("./hist.csv");

	bool fileOpened = histFile.open(QIODevice::WriteOnly);
	if ( false == fileOpened )
	{
		qDebug() << "TestStatistic(): Error - can't open file!";
		return;
	}

	QTextStream streamToFile;
	streamToFile.setDevice(&histFile);

	const int numOfValues = t_stat.size();

	streamToFile << "sep = ;" << endl;
	streamToFile << "NUM;Rel_Lum;Pixels" << endl;
	for ( int i = 0; i < numOfValues; i++ )
	{
		double lumValue = i * RELATIVE_DIVIDER;
		streamToFile << i << ";" <<
						lumValue << ";" <<
						t_stat[i] <<
						endl;
	}

	histFile.close();
}
