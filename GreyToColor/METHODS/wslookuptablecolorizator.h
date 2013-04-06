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

#ifndef WSLOOKUPTABLECOLORIZATOR_H
#define WSLOOKUPTABLECOLORIZATOR_H

#include <math.h>
#include <time.h>

#include <QPair>
#include <QDebug>
#include <QElapsedTimer>

#include "colorizator.h"
#include "./DEFINES/global.h"
#include "./DEFINES/colorization.h"
#include "./DEFINES/pixels.h"

class WSLookUpTableColorizator : public Colorizator
{
	// == DATA ==
private:
	QMap<unsigned int, LookUpSKO> m_lookUpTable;

	// == METHODS ==
public:
	WSLookUpTableColorizator();

	// Start Colorization
	virtual bool Colorize(TargetImage *t_targetImg,
						  SourceImage *t_sourceImg,
						  const LumEqualization::Type &t_type);

private:
	// Prepare images to colorization
	virtual bool PrepareImages(const LumEqualization::Type &t_type);
	// Form look up table on Source image basis
	bool FormLookUpTable();
	// Form empty look up table
	void FormEmptyLookUpTable();
	// Form list of all posible LAB luminances
	QList<unsigned int> FormLumValues();
	// Form list of all possible SKO values
	QList<unsigned int> FormSKOValues();
	// Fill look up table
	bool FillLookUpTable();
	// Reduce number of coords per cell in look up table
	void ReduceLookUpTable();
	// Colorize Target image using color information from Source image
	virtual bool ColorizeImage();
	// Finish colorization of Target image using Walsh Simple algorithm
	bool FinishColorization();
	// Restore images params if needed
	virtual bool PostColorization();
};

#endif // WSLOOKUPTABLECOLORIZATOR_H
