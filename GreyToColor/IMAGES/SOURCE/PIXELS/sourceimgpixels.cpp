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
		qDebug() << "CalcPixsEntropy(): Error - no pixels - no SKO";
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
// - NULL - can't find such pixel
// - double - pixels entropy
double SourceImgPixels::GetPixelsEntropy(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsEntropy(): Error - invalid arguments";
		return 0;
	}

	const ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	return pixel->GetEntropy();
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

	double minLum = DEFAULT_MIN_LAB_LUM;
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

	double averageLum = DEFAULT_MIN_LAB_LUM;
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
	const int numberOfLevels = RELATIVE_MAX / LAB_LUM_HIST_DIVIDER;
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
			double lumLvl = pixLum / LAB_LUM_HIST_DIVIDER;
			int lvlNum = (int)floor(lumLvl);

			lumStatistic[lvlNum]++;
		}
	}

	// Find number of most popular luminance level
	int mostCommonLvl = 0;
	int maxNumInLvl = 0;
	for ( int lvl = 0; lvl < numberOfLevels; lvl++ )
	{
		if ( maxNumInLvl < lumStatistic.at(lvl) )
		{
			maxNumInLvl = lumStatistic.at(lvl);
			mostCommonLvl = lvl;
		}
	}

	// Transform number of luminance level to relative LAB luminance value
	double mostCommonLum = mostCommonLvl * LAB_LUM_HIST_DIVIDER;

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
