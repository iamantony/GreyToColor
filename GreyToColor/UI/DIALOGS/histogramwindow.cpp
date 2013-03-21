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

#include "histogramwindow.h"
#include "ui_histogramwindow.h"

HistogramWindow::HistogramWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::HistogramWindow)
{
	ui->setupUi(this);

	InitSettings();
	InitImgTypeGroup();
	InitHistTypeGroup();
	InitImgLabels();
	FormWindowName();
}

HistogramWindow::~HistogramWindow()
{
	delete ui;
}

// Init default settings
// @input:
// @output:
void HistogramWindow::InitSettings()
{
	m_imgType = ImageKind::DEFAULT_LAST;
	m_colorSpaceType = ColorSpace::DEFAULT_LAST;
}

// Init action group of images type
// @input:
// @output:
void HistogramWindow::InitImgTypeGroup()
{
	m_imgTypeGroup = new QActionGroup(this);
	m_imgTypeGroup->addAction(ui->actionTargOriginal);
	m_imgTypeGroup->addAction(ui->actionTargColorized);
	m_imgTypeGroup->addAction(ui->actionSource);

	connect(m_imgTypeGroup,
			SIGNAL(triggered(QAction*)),
			this,
			SLOT(SlotSetImgType(QAction*)));

	ui->actionTargOriginal->setChecked(true);
	SlotSetImgType(ui->actionTargOriginal);

	m_imgTypeGroup->setExclusive(true);
	m_imgTypeGroup->setVisible(true);
}

// Init action group of histogram type
// @input:
// @output:
void HistogramWindow::InitHistTypeGroup()
{
	m_histTypeGroup = new QActionGroup(this);
	m_histTypeGroup->addAction(ui->actionHistRGB);
	m_histTypeGroup->addAction(ui->actionHistLAB);

	connect(m_histTypeGroup,
			SIGNAL(triggered(QAction*)),
			this,
			SLOT(SlotSetColorSpType(QAction*)));

	ui->actionHistRGB->setChecked(true);
	SlotSetColorSpType(ui->actionHistRGB);

	m_histTypeGroup->setExclusive(true);
	m_histTypeGroup->setVisible(true);
}

// Init image labels
// @input:
// @output:
void HistogramWindow::InitImgLabels()
{
	ui->labelHist->ShowDefaultImg();
}

// Form window name
// @input:
// @output:
void HistogramWindow::FormWindowName()
{
	QString windName;
	windName.append("Histogram - ");

	switch(m_imgType)
	{
		case ImageKind::TARGET_ORIGINAL:
			windName.append("Target Original - ");
			break;

		case ImageKind::TARGET_COLORIZED:
			windName.append("Target Colorized - ");
			break;

		case ImageKind::SOURCE:
			windName.append("Source - ");
			break;

		case ImageKind::DEFAULT_LAST:
		default:
			windName.append("No image type -");
			break;
	}

	switch(m_colorSpaceType)
	{
		case ColorSpace::RGB:
			windName.append("RGB");
			break;

		case ColorSpace::LAB:
			windName.append("LAB");
			break;

		case ColorSpace::DEFAULT_LAST:
		default:
			windName.append("No color space");
			break;
	}

	this->setWindowTitle(windName);
}

// Slot for catching what type of image user want to use
// @input:
// - QAction - unnull action choosed by user
// @output:
void HistogramWindow::SlotSetImgType(QAction *t_action)
{
	if ( t_action == ui->actionTargOriginal )
	{
		m_imgType = ImageKind::TARGET_ORIGINAL;
	}
	else if ( t_action == ui->actionTargColorized )
	{
		m_imgType = ImageKind::TARGET_COLORIZED;
	}
	else if ( t_action == ui->actionSource )
	{
		m_imgType = ImageKind::SOURCE;
	}

	FormWindowName();

	emit SignalGetImage(m_imgType);
}

// Slot for catching in what type of colorspace we should build histogram
// @input:
// - QAction - unnull action choosed by user
// @output:
void HistogramWindow::SlotSetColorSpType(QAction *t_action)
{
	if ( t_action == ui->actionHistRGB )
	{
		m_colorSpaceType = ColorSpace::RGB;
	}
	else if ( t_action == ui->actionHistLAB )
	{
		m_colorSpaceType = ColorSpace::LAB;
	}

	FormWindowName();
}

// Slot get image for building histogram
// @input:
// - Image - unempty image
// @output:
void HistogramWindow::SlotGetImage(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "SlotGetImage(): Error - invalid arguments";
		return;
	}

	m_image = t_img;
}
