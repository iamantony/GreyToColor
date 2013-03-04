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
#include "./IMAGES/COMMON/image.h"
#include "./IMAGES/CANDIDATE/candidateimage.h"
#include "./IMAGES/SOURCE/sourceimage.h"
#include "./IMAGES/TARGET/targetimage.h"

class ImgHandler : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	Image m_targetOriginal;
	TargetImage m_target;
	SourceImage m_source;

	// == METHODS ==
public:
	explicit ImgHandler(QObject *parent = 0);
	~ImgHandler();

private:
	// Send out current result image
	void SendResultImg();

signals:
	void SignalFailLoadOrigTargImg();
	void SignalFailLoadTargImg();
	void SignalFailTargetImgSave();
	void SignalNoTargetImg();
	void SignalGetResultImg(QImage t_resultImg);
	void SignalNoResultImg();
	void SignalFailLoadSourceImg();

public slots:
	// This slot get signal to save result (colorized or not) image and send it copy signal to some (MainWindow) UI
	void SlotSaveResultImg(const QString &t_imgPath);
	// This slot get path to new original image
	void SlotGetNewTargetImg(const QString &t_imgPath);
	// This slot get path to new source image
	void SlotGetNewSourceImg(const QString &t_imgPath);
};

#endif // IMGHANDLER_H
