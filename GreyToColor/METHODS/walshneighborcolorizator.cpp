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
bool WalshNeighborColorizator::Colorize(TargetImage *t_targetImg, SourceImage *t_sourceImg)
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
bool WalshNeighborColorizator::PrepareImages()
{
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

	for ( unsigned int width = 0; width < targetWdt; width++ )
	{
		qDebug() << "ColorizeImage(): row =" << width;
		for ( unsigned int height = 0; height < targetHgt; height++ )
		{
			if ( true == m_target->IsPixColoured(width, height) )
			{
				continue;
			}

			srand(time(NULL));

			double bestDiffLum = DEFAULT_LUM;
			double bestDiffSKO = DEFAULT_SKO;
			unsigned int bestSourcePixWdt = 0;
			unsigned int bestSourcePixHgt = 0;

			double targPixLum = m_target->PixelChLum(width, height);
			double targPixSKO = m_target->GetPixelsSKO(width, height);
			if ( (targPixLum <= NO_INFO) || (targPixSKO <= ERROR) )
			{
				qDebug() << "ColorizeImage(): Warning - failed to colorize pixel" << width << height;
				continue;
			}

			for ( int pix = 0; pix < NUM_OF_ATTEMPTS; pix++ )
			{
				const unsigned int sourceRandWdt = rand() % sourceWdt;
				const unsigned int sourceRandHgt = rand() % sourceHgt;

				const double sourcePixLum = m_source->PixelChLum(sourceRandWdt, sourceRandHgt);
				const double sourcePixSKO = m_source->GetPixelsSKO(sourceRandWdt, sourceRandHgt);

				const double diffLum = fabs( targPixLum - sourcePixLum );
				const double diffSKO = fabs( targPixSKO - sourcePixSKO );

				if ( ( (diffLum < bestDiffLum) && (diffSKO < (bestDiffSKO + SKO_TRESHOLD)) ) ||
					 ( (diffLum < (bestDiffLum + LUM_TRESHOLD)) && (diffSKO < bestDiffSKO) ) )
				{
					bestDiffLum = diffLum;
					bestDiffSKO = diffSKO;
					bestSourcePixWdt = sourceRandWdt;
					bestSourcePixHgt = sourceRandHgt;
				}
			}

			double sourceChA = m_source->PixelChA(bestSourcePixWdt, bestSourcePixHgt);
			double sourceChB = m_source->PixelChB(bestSourcePixWdt, bestSourcePixHgt);
			m_target->SetPixelChAB(width,
								   height,
								   sourceChA,
								   sourceChB);

			m_target->SetPixColoured(width, height);

			unsigned int referenceTargWdt = width;
			unsigned int referenceTargHgt = height;
			// Lets check is pixel under us has same characteristics
			while ( (true == m_target->IsPixColoured(width, referenceTargHgt)) &&
					(referenceTargHgt + 1 < targetHgt) )
			{
				targPixLum = m_target->PixelChLum(width, referenceTargHgt);
				targPixSKO = m_target->GetPixelsSKO(width, referenceTargHgt);
				double lowerTargPixLum = m_target->PixelChLum(width, referenceTargHgt + 1);
				double lowerTargPixSKO = m_target->GetPixelsSKO(width, referenceTargHgt + 1);

				double lowerNeighborDiffLum = fabs( targPixLum - lowerTargPixLum );
				double lowerNeighborDiffSKO = fabs( targPixSKO - lowerTargPixSKO );
				if ( (lowerNeighborDiffLum < LUM_TRESHOLD) && (lowerNeighborDiffSKO < SKO_TRESHOLD) )
				{
					sourceChA = m_source->PixelChA(width, referenceTargHgt);
					sourceChB = m_source->PixelChB(width, referenceTargHgt);
					m_target->SetPixelChAB(width,
										   referenceTargHgt + 1,
										   sourceChA,
										   sourceChB);

					m_target->SetPixColoured(width, referenceTargHgt + 1);
				}


				referenceTargHgt++;
			}
		}
	}


//	int targWidth = m_imgTarget->GetImgWidth();
//	int targHeight = m_imgTarget->GetImgHeight();

//	int origWidth = m_imgOriginal->GetImgWidth();
//	int origHeight = m_imgOriginal->GetImgHeight();

//	double bestLum, bestSKO;
//	double nextTargPixLum, nextTargPixSKO, targPixLum, targPixSKO, origLum, origSKO, diffLum, diffSKO;
//	double origA, origB;
//	int x, y, wRand, hRand, nextX, nextY;

//	for (int i = 0; i < targWidth; i++)
//	{
//		qDebug() << "row =" << i;
//		for (int j = 0; j < targHeight; j++)
//		{
//			if ( true == m_imgTarget->PixelHasColor(i, j) )
//			{
//				continue;
//			}

//			srand(time(NULL));

//			bestLum = 1000;
//			bestSKO = 1000;
//			x = 0;
//			y = 0;

//			targPixLum = m_imgTarget->PixelLum(i, j);
//			targPixSKO = m_imgTarget->PixelSKO(i, j);

//			for (int k = 0; k < 400; k++)
//			{
//				wRand = rand()%origWidth;
//				hRand = rand()%origHeight;

//				origLum = m_imgOriginal->PixelLum(wRand, hRand);
//				origSKO = m_imgOriginal->PixelSKO(wRand, hRand);

//				diffLum = fabs(targPixLum - origLum);
//				diffSKO = fabs(targPixSKO - origSKO);

//				if ((diffLum < bestLum && diffSKO < (bestSKO + SKO_TRESHOLD)) ||
//						(diffLum < (bestLum + LUMINANCE_TRESHOLD) && diffSKO < bestSKO))
//				{
//					bestLum = diffLum;
//					bestSKO = diffSKO;
//					x = wRand;
//					y = hRand;
//				}
//			}

//			origA = m_imgOriginal->PixelChA(x, y);
//			origB = m_imgOriginal->PixelChB(x, y);
//			m_imgTarget->SetPixelChA(i, j, origA);
//			m_imgTarget->SetPixelChB(i, j, origB);
//			m_imgTarget->SetPixelHasColor(i, j);

//			nextX = i;
//			nextY = j;

//			while ( (true == m_imgTarget->PixelHasColor(nextX, j)) && (nextX + 1 < targWidth) )
//			{
//				targPixLum = m_imgTarget->PixelLum(nextX, j);
//				targPixSKO = m_imgTarget->PixelSKO(nextX, j);
//				nextTargPixLum = m_imgTarget->PixelLum(nextX + 1, j);
//				nextTargPixSKO = m_imgTarget->PixelSKO(nextX + 1, j);

//				double neighborXDiffLum = fabs( nextTargPixLum - targPixLum );
//				double neighborXDiffSKO = fabs( nextTargPixSKO - targPixSKO );
//				if ((neighborXDiffLum < LUMINANCE_TRESHOLD) && (neighborXDiffSKO < SKO_TRESHOLD))
//				{
//					origA = m_imgOriginal->PixelChA(nextX, j);
//					origB = m_imgOriginal->PixelChB(nextX, j);
//					m_imgTarget->SetPixelChA(nextX + 1, j, origA);
//					m_imgTarget->SetPixelChB(nextX + 1, j, origB);
//					m_imgTarget->SetPixelHasColor(nextX + 1, j);

//					while ( (true == m_imgTarget->PixelHasColor(nextX + 1, nextY)) && (nextY + 1 < targHeight) )
//					{
//						targPixLum = m_imgTarget->PixelLum(nextX + 1, nextY);
//						targPixSKO = m_imgTarget->PixelSKO(nextX + 1, nextY);
//						nextTargPixLum = m_imgTarget->PixelLum(nextX + 1, nextY + 1);
//						nextTargPixSKO = m_imgTarget->PixelSKO(nextX + 1, nextY + 1);

//						double neighborYDiffLum = fabs( nextTargPixLum - targPixLum );
//						double neighborYDiffSKO = fabs(nextTargPixSKO - targPixSKO );
//						if ((neighborYDiffLum < LUMINANCE_TRESHOLD) && (neighborYDiffSKO < SKO_TRESHOLD))
//						{
//							origA = m_imgOriginal->PixelChA(nextX + 1, nextY);
//							origB = m_imgOriginal->PixelChB(nextX + 1, nextY);
//							m_imgTarget->SetPixelChA(nextX + 1, nextY + 1, origA);
//							m_imgTarget->SetPixelChB(nextX + 1, nextY + 1, origB);
//							m_imgTarget->SetPixelHasColor(nextX + 1, nextY + 1);
//						}
//						nextY++;
//					}
//					nextY = j;
//				}
//				nextX++;
//			}
//		}
//	}

	return true;
}

// Try to colorize neighbor pixels by the same color
void WalshNeighborColorizator::ColorizeNeighbor(const unsigned int &t_startWidth, const unsigned int &t_startHeight)
{
	const unsigned int targetWdt = m_target->GetImageWidth();
	const unsigned int targetHgt = m_target->GetImageHeight();
	unsigned int targCurrWdt = t_startWidth;
	unsigned int targCurrHgt = t_startHeight;

	while( (true == m_target->IsPixColoured(targCurrWdt, targCurrHgt)) &&
		  (targCurrHgt + 1 < targetHgt) )
	{
		// Get characteristics of current pixel
		double targPixLum = m_target->PixelChLum(targCurrWdt, targCurrHgt);
		double targPixSKO = m_target->GetPixelsSKO(targCurrWdt, targCurrHgt);
		// Get characteristics of next lower pixel
		double lowerTargPixLum = m_target->PixelChLum(targCurrWdt, targCurrHgt + 1);
		double lowerTargPixSKO = m_target->GetPixelsSKO(targCurrWdt, targCurrHgt + 1);

		double lowerNeighborDiffLum = fabs( targPixLum - lowerTargPixLum );
		double lowerNeighborDiffSKO = fabs( targPixSKO - lowerTargPixSKO );
		if ( (lowerNeighborDiffLum < LUM_TRESHOLD) && (lowerNeighborDiffSKO < SKO_TRESHOLD) )
		{
			double chA = m_target->PixelChA(targCurrWdt, targCurrHgt);
			double chB = m_target->PixelChB(targCurrWdt, targCurrHgt);
			m_target->SetPixelChAB(targCurrWdt,
								   targCurrHgt + 1,
								   chA,
								   chB);

			m_target->SetPixColoured(targCurrWdt, targCurrHgt + 1);

			while( (true == m_target->IsPixColoured(targCurrWdt, targCurrHgt + 1)) &&
				  (targCurrWdt + 1 < targetWdt) )
			{
				// Get characteristics of pixel from the right sight of lower pixel
				double rightTargPixLum = m_target->PixelChLum(targCurrWdt + 1, targCurrHgt + 1);
				double rightTargPixSKO = m_target->GetPixelsSKO(targCurrWdt + 1, targCurrHgt + 1);

				double rightNeighborDiffLum = fabs( lowerTargPixLum - rightTargPixLum );
				double rightNeighborDiffSKO = fabs( lowerTargPixSKO - rightTargPixSKO );
				if ( (rightNeighborDiffLum < LUM_TRESHOLD) && (rightNeighborDiffSKO < SKO_TRESHOLD) )
				{
					m_target->SetPixelChAB(targCurrWdt + 1,
										   targCurrHgt + 1,
										   chA,
										   chB);

					m_target->SetPixColoured(targCurrWdt + 1, targCurrHgt + 1);

					// Recursion!
					ColorizeNeighbor(targCurrWdt + 1, targCurrHgt + 1);
				}

				targCurrWdt++;
			}
		}

		targCurrHgt++;
	}
}

// Restore images params if needed
// @input:
// @output:
bool WalshNeighborColorizator::PostColorization()
{
	m_target->UnScaleLABLum();
	return true;
}
