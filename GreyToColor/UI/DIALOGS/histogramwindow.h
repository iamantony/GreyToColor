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
#include <QMutex>
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
	ImageKind::Type m_imgType;
	ColorSpace::Type m_colorSpaceType;
	QMutex m_processing;

	// == METHODS ==
public:
	explicit HistogramWindow(QWidget *parent = 0);
	~HistogramWindow();

private:
	// Init default settings
	void InitSettings();
	// Set up image type
	void SetUpImgType();
	// Set up color space in which we should calc histogram
	void SetUpColorSpaceType();
	// Define checked Image Type
	void DefineImageType();
	// Define checked Color Space Type
	void DefineColorSpaceType();

signals:
	void SignalFormGreyRGBHist(const ImageKind::Type &t_imgType);
	void SignalFormRGBHist(const ImageKind::Type &t_imgType);
	void SignalFormLABLumHist(const ImageKind::Type &t_imgType);

public slots:
	// Slot for recieving greyscaled RGB histogram
	void SlotRecieveGreyRGBHist(const QList<double> &t_hist);
	// Slot for recieving RGB histogram
	void SlotRecieveRGBHist(const QList< QList<double> > &t_hist);
	// Slot for recieving LAB Luminance histogram
	void SlotRecieveLABLumHist(const QList<double> &t_hist);

private slots:
	void on_pbFormHist_clicked();
};

#endif // HISTOGRAMWINDOW_H
