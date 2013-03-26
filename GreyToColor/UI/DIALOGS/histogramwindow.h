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

#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QMutex>
#include <QMap>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include "UI/scalelabel.h"
#include "DEFINES/imgservice.h"
#include "DEFINES/pixels.h"
#include "DEFINES/images.h"
#include "DEFINES/histogramui.h"

namespace Ui
{
	class HistogramWindow;
}

class HistogramWindow : public QMainWindow
{
	Q_OBJECT

	// == DATA ==
private:
	Ui::HistogramWindow *ui;
	QButtonGroup m_imgTypeBG;
	QButtonGroup m_colorSpcaeBG;
	QButtonGroup m_targetLumScaleBG;
	QMap<int, ImageKind::Type> m_imgTypes;
	QMap<int, ColorSpace::Type> m_csTypes;
	QMap<int, LumEqualization::Type> m_targScaleTypes;
	QMutex m_processing;

	// == METHODS ==
public:
	explicit HistogramWindow(QWidget *parent = 0);
	~HistogramWindow();

private:
	// Init default settings
	void InitSettings();
	// Init Button group for image types
	void InitImgTypeBG();
	// Init Button group for color space types
	void InitColorSpaceBG();
	// Init Button group for types of Target image luminance scale
	void InitTargLumScaleBG();
	// Checking rule for enabling Group Box of Target Luminance scale types
	bool CheckLumScaleGBRule(const ImageKind::Type &t_imgType, const ColorSpace::Type &t_csType);

signals:
	void SignalFormGreyRGBHist(const ImageKind::Type &t_imgType);
	void SignalFormRGBHist(const ImageKind::Type &t_imgType);
	void SignalFormLABLumHist(const ImageKind::Type &t_imgType);
	void SignalFormTargLumHist(const LumEqualization::Type &t_lumType);

public slots:
	// Slot for recieving greyscaled RGB histogram
	void SlotRecieveGreyRGBHist(const QList<double> &t_hist);
	// Slot for recieving RGB histogram
	void SlotRecieveRGBHist(const QList< QList<double> > &t_hist);
	// Slot for recieving LAB Luminance histogram
	void SlotRecieveLABLumHist(const QList<double> &t_hist);

private slots:
	void on_pbFormHist_clicked();
	// Slot for getting ID number of current checked Image Type RB
	void SlotImgTypeRBClicked(int t_id);
	// Slot for getting ID number of current checked Color Space Type RB
	void SlotColorSPTypeRBClicked(int t_id);
};

#endif // HISTOGRAMWINDOW_H
