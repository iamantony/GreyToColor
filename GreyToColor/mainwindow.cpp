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

// Call all functions to initialise UI
// @input:
// @output:
void MainWindow::InitUI()
{
	ui->setupUi(this);

	InitStatusBar();
	InitImgsLabels();
}

// Creating, applying settings to status bar
// @input:
// @output:
void MainWindow::InitStatusBar()
{
	m_statusBar = new StatusBar();
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
// - t_imgType - type of label
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

		default:
		{
			qDebug() << "MainWindow::InitImg(): Error - undefined image type";
			return;
		}
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

// Show warning window with title and some text
// @input:
// - t_title - nonempty title of the window
// - t_text - nonempty text for the message
// @output:
void MainWindow::ShowWarning(const QString &t_title, const QString &t_text)
{
	QMessageBox::warning(this,
						 t_title,
						 t_text,
						 QMessageBox::Ok,
						 QMessageBox::NoButton);
}

// Slot for button TargetImgPB to set target image
// @input:
// @output:
void MainWindow::on_openTargetImgPB_clicked()
{
	QString fName = QFileDialog::getOpenFileName(this,
												 "Open target image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.bmp)");

	if(true == fName.isEmpty())
	{
		return;
	}

	bool imgSet = ui->targetImgLbl->SetImage(fName);
	if ( false == imgSet )
	{
		ShowWarning("Loading target image...", "Can't load image. Please, try another one.");
	}
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
	QString fName = QFileDialog::getOpenFileName(this,
												 "Open source image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.bmp)");

	if(true == fName.isEmpty())
	{
		return;
	}

	bool imgSet = ui->sourceImgLbl->SetImage(fName);
	if ( false == imgSet )
	{
		ShowWarning("Loading source image...", "Can't load image. Please, try another one.");
	}
}

// Slot for action actionOpenSourceImage to set source image
// @input:
// @output:
void MainWindow::on_actionOpenSourceImage_triggered()
{
	on_openSourceImgPB_clicked();
}
