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
	InitImgTypeBG();
	InitColorSpaceBG();
	InitTargLumScaleBG();
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
	m_processing.unlock();
}

// Init Button group for image types
// @input:
// @output:
void HistogramWindow::InitImgTypeBG()
{
	m_imgTypeBG.setExclusive(true);

	connect(&m_imgTypeBG,
			SIGNAL(buttonClicked(int)),
			this,
			SLOT(SlotImgTypeRBClicked(int)));

	int buttonID = 0;
	m_imgTypeBG.addButton(ui->rbTargOrig, buttonID);
	m_imgTypes.insert(buttonID, ImageKind::TARGET_ORIGINAL);

	buttonID++;
	m_imgTypeBG.addButton(ui->rbTargColor, buttonID);
	m_imgTypes.insert(buttonID, ImageKind::TARGET_COLORIZED);

	buttonID++;
	m_imgTypeBG.addButton(ui->rbSource, buttonID);
	m_imgTypes.insert(buttonID, ImageKind::SOURCE);

	ui->rbTargOrig->setChecked(true);
}

// Init Button group for color space types
// @input:
// @output:
void HistogramWindow::InitColorSpaceBG()
{
	m_colorSpcaeBG.setExclusive(true);

	connect(&m_colorSpcaeBG,
			SIGNAL(buttonClicked(int)),
			this,
			SLOT(SlotColorSPTypeRBClicked(int)));

	int buttonID = 0;
	m_colorSpcaeBG.addButton(ui->rbRGBGrey, buttonID);
	m_csTypes.insert(buttonID, ColorSpace::GREY);

	buttonID++;
	m_colorSpcaeBG.addButton(ui->rbRGB, buttonID);
	m_csTypes.insert(buttonID, ColorSpace::RGB);

	buttonID++;
	m_colorSpcaeBG.addButton(ui->rbLAB, buttonID);
	m_csTypes.insert(buttonID, ColorSpace::LAB);

	ui->rbRGBGrey->setChecked(true);
}

// Init Button group for types of Target image luminance scale
// @input:
// @output:
void HistogramWindow::InitTargLumScaleBG()
{
	m_targetLumScaleBG.setExclusive(true);

	int buttonID = 0;
	m_targetLumScaleBG.addButton(ui->rbNoScale, buttonID);
	m_targScaleTypes.insert(buttonID, LumEqualization::NO_SCALE);

	buttonID++;
	m_targetLumScaleBG.addButton(ui->rbScaleMax, buttonID);
	m_targScaleTypes.insert(buttonID, LumEqualization::SCALE_BY_MAX);

	buttonID++;
	m_targetLumScaleBG.addButton(ui->rbScaleAver, buttonID);
	m_targScaleTypes.insert(buttonID, LumEqualization::SCALE_BY_AVERAGE);

	buttonID++;
	m_targetLumScaleBG.addButton(ui->rbNormBorder, buttonID);
	m_targScaleTypes.insert(buttonID, LumEqualization::NORMALIZE_LUM_BORDER);

	buttonID++;
	m_targetLumScaleBG.addButton(ui->rbNormCenter, buttonID);
	m_targScaleTypes.insert(buttonID, LumEqualization::NORMALIZE_LUM_CENTER);

	ui->rbScaleMax->setChecked(true);
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


	int imgTypeRBID = m_imgTypeBG.checkedId();
	ImageKind::Type imgType = m_imgTypes.value(imgTypeRBID);

	int colorSpRBID = m_colorSpcaeBG.checkedId();
	ColorSpace::Type colorSpaceType = m_csTypes.value(colorSpRBID);

	// Check if user want to see scaled Target image Luminance histogram
	bool ruleComplied = CheckLumScaleGBRule(imgType, colorSpaceType);
	if ( true == ruleComplied )
	{
		int lumScaleRBID = m_targetLumScaleBG.checkedId();
		LumEqualization::Type lumEqType = m_targScaleTypes.value(lumScaleRBID);

		emit SignalFormTargLumHist(lumEqType);

		return;
	}

	switch(colorSpaceType)
	{
		case ColorSpace::GREY:
			emit SignalFormGreyRGBHist(imgType);
			break;

		case ColorSpace::RGB:
			emit SignalFormRGBHist(imgType);
			break;

		case ColorSpace::LAB:
			emit SignalFormLABLumHist(imgType);
			break;

		case ColorSpace::DEFAULT_LAST:
		default:
		{
			qDebug() << "on_pbFormHist_clicked(): Error - invalid color space type";
			return;
		}
	}
}

// Slot for getting ID number of current checked Image Type RB
// @input:
// - int - exist ID of Image type RB
// @output:
void HistogramWindow::SlotImgTypeRBClicked(int t_id)
{
	ImageKind::Type imgType = m_imgTypes.value(t_id);

	int colorSpRBID = m_colorSpcaeBG.checkedId();
	ColorSpace::Type colorSpaceType = m_csTypes.value(colorSpRBID);

	CheckLumScaleGBRule(imgType, colorSpaceType);
}

// Slot for getting ID number of current checked Color Space Type RB
// @input:
// - int - exist ID of Color Space type RB
// @output:
void HistogramWindow::SlotColorSPTypeRBClicked(int t_id)
{
	ColorSpace::Type colorSpaceType = m_csTypes.value(t_id);

	int imgTypeRBID = m_imgTypeBG.checkedId();
	ImageKind::Type imgType = m_imgTypes.value(imgTypeRBID);

	CheckLumScaleGBRule(imgType, colorSpaceType);
}

// Checking rule for enabling Group Box of Target Luminance scale types
// @input:
// - ImageKind::Type - exist Image Type
// - ColorSpace::Type - exist Color Space type
// @output:
bool HistogramWindow::CheckLumScaleGBRule(const ImageKind::Type &t_imgType, const ColorSpace::Type &t_csType)
{
	bool enableTargLumGB = false;
	if ( (ImageKind::TARGET_COLORIZED == t_imgType) && (ColorSpace::LAB == t_csType) )
	{
		enableTargLumGB = true;
	}
	else
	{
		enableTargLumGB = false;
	}

	ui->gbTargLum->setEnabled(enableTargLumGB);
	return enableTargLumGB;
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

	streamToFile << "NUM;LAB_Lum;Pixels" << endl;
	for ( int i = 0; i < numOfValues; i++ )
	{
		double lumValue = i * LAB_LUM_HIST_DIVIDER;
		streamToFile << i << ";" <<
						lumValue << ";" <<
						t_hist[i] << endl;
	}

	histFile.close();

	m_processing.unlock();
}
