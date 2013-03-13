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
#include <QActionGroup>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include "UI/statusbar.h"
#include "UI/scalelabel.h"
#include "IMAGES/COMMON/image.h"
#include "DEFINES/programstatus.h"
#include "DEFINES/mainwindowui.h"
#include "DEFINES/idbs.h"

#include "SERVICE/IMAGES/imgfilter.h"

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
	QActionGroup *m_passports;
	Program::Status m_appStatus;

	// == METHODS ==
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	// Call all functions to initialise UI
	void InitUI();
	// Creating, applying settings to status bar
	void InitStatusBar();
	// Put default picture to all labels on MainWindow
	void InitImgsLabels();
	// Put default picture to one of three labels on MainWindow
	void InitImg(Images::Types t_imgType);
	// Init group of passport type actions
	void InitPassportActionsGroup();
	// Show warning window with title and some text
	void ShowWarning(const QString &t_title, const QString &t_text);
	// Check if app status if OK (application not performing some calculations)
	bool CanOperate();

signals:
	void SignalNewIDB(const QString &t_name);
	void SignalOpenIDB(const QString &t_name);
	void SignalAddImagesToIDB(const QStringList &t_names);
	void SignalFindSimilarImgInIDB();
	void SignalNewTargetImg(const QString &t_str);
	void SignalNewSourceImg(const QString &t_str);
	void SignalSaveResultImg(const QString &t_imgPath);
	void SignalUseImgPassport(const Passport::Type &t_type);

public slots:
	// Slot for getting new Target image
	void SlotGetTargetImg(const QString &t_targetImgPath);
	// Slot for getting new Source image
	void SlotGetSourceImg(const QString &t_sourceImgPath);
	// Slot for getting new Result image
	void SlotGetResultImg(QImage t_resultImg);
	// Info-slot: type of current proccess
	void SlotCurrProcess(const Program::Status &t_status);
	// Info-slot: process ended normally
	void SlotProcessEnd();
	// Info-slot: process failed with some reason
	void SlotProcError(const QString &t_message);
	// Info-slot: process fatal fail
	void SlotProcessFail();

private slots:
	void on_openTargetImgPB_clicked();
	void on_actionOpenTargetImage_triggered();
	void on_openSourceImgPB_clicked();
	void on_actionOpenSourceImage_triggered();
	void on_actionSaveResult_triggered();
	void on_findSourceImgPB_clicked();
	void on_startColorizationPB_clicked();
	void on_resetPB_clicked();
	void on_actionCreateDatabase_triggered();
	void on_actionOpenDatabase_triggered();
	void on_actionAddImages_triggered();
	void on_actionPreferences_triggered();
	void SlotPassportType(QAction *t_action);
};

#endif // MAINWINDOW_H
