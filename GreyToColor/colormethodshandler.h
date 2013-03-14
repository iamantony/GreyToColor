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

#ifndef COLORMETHODSHANDLER_H
#define COLORMETHODSHANDLER_H

#include <QObject>
#include <QDebug>
#include "./IMAGES/SOURCE/sourceimage.h"
#include "./IMAGES/TARGET/targetimage.h"
#include "DEFINES/programstatus.h"
#include "DEFINES/colorization.h"

class ColorMethodsHandler : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	Methods::Type m_methodToUse;
	TargetImage *m_targetImg;
	SourceImage *m_sourceImg;

	// == METHODS ==
public:
	explicit ColorMethodsHandler(QObject *parent = 0);
	~ColorMethodsHandler();

	// Clear all info
	void Clear();

private:
	// Start colorization method Walsh Simple
	void ColorizeByWalshSimple();
	// Start colorization method Walsh Neighbor
	void ColorizeByWalshNeighbor();

signals:
	void SignalCurrentProc(const Program::Status &);
	void SignalProcDone();
	void SignalProcError(const QString &);
	void SignalProcFatalError();

public slots:
	// Set type of colorization method to use
	void SlotSetMethodType(const Methods::Type &t_type);
	// Start Colorization
	void SlotStartColorization();
	// Get pointer to current target image
	void SlotGetTargetImg(TargetImage *t_targ);
	// Get pointer to current source image
	void SlotGetSourceImg(SourceImage *t_source);
};

#endif // COLORMETHODSHANDLER_H
