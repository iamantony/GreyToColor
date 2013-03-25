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

#ifndef IMGHANDLER_H
#define IMGHANDLER_H

#include <QObject>
#include <QDebug>
#include "./IMAGES/COMMON/image.h"
#include "./IMAGES/CANDIDATE/candidateimage.h"
#include "./IMAGES/SOURCE/sourceimage.h"
#include "./IMAGES/TARGET/targetimage.h"
#include "SERVICE/calculatorsko.h"
#include "SERVICE/IMAGES/imghistogram.h"
#include "DEFINES/programstatus.h"

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

	// Clear all data
	void Clear();

private:
	// Send greyscale version of target image
	void GetGreyTarget();
	// Get result Target image
	QImage GetResultTargetImg();
	// Calc SKO of coloured Target and original target images
	void CalcTargetsSKO(const QImage &t_resultImg);

signals:
	void SignalGetTargetImg(const QString &t_path);
	void SignalGetResultImg(QImage t_resultImg);
	void SignalFindSimilarInIDB(const Image &t_img);
	void SignalCurrentSourceImg(const QString &t_name);
	void SignalGetPassFromIDB();
	void SignalTargetSet(TargetImage *t_targ);
	void SignalSourceSet(SourceImage *t_source);
	void SignalTargetResultSKO(const double &t_sko);
	void SignalCurrentProc(const Program::Status &);
	void SignalProcDone();
	void SignalProcError(const QString &);
	void SignalProcFatalError();
	void SignalGetGreyRGBHist(const QList<double> &t_hist);
	void SignalGetRGBHist(const QList< QList<double> > &t_hist);
	void SignalGetLABLumHist(const QList<double> &t_hist);

public slots:
	// This slot get signal to save result (colorized or not) image and send it copy signal to some (MainWindow) UI
	void SlotSaveResultImg(const QString &t_imgPath);
	// This slot get path to new original image
	void SlotGetNewTargetImg(const QString &t_imgPath);
	// This slot get path to new source image
	void SlotGetNewSourceImg(const QString &t_imgPath);
	// Start process of searching image in IDB
	void SlotFindSimilarForTarget();
	// Colorization performed. Show result
	void SlotTargetColorized();
	// Slot to form Grey RGB Histogram
	void SlotGreyRGBHist(const ImageKind::Type &t_type);
	// Slot to form RGB Histogram
	void SlotRGBHist(const ImageKind::Type &t_type);
	// Slot to form LAB Histogram
	void SlotLABLumHist(const ImageKind::Type &t_type);
};

#endif // IMGHANDLER_H
