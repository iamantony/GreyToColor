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

#include <QDebug>
#include "sourceimgpixels.h"
#include "./SERVICE/calculatorsko.h"
#include "./SERVICE/IMAGES/imghistogram.h"

SourceImgPixels::SourceImgPixels()
{

}

SourceImgPixels::~SourceImgPixels()
{

}

// Save all pixels from input QImage as custom pixels
// @input:
// - t_img - unnull image
// @output:
// - true - new image formed
// - false - failed to form pixels from image
bool SourceImgPixels::FormImgPixels(const QImage &t_img)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "FormImgPixels(): Error - invalid arguments";
		return false;
	}

	m_width = t_img.width();
	m_height = t_img.height();
	m_pixels.reserve(m_width * m_height);

	for ( unsigned int wdt = 0; wdt < m_width; ++wdt )
	{
		for ( unsigned int hgt = 0; hgt < m_height; ++hgt )
		{
			QRgb pixel = t_img.pixel(wdt, hgt);

			RGB rgbPixel(qRed(pixel),
						 qGreen(pixel),
						 qBlue(pixel) );

			ColorPixel *colorPix = new ColorPixel(&rgbPixel);
			m_pixels.push_back(colorPix);
		}
	}

	return true;
}

// Transform all image pixels from RGB color space to LAB
// @input:
// @output:
void SourceImgPixels::TransAllPixRGB2LAB()
{
	for ( unsigned int width = 0; width < m_width; ++width )
	{
		for ( unsigned int height = 0; height < m_height; ++height )
		{
			TransformPixRGB2LAB(width, height);
			CalcPixRelativeLum(width, height);
		}
	}
}

// Calc relative LAB luminance
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
void SourceImgPixels::CalcPixRelativeLum(const unsigned int &t_width,
										 const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixRelativeLum(): Error - invalid arguments";
		return;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	ColorPixel *pixel = (ColorPixel *)m_pixels[index];
	pixel->CalcRelativeLum();
}

// Get pixel relative luminance
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - double in range [0, 1] - pixels relative luminance
// - double < 0 - can't find such pixel
double SourceImgPixels::GetPixelsRelativeLum(const unsigned int &t_width,
											 const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsRelativeLum(): Error - invalid arguments";
		return ERROR;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	ColorPixel *pixel = (ColorPixel *)m_pixels[index];
	return pixel->GetRelativeLum();
}

// Calc for each pixel in image it's SKO
// @input:
// @output:
void SourceImgPixels::CalcPixelsSKO()
{
	for ( unsigned int wdt = 0; wdt < m_width; ++wdt )
	{
		for ( unsigned int hgt = 0; hgt < m_height; ++hgt )
		{
			CalcPixSKO(wdt, hgt);
		}
	}
}

// Calc for certain pixel in image it's SKO
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
void SourceImgPixels::CalcPixSKO(const unsigned int &t_width,
								 const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixSKO(): Error - invalid arguments";
		return;
	}

	std::vector<double> lumInMask = GetPixNeighborsRelLum(t_width,
														  t_height,
														  SKO_MASK_RECT_SIDE);

	if ( true == lumInMask.empty() )
	{
		qDebug() << "CalcPixSKO(): Error - no pixels in mask";
		return;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	ColorPixel *pixel = (ColorPixel *)m_pixels[index];
	double pixelLum = pixel->GetRelativeLum();

	CalculatorSKO calc;
	double pixelSKO = calc.PixelMaskSKO(pixelLum, lumInMask);
	if ( pixelSKO < 0 )
	{
		qDebug() << "CalcPixSKO(): Error - can't calc SKO for pixel" <<
					t_width << t_height;
		return;
	}

	pixel->SetSKO(pixelSKO);
}

// Get SKO of pixel with certain coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - ERROR - can't find such pixel
// - double - pixels SKO
double SourceImgPixels::GetPixelsSKO(const unsigned int &t_width,
									 const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsSKO(): Error - invalid arguments";
		return ERROR;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	ColorPixel *pixel = (ColorPixel *)m_pixels[index];
	return pixel->GetSKO();
}

// Calc for each pixel in image it's Entropy
// @input:
// @output:
void SourceImgPixels::CalcPixelsEntropy()
{
	for ( unsigned int wdt = 0; wdt < m_width; ++wdt )
	{
		for ( unsigned int hgt = 0; hgt < m_height; ++hgt )
		{
			CalcPixsEntropy(wdt, hgt);
		}
	}
}

// Calc for certain pixel in image it's entropy
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
void SourceImgPixels::CalcPixsEntropy(const unsigned int &t_width,
									  const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixsEntropy(): Error - invalid arguments";
		return;
	}

	std::vector<double> lumInMask = GetPixNeighborsRelLum(t_width,
														  t_height,
														  ENTROPY_MASK_RECT_SIDE);

	if ( true == lumInMask.empty() )
	{
		qDebug() << "CalcPixsEntropy(): Error - no neighbor pixels";
		return;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	ColorPixel *pixel = (ColorPixel *)m_pixels[index];
	double pixelLum = pixel->GetRelativeLum();
	lumInMask.push_back(pixelLum);

	ImgHistogram histogramer;
	std::vector<double> maskHist = histogramer.MaskRelLumHistogram(lumInMask);

	double pixelEntropy = 0;
	int existLumNum = 0;
	const int maskSize = lumInMask.size();
	const int numOfLumValues = maskHist.size();
	for ( int lum = 0; lum < numOfLumValues; lum++ )
	{
		if ( maskHist[lum] <= 0.0 )
		{
			continue;
		}

		double relativeHistValue = maskHist[lum] / maskSize;
		pixelEntropy -= relativeHistValue * log2(relativeHistValue);

		++existLumNum;
	}

	if ( pixelEntropy < RELATIVE_MIN )
	{
		qDebug() << "CalcPixsEntropy(): negative entropy =" << pixelEntropy;
		pixelEntropy = RELATIVE_MIN;
	}

	pixelEntropy /= existLumNum;
	pixel->SetEntropy(pixelEntropy);
}

// Get Entropy of pixel with certain coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - double - pixels entropy
double SourceImgPixels::GetPixelsEntropy(const unsigned int &t_width,
										 const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsEntropy(): Error - invalid arguments";
		return RELATIVE_MIN;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	const ColorPixel *pixel = (ColorPixel *)m_pixels[index];
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
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
void SourceImgPixels::CalcPixsSkewAndKurt(const unsigned int &t_width,
										  const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixsSkewAndKurt(): Error - invalid arguments";
		return;
	}

	std::vector<double> lumInMask = GetPixNeighborsRelLum(t_width,
														  t_height,
														  ENTROPY_MASK_RECT_SIDE);
	if ( true == lumInMask.empty() )
	{
		qDebug() << "CalcPixsSkewAndKurt(): Error - no neighbor pixels";
		return;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	ColorPixel *pixel = (ColorPixel *)m_pixels[index];
	double pixelLum = pixel->GetRelativeLum();
	lumInMask.push_back(pixelLum);

	ImgHistogram histogramer;
	std::vector<double> maskHist = histogramer.MaskRelLumHistogram(lumInMask);

	const int maskSize = lumInMask.size();
	std::vector<double> relMaskHist = CalcRelativeMaskHist(maskHist, maskSize);

	double mean = CalcMaskHistMean(relMaskHist);
	double variance = CalcMaskHistVariance(relMaskHist, mean);

	double skewness = 0.0;
	double kurtosis = 0.0;
	const unsigned int relMaskHistSize = relMaskHist.size();
	for ( unsigned int val = 0; val < relMaskHistSize; ++val )
	{
		if ( relMaskHist.at(val) <= 0.0 )
		{
			continue;
		}

		double lumDiff = val * RELATIVE_DIVIDER - mean;

		skewness += pow(lumDiff, 3.0) * relMaskHist[val];
		kurtosis += pow(lumDiff, 4.0) * relMaskHist[val];
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
// - t_hist - unempty mask histogram
// - t_maskSize - positive mask size
// @output:
// - std::vector<double> - mask histogram with relative values
// - empty std::vector<double> - failed to calc relative values
std::vector<double> SourceImgPixels::CalcRelativeMaskHist(const std::vector<double> &t_hist,
														  const int &t_maskSize)
{
	if ( (true == t_hist.empty()) || (t_maskSize <= 0) )
	{
		qDebug() << "CalcRelativeMaskHist(): Error - invalid arguments";
		return std::vector<double>();
	}

	std::vector<double> relHist;
	const int histSize = t_hist.size();
	for ( int val = 0; val < histSize; ++val )
	{
		double relValue = t_hist[val] / t_maskSize;
		relHist.push_back(relValue);
	}

	return relHist;
}

// Calc relative mask histogram mean value
// @input:
// - t_hist - unempty mask histogram
// @output:
// - double - mask histogram mean value
// - double < 0 - failed to calc mean
double SourceImgPixels::CalcMaskHistMean(const std::vector<double> &t_hist)
{
	if ( true == t_hist.empty() )
	{
		qDebug() << "CalcMaskHistMean(): Error - invalid arguments";
		return ERROR_FP;
	}

	double mean = 0.0;
	const int histSize = t_hist.size();
	for( int val = 0; val < histSize; ++val )
	{
		mean += val * RELATIVE_DIVIDER * t_hist[val];
	}

	return mean;
}

// Calc relative mask histogram variance value
// @input:
// - t_hist - unempty mask histogram
// - t_histMean - positive mask histogram mean value
// @output:
// - double - mask histogram variance value
// - double < 0 - failed to calc variance
double SourceImgPixels::CalcMaskHistVariance(const std::vector<double> &t_hist,
											 const double &t_histMean)
{
	if ( (true == t_hist.empty()) || (t_histMean < 0.0) )
	{
		qDebug() << "CalcMaskHistVariance(): Error - invalid arguments";
		return ERROR_FP;
	}

	double squareVariance = 0.0;
	const int histSize = t_hist.size();
	for( int val = 0; val < histSize; ++val )
	{
		double relLum = val * RELATIVE_DIVIDER;
		squareVariance += t_hist[val] * pow( relLum - t_histMean, 2 );
	}

	double variance = pow(squareVariance, 0.5);

	return variance;
}

// Get Skewness of pixel with certain coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - double - pixels Skewness
double SourceImgPixels::GetPixelsSkewness(const unsigned int &t_width,
										  const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsSkewness(): Error - invalid arguments";
		return RELATIVE_MIN;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	const ColorPixel *pixel = (ColorPixel *)m_pixels[index];
	return pixel->GetSkewness();
}

// Get Kurtosis of pixel with certain coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - double - pixels Kurtosis
double SourceImgPixels::GetPixelsKurtosis(const unsigned int &t_width,
										  const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsKurtosis(): Error - invalid arguments";
		return RELATIVE_MIN;
	}

	const unsigned int index = GetPixelIndex(t_width, t_height);
	const ColorPixel *pixel = (ColorPixel *)m_pixels[index];
	return pixel->GetKurtosis();
}

// Find among all pixels in image value of max relative luminance
// @input:
// @output:
// - double - positive found max relative luminance of images pixels
// - double < 0 - can't find max relative luminance
double SourceImgPixels::FindMaxRelLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMaxLum(): Error - no pixels";
		return ERROR_FP;
	}

	double maxLum = RELATIVE_MIN;
	ColorPixel *pixel = nullptr;
	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		pixel = (ColorPixel *)m_pixels[pix];
		double pixelLum = pixel->GetRelativeLum();
		if ( maxLum < pixelLum )
		{
			maxLum = pixelLum;
		}
	}

	return maxLum;
}

// Find among all pixels in image value of min relative luminance
// @input:
// @output:
// - double - positive found min relative luminance of images pixels
// - double < 0 - can't find min relative luminance
double SourceImgPixels::FindMinRelLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMinLum(): Error - no pixels";
		return ERROR_FP;
	}

	double minLum = RELATIVE_MAX;
	ColorPixel *pixel = nullptr;
	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		pixel = (ColorPixel *)m_pixels[pix];
		double pixelLum = pixel->GetRelativeLum();
		if ( pixelLum < minLum )
		{
			minLum = pixelLum;
		}
	}

	return minLum;
}

// Find average image relative luminance
// @input:
// @output:
// - double - positive found average relative luminance of images pixels
// - double < 0 - can't find average relative luminance
double SourceImgPixels::FindAverageRelLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindAverageLum(): Error - no pixels";
		return ERROR_FP;
	}

	double averageLum = 0.0;
	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		ColorPixel *pixel = (ColorPixel *)m_pixels[pix];
		averageLum += pixel->GetRelativeLum();
	}

	averageLum /= maxPixels;

	return averageLum;
}

// Find most common relative luminance value
// @input:
// @output:
// - double - positive found most common relative luminance of images pixels
// - double < 0 - can't find most common relative luminance
double SourceImgPixels::FindMostCommonRelLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMostCommonLum(): Error - no pixels";
		return ERROR_FP;
	}

	// Create zero mass for statistic
	const int numberOfLevels = (int)floor(RELATIVE_MAX / RELATIVE_DIVIDER + 0.5);
	std::vector<int> lumStatistic(numberOfLevels, 0);

	// Form statistic
	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		ColorPixel *pixel = (ColorPixel *)m_pixels[pix];
		double lumLvl = pixel->GetRelativeLum() / RELATIVE_DIVIDER;
		int lvlNum = (int)floor(lumLvl);

		++lumStatistic[lvlNum];
	}

	// Find number of most popular luminance level
	const int percentOffset = 0;
	const int lvlOffset = (numberOfLevels * percentOffset) / 100;
	int mostCommonLvl = 0;
	int maxNumInLvl = 0;
	for ( int lvl = lvlOffset; lvl < numberOfLevels - lvlOffset; ++lvl )
	{
		if ( maxNumInLvl < lumStatistic[lvl] )
		{
			maxNumInLvl = lumStatistic[lvl];
			mostCommonLvl = lvl;
		}
	}

	// Transform number of luminance level to relative LAB luminance value
	double mostCommonLum = mostCommonLvl * RELATIVE_DIVIDER;

	return mostCommonLum;
}

// Get list of relative luminances of neighbor pixels (to calc SKO, for example)
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// - t_maskRectSide - get size of rectangle in which we will search neighbor pixels
// @output:
// - QList<double> - luminances of neighbor pixels
// - empty QList<double> - don't have pixels
std::vector<double> SourceImgPixels::GetPixNeighborsRelLum(const unsigned int &t_width,
														   const unsigned int &t_height,
														   const unsigned int &t_maskRectSide) const
{
	if ( (false == IsPixelExist(t_width, t_height)) ||
		 (m_width <= t_maskRectSide) ||
		 (m_height <= t_maskRectSide) )
	{
		qDebug() << "GetPixNeighborsLum(): Error - invalid arguments";
		return std::vector<double>();
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
	std::vector<double> luminances;
	for ( unsigned int width = widthStart; width < widthEnd; ++width )
	{
		for ( unsigned int height = heightStart; height < heightEnd; ++height )
		{
			if ( (width == t_width) && (height == t_height) )
			{
				// We take luminance of neighbor pixels, so we don't interested in value of luminance of current
				// (central) pixel
				continue;
			}

			const unsigned int index = GetPixelIndex(t_width, t_height);
			ColorPixel *pixel = (ColorPixel *)m_pixels[index];
			double pixelLum = pixel->GetRelativeLum();
			luminances.push_back(pixelLum);
		}
	}

	return luminances;
}
