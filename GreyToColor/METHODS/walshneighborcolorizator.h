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

#ifndef WALSHNEIGHBORCOLORIZATOR_H
#define WALSHNEIGHBORCOLORIZATOR_H

#include "colorizator.h"
#include <QDebug>
#include <time.h>
#include <math.h>
#include <QElapsedTimer>
#include "./DEFINES/global.h"
#include "./DEFINES/colorization.h"

class WalshNeighborColorizator : public Colorizator
{
	// == DATA ==

	// == METHODS ==
public:
	WalshNeighborColorizator();

	// Start Colorization
	virtual bool Colorize(TargetImage *t_targetImg, SourceImage *t_sourceImg);

private:
	// Prepare images to colorization
	virtual bool PrepareImages();
	// Colorize Target image using color information from Source image
	virtual bool ColorizeImage();
	// Try to colorize neighbor pixels by the same color
	void ColorizeNeighbor(const unsigned int &t_startWidth, const unsigned int &t_startHeight);

	// Restore images params if needed
	virtual bool PostColorization();
};

#endif // WALSHNEIGHBORCOLORIZATOR_H
