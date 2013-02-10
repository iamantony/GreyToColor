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
	ScaleLabel *imgLabel;
	QString pathToImg;
	Qt::GlobalColor defaultColor;

	switch (t_imgType)
	{
		case Images::TARGET:
		{
			imgLabel = ui->targetImgLbl;
			pathToImg.append(DEFAULT_TARGET_IMG_PATH);
			defaultColor = Qt::red;
			break;
		}

		case Images::RESULT:
		{
			imgLabel = ui->resultImgLbl;
			pathToImg.append(DEFAULT_RESULT_IMG_PATH);
			defaultColor = Qt::green;
			break;
		}

		case Images::SOURCE:
		{
			imgLabel = ui->sourceImgLbl;
			pathToImg.append(DEFAULT_SOURCE_IMG_PATH);
			defaultColor = Qt::blue;
			break;
		}

		default:
		{
			qDebug() << "MainWindow::InitImg(): Error - undefined image type";
			return;
		}
	}

	int currentLabelWidth = imgLabel->width();
	int currentLabelHeight = imgLabel->height();

	QImage imgToSet(pathToImg);
	if ( true == imgToSet.isNull() )
	{
		qDebug() << "Can't load default image from" << pathToImg << endl <<
					"Setting up default color";

		QPixmap pixMap(currentLabelWidth, currentLabelHeight);
		pixMap.fill(defaultColor);
		imgLabel->setPixmap(pixMap);
	}
	else
	{
		imgLabel->SetImage(imgToSet);
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

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

	QImage img(fName);
	ui->targetImgLbl->SetImage(img);
}
