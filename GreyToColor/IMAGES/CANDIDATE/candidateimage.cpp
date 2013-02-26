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

#include "candidateimage.h"

CandidateImage::CandidateImage()
{
}

// Get value of max RGB luminance (for grey/color images)
// @input:
// @output:
// - ERROR - can't get max luminance
// - int - posititve value of max luminance of this image
int CandidateImage::GetMaxRGBLum()
{
	return ERROR;
}

// Get value of min RGB luminance (for grey/color images)
// @input:
// @output:
// - ERROR - can't get min luminance
// - int - posititve value of min luminance of this image
int CandidateImage::GetMinRGBLum()
{
	return ERROR;
}

// Get luminance histogram of this image
// @input:
// @output:
// - empty QList<int> - can't get luminance histogram
// - unempty QList<int> - luminance histogram of this image
QList<int> CandidateImage::GetRGBLumHistogram()
{
	QList<int> empty;
	return empty;
}

// Get histogram of each RGB channel (red, green, blue) of this image
// @input:
// @output:
// - empty QList< QList<int> > - can't get luminance histogram
// - unempty QList< QList<int> > - histogram of each RGB channels of this image
QList< QList<int> > CandidateImage::GetRGBHistogram()
{
	QList< QList<int> > empty;
	return empty;
}
