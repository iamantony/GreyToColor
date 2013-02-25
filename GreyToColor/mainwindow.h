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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include "UI/statusbar.h"
#include "UI/scalelabel.h"
#include "IMAGES/COMMON/image.h"
#include "DEFINES/programstatus.h"
#include "DEFINES/mainwindowui.h"

#include "IMAGES/COMMON/PIXELS/imagepixels.h"
#include "IMAGES/SOURCE/PIXELS/sourceimgpixels.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	// == DATA ==
private:
	Ui::MainWindow *ui;
	StatusBar *m_statusBar;

	// == METHODS ==
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void InitUI();
	void InitStatusBar();
	void InitImgsLabels();
	void InitImg(Images::Types t_imgType);
	void ShowWarning(const QString &t_title, const QString &t_text);

signals:
	void SignalFindSimilarInIDB();
	void SignalSaveResultImg();
	void SignalStrToOriginalImg(const QString &t_str);

public slots:
	// Slot for getting new Result image
	void SlotResultImg(QImage t_resultImg);
	// Slot for getting new Source image
	void SlotSourceImg(QImage t_sourceImg);
	// Slot for saving result (colorized) image
	void SlotSaveResult(QImage t_resultImg);

private slots:
	void on_openTargetImgPB_clicked();
	void on_actionOpenTargetImage_triggered();
	void on_openSourceImgPB_clicked();
	void on_actionOpenSourceImage_triggered();
	void on_findSourceImgPB_clicked();
	void on_saveResultPB_clicked();
	void on_resetPB_clicked();
};

#endif // MAINWINDOW_H
