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
#include <QActionGroup>
#include <QDebug>
#include "IMAGES/COMMON/image.h"
#include "UI/scalelabel.h"
#include "DEFINES/images.h"

namespace Ui {
	class HistogramWindow;
}

class HistogramWindow : public QMainWindow
{
	Q_OBJECT

	// == DATA ==
private:
	Ui::HistogramWindow *ui;
	QActionGroup *m_imgTypeGroup;
	QActionGroup *m_histTypeGroup;
	ImageKind::Type m_imgType;
	ColorSpace::Type m_colorSpaceType;
	Image m_image;

	// == METHODS ==
public:
	explicit HistogramWindow(QWidget *parent = 0);
	~HistogramWindow();

private:
	// Init default settings
	void InitSettings();
	// Init action group of images type
	void InitImgTypeGroup();
	// Init action group of histogram type
	void InitHistTypeGroup();
	// Init image labels
	void InitImgLabels();
	// Form window name
	void FormWindowName();

signals:
	void SignalGetImage(const ImageKind::Type &t_imgType);

private slots:
	// Slot for catching what type of image user want to use
	void SlotSetImgType(QAction *t_action);
	// Slot for catching in what type of colorspace we should build histogram
	void SlotSetColorSpType(QAction *t_action);
	// Slot get image for building histogram
	void SlotGetImage(const Image &t_img);
};

#endif // HISTOGRAMWINDOW_H
