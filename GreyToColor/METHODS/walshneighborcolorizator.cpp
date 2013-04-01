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

#include "walshneighborcolorizator.h"

WalshNeighborColorizator::WalshNeighborColorizator()
{

}

// Start Colorization
// @input:
// - TargetImage - unnull unempty target image which we need to colorize
// - SourceImage - unnull unempty source image
// @output:
// - false - can't colorize
// - true - Target Image colorized
bool WalshNeighborColorizator::Colorize(TargetImage *t_targetImg,
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
bool WalshNeighborColorizator::PrepareImages(const LumEqualization::Type &t_type)
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

	m_target->CalcPixelsSKO();
	m_source->CalcPixelsSKO();

	return true;
}

// Colorize Target image using color information from Source image
// @input:
// @output:
// - true - Target image colorized
// - false - failed to colorize Target image
bool WalshNeighborColorizator::ColorizeImage()
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

	qDebug() << "Start colorization!";
	QElapsedTimer timer;
	timer.start();

	for ( unsigned int width = 0; width < targetWdt; width++ )
	{
//		qDebug() << "ColorizeImage(): row =" << width;
		for ( unsigned int height = 0; height < targetHgt; height++ )
		{
			if ( true == m_target->IsPixColoured(width, height) )
			{
				continue;
			}

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
			for ( unsigned int pix = 0; pix < numOfAttempts; pix++ )
			{
				sourceRandWdt = rand() % sourceWdt;
				sourceRandHgt = rand() % sourceHgt;

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

			m_target->SetPixColoured(width, height);

			// Try to color coloured target pixels neighbor pixels by the same color
			ColorizeNeighbor(width, height);
		}
	}

	qDebug() << "Elapsed time in nanosec:" << timer.nsecsElapsed();

	return true;
}

// Try to colorize neighbor pixels by the same color
// @input:
// - unsigned int - start pixel width coord
// - unsigned int - start pixel height coord
// @output:
void WalshNeighborColorizator::ColorizeNeighbor(const unsigned int &t_startWidth, const unsigned int &t_startHeight)
{
	const unsigned int targetWdt = m_target->GetImageWidth();
	const unsigned int targetHgt = m_target->GetImageHeight();
	unsigned int targCurrWdt = t_startWidth;
	unsigned int targCurrHgt = t_startHeight;

	// Coords of next pixel to try to color
	double targHgtTry = 0;
	double targWdtTry = 0;

	// Params of current pixel
	double targPixLum = DEFAULT_LUM;
	double targPixSKO = DEFAULT_SKO;

	// Params of lower neighbor pixel
	double lowerTargPixLum = DEFAULT_LUM;
	double lowerTargPixSKO = DEFAULT_SKO;

	// Decision variables
	double lowerNeighborDiffLum = DEFAULT_LUM;
	double lowerNeighborDiffSKO = DEFAULT_SKO;

	// A and B channels of LAB color space
	double chA = 0;
	double chB = 0;

	// Coord of right neighbor pixel
	double targRightWdt = 0;

	// Params of right neighbor pixel
	double rightTargPixLum = DEFAULT_LUM;
	double rightTargPixSKO = DEFAULT_SKO;

	// Decision variables
	double rightNeighborDiffLum = DEFAULT_LUM;
	double rightNeighborDiffSKO = DEFAULT_SKO;

	// Try to color lower neighbor pixel
	targHgtTry = targCurrHgt + 1;
	while( (true == m_target->IsPixColoured(targCurrWdt, targCurrHgt)) &&
		   (targHgtTry < targetHgt) &&
		   (false == m_target->IsPixColoured(targCurrWdt, targHgtTry)) )
	{
		// Get characteristics of current pixel
		targPixLum = m_target->PixelChLum(targCurrWdt, targCurrHgt);
		targPixSKO = m_target->GetPixelsSKO(targCurrWdt, targCurrHgt);

		// Get characteristics of next lower pixel
		lowerTargPixLum = m_target->PixelChLum(targCurrWdt, targHgtTry);
		lowerTargPixSKO = m_target->GetPixelsSKO(targCurrWdt, targHgtTry);

		lowerNeighborDiffLum = fabs( targPixLum - lowerTargPixLum );
		lowerNeighborDiffSKO = fabs( targPixSKO - lowerTargPixSKO );
		if ( (lowerNeighborDiffLum < LUM_TRESHOLD) && (lowerNeighborDiffSKO < SKO_TRESHOLD) )
		{
			// If neighbor pixel has quite the same characteristics, apply to it the same color
			chA = m_target->PixelChA(targCurrWdt, targCurrHgt);
			chB = m_target->PixelChB(targCurrWdt, targCurrHgt);
			m_target->SetPixelChAB(targCurrWdt,
								   targHgtTry,
								   chA,
								   chB);

			m_target->SetPixColoured(targCurrWdt, targHgtTry);

			// Try to color neighbor right pixel
			targRightWdt = targCurrWdt;
			targWdtTry = targCurrWdt + 1;
			while( (true == m_target->IsPixColoured(targRightWdt, targHgtTry)) &&
				   (targWdtTry < targetWdt) &&
				   (false == m_target->IsPixColoured(targWdtTry, targHgtTry)) )
			{
				rightTargPixLum = m_target->PixelChLum(targWdtTry, targHgtTry);
				rightTargPixSKO = m_target->GetPixelsSKO(targWdtTry, targHgtTry);

				rightNeighborDiffLum = fabs( lowerTargPixLum - rightTargPixLum );
				rightNeighborDiffSKO = fabs( lowerTargPixSKO - rightTargPixSKO );
				if ( (rightNeighborDiffLum < LUM_TRESHOLD) && (rightNeighborDiffSKO < SKO_TRESHOLD) )
				{
					m_target->SetPixelChAB(targWdtTry,
										   targHgtTry,
										   chA,
										   chB);

					m_target->SetPixColoured(targWdtTry, targHgtTry);

					// Recursion!
					ColorizeNeighbor(targWdtTry, targHgtTry);
				}

				targRightWdt = targWdtTry;
				targWdtTry++;
			}
		}

		// Set this just checked pixel as current
		targCurrHgt = targHgtTry;
		targHgtTry++;
	}
}

// Restore images params if needed
// @input:
// @output:
// - true - images params restored
// - false - can't restore images parameters
bool WalshNeighborColorizator::PostColorization()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) ||
		 (false == m_target->HasImage()) ||
		 (false == m_source->HasImage()) )
	{
		qDebug() << "PostColorization(): Error - invalid arguments";
		return false;
	}

	m_target->RestoreLABLum();
	return true;
}
