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

#ifndef IMGHANDLER_H
#define IMGHANDLER_H

#include <QObject>
#include <QDebug>
#include "./IMAGES/image.h"

class ImgHandler : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	Image m_original;
//	TargetImage m_target;
//	SourceImage m_source;

	// == METHODS ==
public:
	explicit ImgHandler(QObject *parent = 0);

signals:
	void SignalGetResultImg(QImage t_img);
	void SignalHasNewTarget();
	void SignalSendTargetImg();

public slots:
	// This slot get signal to save result (colorized or not) image and send it copy signal to some (MainWindow) UI
	void SlotSaveResultImg();
	// This slot get path to new original image
	void SlotGetOriginalImg(const QString &t_imgPath);
};

#endif // IMGHANDLER_H
