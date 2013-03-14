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

#ifndef COLORIZATOR_H
#define COLORIZATOR_H

#include "./IMAGES/SOURCE/sourceimage.h"
#include "./IMAGES/TARGET/targetimage.h"

class Colorizator
{
	// == DATA ==
protected:
	TargetImage *m_target;
	SourceImage *m_source;

	// == METHODS ==
public:
	Colorizator();
	~Colorizator();

	// Start Colorization
	virtual bool Colorize(TargetImage *t_targetImg, SourceImage *t_sourceImg) = 0;

protected:
	// Prepare images to colorization
	virtual bool PrepareImages() = 0;
	// Colorize Target image using color information from Source image
	virtual bool ColorizeImage() = 0;
	// Restore images params if needed
	virtual bool PostColorization() = 0;

private:
	void Clear();
};

#endif // COLORIZATOR_H
