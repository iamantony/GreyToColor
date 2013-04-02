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

#include "wslookuptablecolorizator.h"

WSLookUpTableColorizator::WSLookUpTableColorizator()
{

}

// Start Colorization
// @input:
// - TargetImage - unnull unempty target image which we need to colorize
// - SourceImage - unnull unempty source image
// @output:
// - false - can't colorize
// - true - Target Image colorized
bool WSLookUpTableColorizator::Colorize(TargetImage *t_targetImg,
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
bool WSLookUpTableColorizator::PrepareImages(const LumEqualization::Type &t_type)
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

	bool tableFormed = FormLookUpTable();
	if ( false == tableFormed )
	{
		qDebug() << "PrepareImages(): Error - can't form look up table";
		return false;
	}

	return true;
}

// Form look up table on Source image basis
// @input:
// @output:
// - true - look up table formed
// - false - can't form table
bool WSLookUpTableColorizator::FormLookUpTable()
{
	if ( (NULL == m_source) || (false == m_source->HasImage()) )
	{
		qDebug() << "FormLookUpTable(): Error - no source image";
		return false;
	}

	FormEmptyLookUpTable();
	bool tabledFilled = FillLookUpTable();
	if ( false == tabledFilled )
	{
		qDebug() << "FormLookUpTable(): Error - can't fill look up table";
		return false;
	}

	return true;
}

// Form empty look up table
// @input:
// @output:
void WSLookUpTableColorizator::FormEmptyLookUpTable()
{
	QList<unsigned int> lumValues = FormLumValues();
	QList<unsigned int> skoValues = FormSKOValues();

	const int lumValNum = lumValues.size();
	const int skoValNum = skoValues.size();
	for ( int lum = 0; lum < lumValNum; lum++ )
	{
		LookUpSKO skoLookUp;
		for ( int sko = 0; sko < skoValNum; sko++ )
		{
			PixCoords empty;
			skoLookUp.insert(skoValues.at(sko), empty);
		}

		m_lookUpTable.insert(lumValues.at(lum), skoLookUp);
	}
}

// Form list of all posible LAB luminances
// @input:
// @output:
// - QList<unsigned int> - possible values of LAB luminance
QList<unsigned int> WSLookUpTableColorizator::FormLumValues()
{
	QList<unsigned int> lumValues;
	const unsigned int numOfSteps = LAB_MAX_LUM / LAB_LUM_HIST_DIVIDER;
	for ( unsigned  int step = 0; step <= numOfSteps; step++ )
	{
		lumValues.append(step);
	}

	return lumValues;
}

// Form list of all possible SKO values
// @input:
// @output:
// - QList<unsigned int> - possible values of LAB luminance
QList<unsigned int> WSLookUpTableColorizator::FormSKOValues()
{
	const double squareRectSide = pow( MASK_RECT_SIDE_LENGTH, 2 );
	const double squareLum = pow( LAB_MAX_LUM, 2 );
	const double maxSKO = sqrt( (squareRectSide - 1) * squareLum / MASK_RECT_SIDE_LENGTH );
	const unsigned int numOfSteps = maxSKO / SKO_DIVIDER;

	QList<unsigned int> skoValues;
	for ( unsigned  int step = 0; step <= numOfSteps; step++ )
	{
		skoValues.append(step);
	}

	return skoValues;
}

// Fill look up table
// @input:
// @output:
// - true - images params restored
// - false - can't restore images parameters
bool WSLookUpTableColorizator::FillLookUpTable()
{
	if ( (NULL == m_source) || (false == m_source->HasImage()) )
	{
		qDebug() << "FillLookUpTable(): Error - no source image";
		return false;
	}

	const unsigned int sourceWdt = m_source->GetImageWidth();
	const unsigned int sourceHgt = m_source->GetImageHeight();
	for ( unsigned int width = 0; width < sourceWdt; width++ )
	{
		for ( unsigned int height = 0; height < sourceHgt; height++ )
		{
			double pixLum = m_source->PixelChLum(width, height);
			unsigned int lumStepNum = (unsigned int)floor( pixLum / LAB_LUM_HIST_DIVIDER );

			double pixSKO = m_source->GetPixelsSKO(width, height);
			unsigned int skoStepNum = (unsigned int)floor( pixSKO / SKO_DIVIDER );

			Coord currPixCoords(width, height);
			m_lookUpTable[lumStepNum][skoStepNum].append(currPixCoords);
		}
	}

	return true;
}

// Colorize Target image using color information from Source image
// @input:
// @output:
// - true - Target image colorized
// - false - failed to colorize Target image
bool WSLookUpTableColorizator::ColorizeImage()
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

	// Target image pixel variables
	double targPixLum = DEFAULT_LUM;
	double targPixSKO = DEFAULT_SKO;
	unsigned int lumStepNum = 0;
	unsigned int skoStepNum = 0;

	// Decision variables
	double diffLum = DEFAULT_LUM;
	double diffSKO = DEFAULT_SKO;

	// Values of best found pixels characteristics
	double bestDiffLum = DEFAULT_LUM;
	double bestDiffSKO = DEFAULT_SKO;
	unsigned int bestSourcePixWdt = 0;
	unsigned int bestSourcePixHgt = 0;

	// Source pixel variables
	unsigned int sourceWdt = 0;
	unsigned int sourceHgt = 0;
	double sourcePixLum = DEFAULT_LUM;
	double sourcePixSKO = DEFAULT_SKO;
	double sourceChA = 0;
	double sourceChB = 0;

	PixCoords sourceImgCoords;

	// Offset for search in look up table
	const unsigned int offset = 1;

	int found = 0;

	qDebug() << "Start colorization!";
	QElapsedTimer timer;
	timer.start();

	for ( unsigned int width = 0; width < targetWdt; width++ )
	{
		qDebug() << "width =" << width;
		for ( unsigned int height = 0; height < targetHgt; height++ )
		{
			// Get target pixel params
			targPixLum = m_target->PixelChLum(width, height);
			targPixSKO = m_target->GetPixelsSKO(width, height);
			if ( (targPixLum <= NO_INFO) || (targPixSKO <= ERROR) )
			{
				qDebug() << "FinishColorization(): Warning - failed to colorize pixel" << width << height;
				continue;
			}

			lumStepNum = (unsigned int)floor( targPixLum / LAB_LUM_HIST_DIVIDER );
			skoStepNum = (unsigned int)floor( targPixSKO / SKO_DIVIDER );

			sourceImgCoords = m_lookUpTable[lumStepNum][skoStepNum];

			if ( true == sourceImgCoords.isEmpty() )
			{
				// Try to find similar pixel with quite similar params
				for ( unsigned int lum = lumStepNum - offset; lum <= lumStepNum + offset; lum++ )
				{
					for ( unsigned int sko = skoStepNum - offset; sko <= skoStepNum + offset; sko++ )
					{
						sourceImgCoords = m_lookUpTable[lum][sko];
						if ( false == sourceImgCoords.isEmpty() )
						{
							break;
						}
					}
				}
			}

			if ( true == sourceImgCoords.isEmpty() )
			{
				continue;
			}

			found++;

			// Reset best params
			bestDiffLum = DEFAULT_LUM;
			bestDiffSKO = DEFAULT_SKO;
			bestSourcePixWdt = 0;
			bestSourcePixHgt = 0;

			// Let's find most similar pixel of Source image
			const int coordsListSize = sourceImgCoords.size();
			for ( int coord = 0; coord < coordsListSize; coord++ )
			{
				sourceWdt = sourceImgCoords.at(coord).first;
				sourceHgt = sourceImgCoords.at(coord).second;

				sourcePixLum = m_source->PixelChLum(sourceWdt, sourceHgt);
				sourcePixSKO = m_source->GetPixelsSKO(sourceWdt, sourceHgt);

				diffLum = fabs( targPixLum - sourcePixLum );
				diffSKO = fabs( targPixSKO - sourcePixSKO );

				if ( ( (diffLum < bestDiffLum) && (diffSKO < (bestDiffSKO + SKO_TRESHOLD)) ) ||
					 ( (diffLum < (bestDiffLum + LUM_TRESHOLD)) && (diffSKO < bestDiffSKO) ) )
				{
					bestDiffLum = diffLum;
					bestDiffSKO = diffSKO;
					bestSourcePixWdt = sourceWdt;
					bestSourcePixHgt = sourceHgt;
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
		}
	}

	bool colorizationFinished = FinishColorization();
	if ( false == colorizationFinished )
	{
		qDebug() << "ColorizeImage(): Error - can't finish colorization";
		return false;
	}

	qDebug() << "Elapsed time in nanosec:" << timer.nsecsElapsed();
	qDebug() << "found = " << found;

	return true;
}

// Finish colorization of Target image using Walsh Simple algorithm
// @input:
// @output:
// - true - colorization finished
// - false - failed to finish colorization
bool WSLookUpTableColorizator::FinishColorization()
{
	if ( (NULL == m_target) ||
		 (NULL == m_source) ||
		 (false == m_target->HasImage()) ||
		 (false == m_source->HasImage()) )
	{
		qDebug() << "FinishColorization(): Error - invalid arguments";
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

	srand(time(NULL));

	for ( unsigned int width = 0; width < targetWdt; width++ )
	{
		for ( unsigned int height = 0; height < targetHgt; height++ )
		{
			if ( true == m_target->IsPixColoured(width, height) )
			{
				continue;
			}

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
				qDebug() << "FinishColorization(): Warning - failed to colorize pixel" << width << height;
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
		}
	}

	return true;
}

// Restore images params if needed
// @input:
// @output:
// - true - images params restored
// - false - can't restore images parameters
bool WSLookUpTableColorizator::PostColorization()
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
