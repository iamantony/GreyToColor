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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	InitUI();
}

MainWindow::~MainWindow()
{
	delete ui;
}

// Call all functions to initialise UI
// @input:
// @output:
void MainWindow::InitUI()
{
	ui->setupUi(this);
	m_appStatus = Program::OK;

	InitStatusBar();
	InitImgsLabels();
}

// Creating, applying settings to status bar
// @input:
// @output:
void MainWindow::InitStatusBar()
{
	m_statusBar = new StatusBar();
	m_statusBar->SetStatus(m_appStatus);

	this->setStatusBar(m_statusBar);
}

// Put default picture to all labels on MainWindow
// @input:
// @output:
void MainWindow::InitImgsLabels()
{
	InitImg(Images::TARGET);
	InitImg(Images::RESULT);
	InitImg(Images::SOURCE);
}

// Put default picture to one of three labels on MainWindow
// @input:
// - Images::Types - exist type of label
// @output:
void MainWindow::InitImg(Images::Types t_imgType)
{
	switch (t_imgType)
	{
		case Images::TARGET:
		{
			ui->targetImgLbl->SetDefaultImgPath(DEFAULT_TARGET_IMG_PATH);
			ui->targetImgLbl->ShowDefaultImg();
			break;
		}

		case Images::RESULT:
		{
			ui->resultImgLbl->SetDefaultImgPath(DEFAULT_RESULT_IMG_PATH);
			ui->resultImgLbl->ShowDefaultImg();
			break;
		}

		case Images::SOURCE:
		{
			ui->sourceImgLbl->SetDefaultImgPath(DEFAULT_SOURCE_IMG_PATH);
			ui->sourceImgLbl->ShowDefaultImg();
			break;
		}

		case Images::DEFAULT_LAST:
		default:
		{
			qDebug() << "MainWindow::InitImg(): Error - undefined image type";
			return;
		}
	}
}

// Show warning window with title and some text
// @input:
// - QString - nonempty string with title of the window
// - QString - nonempty string with text for the message
// @output:
void MainWindow::ShowWarning(const QString &t_title, const QString &t_text)
{
	QMessageBox::warning(this,
						 t_title,
						 t_text,
						 QMessageBox::Ok,
						 QMessageBox::NoButton);
}

// Check if app status if OK (application not performing some calculations)
// @input:
// @output:
// - true - app can get new work
// - false - app is busy
bool MainWindow::CanOperate()
{
	if ( Program::OK == m_appStatus )
	{
		return true;
	}

	return false;
}

// Slot for button TargetImgPB to set target image
// @input:
// @output:
void MainWindow::on_openTargetImgPB_clicked()
{
	if ( false == CanOperate() )
	{
		return;
	}

	QString fName = QFileDialog::getOpenFileName(this,
												 "Open target image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	if(true == fName.isEmpty())
	{
		return;
	}

	bool imgSet = ui->targetImgLbl->SetImage(fName);
	if ( false == imgSet )
	{
		ShowWarning("Loading Target Image...", "Can't load image. Please, try another one.");
		return;
	}

	emit SignalNewTargetImg(fName);
}

// Slot for action actionOpenTargetImage to set target image
// @input:
// @output:
void MainWindow::on_actionOpenTargetImage_triggered()
{
	on_openTargetImgPB_clicked();
}

// Slot for button SourceImgPB to set source image
// @input:
// @output:
void MainWindow::on_openSourceImgPB_clicked()
{
	if ( false == CanOperate() )
	{
		return;
	}

	QString fName = QFileDialog::getOpenFileName(this,
												 "Open source image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	if(true == fName.isEmpty())
	{
		return;
	}

	bool imgSet = ui->sourceImgLbl->SetImage(fName);
	if ( false == imgSet )
	{
		ShowWarning("Loading source image...", "Can't load image. Please, try another one.");
		return;
	}

	emit SignalNewSourceImg(fName);
}

// Slot for action actionOpenSourceImage to set source image
// @input:
// @output:
void MainWindow::on_actionOpenSourceImage_triggered()
{
	on_openSourceImgPB_clicked();
}

// Slot for action actionSaveResult to save Result Image
// @input:
// @output:
void MainWindow::on_actionSaveResult_triggered()
{
	if ( false == CanOperate() )
	{
		return;
	}

	QString imgName = QFileDialog::getSaveFileName(this,
												   "Choose name...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	if ( true == imgName.isEmpty() )
	{
		// User change his mind
		return;
	}

	emit SignalSaveResultImg(imgName);
}

// Slot for getting new Source image
// @input:
// - QImage - unnull new source image
// @output:
void MainWindow::SlotGetSourceImg(QImage t_sourceImg)
{
	if ( true == t_sourceImg.isNull() )
	{
		qDebug() << "SlotSourceImg(): Error - invalid arguments";
		return;
	}

	ui->sourceImgLbl->SetImage(t_sourceImg);
}

// Slot for button findSourceImgPB to find similar image from IDB
// @input:
// @output:
void MainWindow::on_findSourceImgPB_clicked()
{
	emit SignalFindSimilarInIDB();
}

// Slot for getting new Result image
// @input:
// - QImage - unnull new result image
// @output:
void MainWindow::SlotGetResultImg(QImage t_resultImg)
{
	if ( true == t_resultImg.isNull() )
	{
		qDebug() << "SlotResultImg(): Error - invalid arguments";
		return;
	}

	ui->resultImgLbl->SetImage(t_resultImg);
}

// Slot for start colrization process
// @input:
// @output:
void MainWindow::on_startColorizationPB_clicked()
{
	if ( false == CanOperate() )
	{
		return;
	}

	// TODO:
	// - start colorization
}

// Slot for resetting current target image
// @input:
// @output:
void MainWindow::on_resetPB_clicked()
{
	if ( false == CanOperate() )
	{
		return;
	}

	ImgSubsampler test;
	test.TestSubsampling();

	// TODO:
	// Send signal to ImgHandler. It should reload target image, calc all it's params (LAB, SKO) and then send
	// it to us
}

// Info-slot: type of current proccess
// @input:
// - Program::Status - exist type of program status
// @output:
void MainWindow::SlotCurrProcess(const Program::Status &t_status)
{
	m_appStatus = t_status;
	m_statusBar->SetStatus(m_appStatus);
}

// Info-slot: process ended normally
// @input:
// @output:
void MainWindow::SlotProcessEnd()
{
	m_appStatus = Program::OK;
	m_statusBar->SetStatus(m_appStatus);
}

// Info-slot: process failed with some reason
// @input:
// - QString - unempty string with warning message from some process
// @output:
void MainWindow::SlotProcError(const QString &t_message)
{
	if ( true == t_message.isEmpty() )
	{
		ShowWarning(tr("Warning!"), tr("Empty message!"));
	}
	else
	{
		ShowWarning(tr("Warning!"), t_message);
	}

	SlotProcessEnd();
}

// Info-slot: process failed
// @input:
// @output:
void MainWindow::SlotProcessFail()
{
	m_appStatus = Program::ERR;
	m_statusBar->SetStatus(m_appStatus);
}

// Slot for creating new database
// @input:
// @output:
void MainWindow::on_actionCreateDatabase_triggered()
{
	bool okButton = false;
	QString idbName = QInputDialog::getText(this,
											"Choose name of new image database...",
											"Enter name:",
											QLineEdit::Normal,
											"default",
											&okButton);

	if ( (false == okButton) || (true == idbName.isEmpty()) )
	{
		return;
	}

	emit SignalNewIDB(idbName);
}

// Slot for opening exist database
// @input:
// @output:
void MainWindow::on_actionOpenDatabase_triggered()
{

}

// Slot for adding images to opened database
// @input:
// @output:
void MainWindow::on_actionAddImages_triggered()
{

}
