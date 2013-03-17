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

#include "walshsimplecolorizator.h"

WalshSimpleColorizator::WalshSimpleColorizator()
{

}

// Start Colorization
// @input:
// - TargetImage - unnull unempty target image which we need to colorize
// - SourceImage - unnull unempty source image
// @output:
// - false - can't colorize
// - true - Target Image colorized
bool WalshSimpleColorizator::Colorize(TargetImage *t_targetImg, SourceImage *t_sourceImg)
{
	if ( (NULL == t_targetImg) ||
		 (NULL == t_sourceImg) ||
		 (false == t_targetImg->HasImage()) ||
		 (false == t_sourceImg->HasImage()) )
	{
		qDebug() << "Colorize(): Error - invalid arguments";
		return false;
	}

	m_target = t_targetImg;
	m_source = t_sourceImg;

	bool imagesPrepared = PrepareImages();
	if ( false == imagesPrepared )
	{
		qDebug() << "Colorize(): Error - can't prepare images for colorization";
		return false;
	}

	bool targetColorized = ColorizeImage();
	if ( false == targetColorized )
	{
		qDebug() << "Colorize(): Error - can't colorize Target image";
		return false;
	}

	bool paramsResored = PostColorization();
	if ( false == paramsResored )
	{
		qDebug() << "Colorize(): Error - can't restore images parameters";
		return false;
	}

	return true;
}

// Prepare images to colorization
// @input:
// @output:
bool WalshSimpleColorizator::PrepareImages()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) ||
		 (false == m_target->HasImage()) ||
		 (false == m_source->HasImage()) )
	{
		qDebug() << "PrepareImages(): Error - invalid arguments";
		return false;
	}

	m_target->SetPixelsUncoloured();

	m_target->TransformImgRGB2LAB();
	m_source->TransformImgRGB2LAB();

	const double targMaxLum = m_target->GetMaxLABLum();
	const double sourceMaxLum = m_source->GetMaxLABLum();
	const double scaleFactor = sourceMaxLum / targMaxLum;
	bool lumScaled = m_target->ScaleLABLum(scaleFactor);
	if ( false == lumScaled )
	{
		qDebug() << "PrepareImages(): Error - can't scale luminance of Target image";
		return false;
	}

	m_target->CalcPixelsSKO();
	m_source->CalcPixelsSKO();

	return true;
}

// Colorize Target image using color information from Source image
// @input:
// @output:
bool WalshSimpleColorizator::ColorizeImage()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) ||
		 (false == m_target->HasImage()) ||
		 (false == m_source->HasImage()) )
	{
		qDebug() << "ColorizeImage(): Error - invalid arguments";
		return false;
	}

	const unsigned int targetWdt = m_target->GetImageWidth();
	const unsigned int targetHgt = m_target->GetImageHeight();
	const unsigned int sourceWdt = m_source->GetImageWidth();
	const unsigned int sourceHgt = m_source->GetImageHeight();

	// Define number of attempts for each target pixel of searching similar pixel in source image
	const unsigned int pixelsInTargetImg = targetWdt * targetHgt;
	int numOfAttempts = NUM_OF_ATTEMPTS;
	if ( pixelsInTargetImg < NUM_OF_ATTEMPTS )
	{
		numOfAttempts = (int)pixelsInTargetImg;
	}

	// Values of best found pixels characteristics
	double bestDiffLum = DEFAULT_LUM;
	double bestDiffSKO = DEFAULT_SKO;
	unsigned int bestSourcePixWdt = 0;
	unsigned int bestSourcePixHgt = 0;

	// Targets pixel variables
	double targPixLum = DEFAULT_LUM;
	double targPixSKO = DEFAULT_SKO;

	// Source pixel variables
	unsigned int sourceRandWdt = 0;
	unsigned int sourceRandHgt = 0;
	double sourcePixLum = DEFAULT_LUM;
	double sourcePixSKO = DEFAULT_SKO;
	double sourceChA = 0;
	double sourceChB = 0;

	// Decision variables
	double diffLum = DEFAULT_LUM;
	double diffSKO = DEFAULT_SKO;

//	// For rand() statistic
//	QList< QList<double> > randStat = GetMassForStat(sourceWdt, sourceHgt);

	qDebug() << "Start colorization!";
	QElapsedTimer timer;
	timer.start();

	for ( unsigned int width = 0; width < targetWdt; width++ )
	{
		qDebug() << "ColorizeImage(): row =" << width;
		for ( unsigned int height = 0; height < targetHgt; height++ )
		{
			srand(time(NULL));

			// Reset best params
			bestDiffLum = DEFAULT_LUM;
			bestDiffSKO = DEFAULT_SKO;
			bestSourcePixWdt = 0;
			bestSourcePixHgt = 0;

			// Get target pixel params
			targPixLum = m_target->PixelChLum(width, height);
			targPixSKO = m_target->GetPixelsSKO(width, height);
			if ( (targPixLum <= NO_INFO) || (targPixSKO <= ERROR) )
			{
				qDebug() << "ColorizeImage(): Warning - failed to colorize pixel" << width << height;
				continue;
			}

			// Try to fins best similar source image pixel
			for ( int pix = 0; pix < numOfAttempts; pix++ )
			{
				sourceRandWdt = rand() % sourceWdt;
				sourceRandHgt = rand() % sourceHgt;

//				// Get rand() stat
//				randStat[sourceRandWdt][sourceRandHgt]++;

				sourcePixLum = m_source->PixelChLum(sourceRandWdt, sourceRandHgt);
				sourcePixSKO = m_source->GetPixelsSKO(sourceRandWdt, sourceRandHgt);

				diffLum = fabs( targPixLum - sourcePixLum );
				diffSKO = fabs( targPixSKO - sourcePixSKO );

				if ( ( (diffLum < bestDiffLum) && (diffSKO < (bestDiffSKO + SKO_TRESHOLD)) ) ||
					 ( (diffLum < (bestDiffLum + LUM_TRESHOLD)) && (diffSKO < bestDiffSKO) ) )
				{
					bestDiffLum = diffLum;
					bestDiffSKO = diffSKO;
					bestSourcePixWdt = sourceRandWdt;
					bestSourcePixHgt = sourceRandHgt;
				}
			}

			// Transfer color from Source pixel to Target pixel
			sourceChA = m_source->PixelChA(bestSourcePixWdt, bestSourcePixHgt);
			sourceChB = m_source->PixelChB(bestSourcePixWdt, bestSourcePixHgt);

			m_target->SetPixelChAB(width,
								   height,
								   sourceChA,
								   sourceChB);
		}
	}

	qDebug() << "Elapsed time in nanosec:" << timer.nsecsElapsed();
//	FormStatImage(randStat);

	return true;
}

// Restore images params if needed
// @input:
// @output:
bool WalshSimpleColorizator::PostColorization()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) ||
		 (false == m_target->HasImage()) ||
		 (false == m_source->HasImage()) )
	{
		qDebug() << "PostColorization(): Error - invalid arguments";
		return false;
	}

	m_target->UnScaleLABLum();
	return true;
}

// Create mass of zeros for statistic
QList< QList<double> > WalshSimpleColorizator::GetMassForStat(const unsigned int &t_width,
																	const unsigned int &t_height)
{
	QList<double> columnLine;
	for ( unsigned int col = 0; col < t_height; col++ )
	{
		columnLine.append(0);
	}

	QList< QList<double> > statMass;
	for ( unsigned int row = 0;  row < t_width; row++ )
	{
		statMass.append(columnLine);
	}

	return statMass;
}

// Form statistic image
void WalshSimpleColorizator::FormStatImage(const QList< QList<double> > &t_statMass)
{
	if ( true == t_statMass.isEmpty() )
	{
		qDebug() << "FormStatImage(): Error - invalid arguments";
		return;
	}

	int width = t_statMass.size();
	int height = t_statMass.at(0).size();

	// Find max value
	double maxValue = 0;
	for ( int wdt = 0; wdt < width; wdt++ )
	{
		for ( int hgt = 0; hgt < height; hgt++ )
		{
			if ( maxValue < t_statMass[wdt][hgt] )
			{
				maxValue = t_statMass[wdt][hgt];
			}
		}
	}

	// Scale all values and form list of RGB luminances
	QImage statImg(width, height, QImage::Format_RGB32);
	for ( int wdt = 0; wdt < width; wdt++ )
	{
		for ( int hgt = 0; hgt < height; hgt++ )
		{
			double scaledValue = t_statMass[wdt][hgt] / maxValue;
			int luminance = (int)floor( 255 * scaledValue + 0.5);
			if ( luminance < 0 )
			{
				luminance = 0;
			}
			else if ( 255 < luminance )
			{
				luminance = 255;
			}

			QRgb pixel = qRgb(luminance, luminance, luminance);
			statImg.setPixel(wdt, hgt, pixel);
		}
	}

	statImg.save("./TEST/rand_stat.png");
}
