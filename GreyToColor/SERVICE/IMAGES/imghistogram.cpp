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

#include "imghistogram.h"

ImgHistogram::ImgHistogram()
{

}

// Get image luminance histogram (in percent)
// @input:
// - Image - unnull image (color/grey)
// @output:
// - empty QList<unsigned int> - failed to form histogram
// - QList<unsigned int> - images luminance histogram
QList<unsigned int> ImgHistogram::LuminanceHistogram(const Image &t_img)
{
	QList<unsigned int> empty;
	return empty;
}

// Get image channels histogram (in percent)
// @input:
// - Image - unnull image (color/grey)
// @output:
// - empty QList< QList<unsigned int> > - failed to form RGB channels histogram
// - QList< QList<unsigned int> > - histograms of all image channels
QList< QList<unsigned int> > ImgHistogram::RGBHistogram(const Image &t_img)
{
	QList< QList<unsigned int> > empty;
	return empty;
}
