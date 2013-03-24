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
	SetUpImgType();
	SetUpColorSpaceType();
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
	m_imgType = ImageKind::TARGET_ORIGINAL;
	m_colorSpaceType = ColorSpace::GREY;
	m_processing.unlock();
}

// Set up image type
// @input:
// @output:
void HistogramWindow::SetUpImgType()
{
	switch(m_imgType)
	{
		case ImageKind::TARGET_ORIGINAL:
			ui->rbTargOrig->setChecked(true);
			break;

		case ImageKind::TARGET_COLORIZED:
			ui->rbTargColor->setChecked(true);
			break;

		case ImageKind::SOURCE:
			ui->rbSource->setChecked(true);
			break;

		case ImageKind::DEFAULT_LAST:
		default:
		{
			qDebug() << "SetUpImgType(): Error - invalid image type";
			return;
		}
	}
}

// Set up color space in which we should calc histogram
// @input:
// @output:
void HistogramWindow::SetUpColorSpaceType()
{
	switch(m_colorSpaceType)
	{
		case ColorSpace::GREY:
			ui->rbRGBGrey->setChecked(true);
			break;

		case ColorSpace::RGB:
			ui->rbRGB->setChecked(true);
			break;

		case ColorSpace::LAB:
			ui->rbLAB->setChecked(true);
			break;

		case ColorSpace::DEFAULT_LAST:
		default:
		{
			qDebug() << "SetUpColorSpaceType(): Error - invalid color space type";
			return;
		}
	}
}

// Define checked Image Type
// @input:
// @output:
void HistogramWindow::DefineImageType()
{
	if ( true == ui->rbTargOrig->isChecked() )
	{
		m_imgType = ImageKind::TARGET_ORIGINAL;
	}
	else if ( true == ui->rbTargColor->isChecked() )
	{
		m_imgType = ImageKind::TARGET_COLORIZED;
	}
	else if ( true == ui->rbSource->isChecked() )
	{
		m_imgType = ImageKind::SOURCE;
	}
}

// Define checked Color Space Type
// @input:
// @output:
void HistogramWindow::DefineColorSpaceType()
{
	if ( true == ui->rbRGBGrey->isChecked() )
	{
		m_colorSpaceType = ColorSpace::GREY;
	}
	else if ( true == ui->rbRGB->isChecked() )
	{
		m_colorSpaceType = ColorSpace::RGB;
	}
	else if ( true == ui->rbLAB->isChecked() )
	{
		m_colorSpaceType = ColorSpace::LAB;
	}
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

	FormHistogram();
}

// Slot for button Show Histogram
// @input:
// @output:
void HistogramWindow::on_pbFormHist_clicked()
{
	if ( false == m_processing.tryLock() )
	{
		return;
	}

	m_processing.lock();

	emit SignalGetImage(m_imgType);
}

// Decide which type of histogram we gonna make
// @input:
// @output:
void HistogramWindow::FormHistogram()
{
	m_processing.lock();

	switch(m_colorSpaceType)
	{
		case ColorSpace::GREY:
			FormRGBGreyHist();
			break;

		case ColorSpace::RGB:
			FormRGBHist();
			break;

		case ColorSpace::LAB:
			FormLABHist();
			break;

		case ColorSpace::DEFAULT_LAST:
		default:
		{
			qDebug() << "FormHistogram(): Error - invalid color space type";
			m_processing.unlock();
			return;
		}
	}

	m_processing.unlock();
}

// Form Greyscaled RGB histogram
// @input:
// @output:
void HistogramWindow::FormRGBGreyHist()
{
	ImgHistogram histogramer;
	QList<double> rgbHist = histogramer.LuminanceHistogram(m_image, NUM_RGB_VALUES);
	if ( (true == rgbHist.isEmpty()) || ( NUM_RGB_VALUES != rgbHist.size() ) )
	{
		qDebug() << "FromRGBGreyHist(): Error - invalid Grey RGB histogram size";
		return;
	}

	QString histFileName = QFileDialog::getSaveFileName(this,
														"Choose name...",
														QDir::currentPath(),
														"CSV file (*.csv)");

	if ( true == histFileName.isEmpty() )
	{
		return;
	}

	QFile histFile;
	histFile.setFileName(histFileName);

	bool fileOpened = histFile.open(QIODevice::WriteOnly);
	if ( false == fileOpened )
	{
		qDebug() << "Can't open file!";
		return;
	}

	QTextStream streamToFile;
	streamToFile.setDevice(&histFile);

	streamToFile << "NUM;Grey" << endl;
	for ( int i = 0; i < NUM_RGB_VALUES; i++ )
	{
		streamToFile << i << ";" << rgbHist[i] << endl;
	}

	histFile.close();
}

// Form RGB histogram
// @input:
// @output:
void HistogramWindow::FormRGBHist()
{
	ImgHistogram histogramer;
	QList< QList<double> > rgbHist = histogramer.RGBHistogram(m_image, NUM_RGB_VALUES);
	if ( (true == rgbHist.isEmpty()) || ( NUM_OF_RGB_CHANN != rgbHist.size() ) )
	{
		qDebug() << "FromRGBHist(): Error - invalid RGB histogram size";
		return;
	}

	const int chanRedLength = rgbHist.at(Histogram::RED).size();
	const int chanGreenLength = rgbHist.at(Histogram::GREEN).size();
	const int chanBlueLength = rgbHist.at(Histogram::BLUE).size();
	if ( (chanRedLength != chanGreenLength) || (chanRedLength != chanBlueLength) )
	{
		qDebug() << "FromRGBHist(): Error - invalid RGB histogram channels length";
		return;
	}

	QString histFileName = QFileDialog::getSaveFileName(this,
														"Choose name...",
														QDir::currentPath(),
														"CSV file (*.csv)");

	if ( true == histFileName.isEmpty() )
	{
		return;
	}

	QFile histFile;
	histFile.setFileName(histFileName);

	bool fileOpened = histFile.open(QIODevice::WriteOnly);
	if ( false == fileOpened )
	{
		qDebug() << "Can't open file!";
		return;
	}

	QTextStream streamToFile;
	streamToFile.setDevice(&histFile);

	streamToFile << "NUM;R;G;B" << endl;
	for ( int i = 0; i < chanRedLength; i++ )
	{
		streamToFile << i << ";" <<
						rgbHist[Histogram::RED][i] << ";" <<
						rgbHist[Histogram::GREEN][i] << ";" <<
						rgbHist[Histogram::BLUE][i] << endl;
	}

	histFile.close();
}

// Form LAB histogram
// @input:
// @output:
void HistogramWindow::FormLABHist()
{
	// TODO:
	// - form histogram
	// - use TargetImage
}
