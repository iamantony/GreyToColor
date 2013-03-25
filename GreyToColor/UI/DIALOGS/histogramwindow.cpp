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

// Slot for button Show Histogram
// @input:
// @output:
void HistogramWindow::on_pbFormHist_clicked()
{
	if ( true == m_processing.tryLock() )
	{
		m_processing.unlock();
	}
	else
	{
		return;
	}

	DefineImageType();
	DefineColorSpaceType();

	switch(m_colorSpaceType)
	{
		case ColorSpace::GREY:
			emit SignalFormGreyRGBHist(m_imgType);
			break;

		case ColorSpace::RGB:
			emit SignalFormRGBHist(m_imgType);
			break;

		case ColorSpace::LAB:
			emit SignalFormLABLumHist(m_imgType);
			break;

		case ColorSpace::DEFAULT_LAST:
		default:
		{
			qDebug() << "on_pbFormHist_clicked(): Error - invalid color space type";
			return;
		}
	}
}

// Slot for recieving greyscaled RGB histogram
// @input:
// - QList<double> - unempty histogram
// @output:
void HistogramWindow::SlotRecieveGreyRGBHist(const QList<double> &t_hist)
{
	if ( true == t_hist.isEmpty() )
	{
		m_processing.unlock();

		qDebug() << "SlotRecieveGreyRGBHist(): Error - invalid arguments";
		return;
	}

	if ( false == m_processing.tryLock() )
	{
		return;
	}

	QString histFileName = QFileDialog::getSaveFileName(this,
														"Choose name for Grey RGB Histogram...",
														QDir::currentPath(),
														"CSV file (*.csv)");

	if ( true == histFileName.isEmpty() )
	{
		m_processing.unlock();
		return;
	}

	QFile histFile;
	histFile.setFileName(histFileName);

	bool fileOpened = histFile.open(QIODevice::WriteOnly);
	if ( false == fileOpened )
	{
		m_processing.unlock();

		qDebug() << "SlotRecieveGreyRGBHist(): Error - can't open file!";
		return;
	}

	QTextStream streamToFile;
	streamToFile.setDevice(&histFile);

	const int numOfValues = t_hist.size();

	streamToFile << "NUM;Grey" << endl;
	for ( int i = 0; i < numOfValues; i++ )
	{
		streamToFile << i << ";" << t_hist[i] << endl;
	}

	histFile.close();

	m_processing.unlock();
}

// Slot for recieving RGB histogram
// @input:
// - QList< QList<double> > - unempty 3-channels RGB histogram
// @output:
void HistogramWindow::SlotRecieveRGBHist(const QList< QList<double> > &t_hist)
{
	if ( true == t_hist.isEmpty() )
	{
		m_processing.unlock();

		qDebug() << "SlotRecieveRGBHist(): Error - invalid arguments";
		return;
	}

	if ( false == m_processing.tryLock() )
	{
		return;
	}

	const int numOfChannels = t_hist.size();
	if ( NUM_OF_RGB_CHANN != numOfChannels )
	{
		m_processing.unlock();

		qDebug() << "SlotRecieveRGBHist(): Error - histogram has invalid number of channels";
		return;
	}

	const int chanRedLength = t_hist.at(Histogram::RED).size();
	const int chanGreenLength = t_hist.at(Histogram::GREEN).size();
	const int chanBlueLength = t_hist.at(Histogram::BLUE).size();
	if ( (chanRedLength != chanGreenLength) || (chanRedLength != chanBlueLength) )
	{
		m_processing.unlock();

		qDebug() << "SlotRecieveRGBHist(): Error - invalid RGB histogram channels length";
		return;
	}

	QString histFileName = QFileDialog::getSaveFileName(this,
														"Choose name for RGB Histogram...",
														QDir::currentPath(),
														"CSV file (*.csv)");

	if ( true == histFileName.isEmpty() )
	{
		m_processing.unlock();
		return;
	}

	QFile histFile;
	histFile.setFileName(histFileName);

	bool fileOpened = histFile.open(QIODevice::WriteOnly);
	if ( false == fileOpened )
	{
		m_processing.unlock();

		qDebug() << "SlotRecieveRGBHist(): Error - can't open file!";
		return;
	}

	QTextStream streamToFile;
	streamToFile.setDevice(&histFile);

	streamToFile << "NUM;R;G;B" << endl;
	for ( int i = 0; i < chanRedLength; i++ )
	{
		streamToFile << i << ";" <<
						t_hist[Histogram::RED][i] << ";" <<
						t_hist[Histogram::GREEN][i] << ";" <<
						t_hist[Histogram::BLUE][i] << endl;
	}

	histFile.close();

	m_processing.unlock();
}

// Slot for recieving LAB Luminance histogram
// @input:
// - QList<double> - unempty LAB luminance histogram
// @output:
void HistogramWindow::SlotRecieveLABLumHist(const QList<double> &t_hist)
{
	if ( true == t_hist.isEmpty() )
	{
		m_processing.unlock();

		qDebug() << "SlotRecieveLABLumHist(): Error - invalid arguments";
		return;
	}

	if ( false == m_processing.tryLock() )
	{
		return;
	}

	QString histFileName = QFileDialog::getSaveFileName(this,
														"Choose name for LAB Luminance Histogram...",
														QDir::currentPath(),
														"CSV file (*.csv)");

	if ( true == histFileName.isEmpty() )
	{
		m_processing.unlock();
		return;
	}

	QFile histFile;
	histFile.setFileName(histFileName);

	bool fileOpened = histFile.open(QIODevice::WriteOnly);
	if ( false == fileOpened )
	{
		m_processing.unlock();

		qDebug() << "SlotRecieveLABLumHist(): Error - can't open file!";
		return;
	}

	QTextStream streamToFile;
	streamToFile.setDevice(&histFile);

	const int numOfValues = t_hist.size();

	streamToFile << "NUM;Step;LAB Lum" << endl;
	for ( int i = 0; i < numOfValues; i++ )
	{
		double lum = t_hist[i] * LAB_LUM_HIST_DIVIDER;
		streamToFile << i << ";" <<
						t_hist[i] << ";" <<
						lum << endl;
	}

	histFile.close();

	m_processing.unlock();
}

void HistogramWindow::on_rbLAB_clicked(bool checked)
{
	if ( false == checked )
	{
		ui->gbTargLum->setEnabled(false);
	}
	else
	{
		if ( true == ui->rbTargColor->isChecked() )
		{
			ui->gbTargLum->setEnabled(true);
		}
		else
		{
			ui->gbTargLum->setEnabled(false);
		}
	}
}

void HistogramWindow::on_rbTargColor_clicked(bool checked)
{
	if ( false == checked )
	{
		ui->gbTargLum->setEnabled(false);
	}
	else
	{
		if ( true == ui->rbLAB->isChecked() )
		{
			ui->gbTargLum->setEnabled(true);
		}
		else
		{
			ui->gbTargLum->setEnabled(false);
		}
	}
}
