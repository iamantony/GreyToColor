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

#include "wsentropycolorizator.h"

WSEntropyColorizator::WSEntropyColorizator()
{

}

// Start Colorization
// @input:
// - TargetImage - unnull unempty target image which we need to colorize
// - SourceImage - unnull unempty source image
// @output:
// - false - can't colorize
// - true - Target Image colorized
bool WSEntropyColorizator::Colorize(TargetImage *t_targetImg,
									SourceImage *t_sourceImg,
									const LumEqualization::Type &t_type)
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

	bool imagesPrepared = PrepareImages(t_type);
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
// - LumEqualization::Type - exist type of way to equalise luminance of the Target image to Source image
// @output:
// - true - images prepared
// - false - can't prepare images to colorization
bool WSEntropyColorizator::PrepareImages(const LumEqualization::Type &t_type)
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

	bool lumScaled = EquliseTargetImgLum(t_type);
	if ( false == lumScaled )
	{
		qDebug() << "PrepareImages(): Error - can't scale luminance of Target image";
		return false;
	}

	m_target->CalcPixelsEntropy();
	m_source->CalcPixelsEntropy();

	m_target->CalcPixelsSKO();
	m_source->CalcPixelsSKO();

	m_target->CalcPixelsSkewAndKurt();
	m_source->CalcPixelsSkewAndKurt();

	return true;
}

// Colorize Target image using color information from Source image
// @input:
// @output:
// - true - Target image colorized
// - false - failed to colorize Target image
bool WSEntropyColorizator::ColorizeImage()
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
	unsigned int numOfAttempts = NUM_OF_ATTEMPTS;
	if ( pixelsInTargetImg < NUM_OF_ATTEMPTS )
	{
		numOfAttempts = pixelsInTargetImg;
	}

	// Values of best found pixels characteristic
	double bestParamsDiff = DEFAULT_DIFF;
	unsigned int bestSourcePixWdt = 0;
	unsigned int bestSourcePixHgt = 0;

	// Sum of Targets pixel variables
	double targSumParams = MIN_SUMM;

	// Source pixel variables
	unsigned int sourceRandWdt = 0;
	unsigned int sourceRandHgt = 0;
	double sourceChA = 0;
	double sourceChB = 0;
	double sourceSumParams = MIN_SUMM;

	// Decision variables
	double diffParams = DEFAULT_DIFF;

	qDebug() << "Start colorization!";
	QElapsedTimer timer;
	timer.start();

	srand(time(NULL));

	for ( unsigned int width = 0; width < targetWdt; ++width )
	{
//		qDebug() << "ColorizeImage(): row =" << width;
		for ( unsigned int height = 0; height < targetHgt; ++height )
		{
			// Reset best params
			bestParamsDiff = DEFAULT_DIFF;
			bestSourcePixWdt = 0;
			bestSourcePixHgt = 0;


			// Get target pixel params
			targSumParams = MIN_SUMM;
			targSumParams += m_target->GetPixelsRelLum(width, height);
			targSumParams += m_target->GetPixelsSKO(width, height);
			targSumParams += m_target->GetPixelsEntropy(width, height);
			targSumParams += m_target->GetPixelsSkewness(width, height);
			targSumParams += m_target->GetPixelsKurtosis(width, height);

			// Try to find best similar source image pixel
			for ( unsigned int pix = 0; pix < numOfAttempts; ++pix )
			{
				sourceRandWdt = rand() % sourceWdt;
				sourceRandHgt = rand() % sourceHgt;

				sourceSumParams = MIN_SUMM;
				sourceSumParams += m_source->GetPixelsRelLum(sourceRandWdt, sourceRandHgt);
				sourceSumParams += m_source->GetPixelsSKO(sourceRandWdt, sourceRandHgt);
				sourceSumParams += m_source->GetPixelsEntropy(sourceRandWdt, sourceRandHgt);
				sourceSumParams += m_source->GetPixelsSkewness(sourceRandWdt, sourceRandHgt);
				sourceSumParams += m_source->GetPixelsKurtosis(sourceRandWdt, sourceRandHgt);

				diffParams = fabs(targSumParams - sourceSumParams);
				if ( diffParams < bestParamsDiff )
				{
					bestParamsDiff = diffParams;
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

	return true;
}

// Restore images params if needed
// @input:
// @output:
// - true - images params restored
// - false - can't restore images parameters
bool WSEntropyColorizator::PostColorization()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) ||
		 (false == m_target->HasImage()) ||
		 (false == m_source->HasImage()) )
	{
		qDebug() << "PostColorization(): Error - invalid arguments";
		return false;
	}

	m_target->RestoreLABRelLum();
	return true;
}
