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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include <QTime>
#include <QDebug>
#include "UI/statusbar.h"
#include "UI/scalelabel.h"
#include "UI/DIALOGS/preferencesdialog.h"
#include "UI/DIALOGS/histogramwindow.h"
#include "IMAGES/COMMON/image.h"
#include "DEFINES/programstatus.h"
#include "DEFINES/mainwindowui.h"
#include "DEFINES/idbs.h"
#include "DEFINES/colorization.h"

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
	Program::Status m_appStatus;

	Passport::Type m_imgPassport;
	Methods::Type m_colorizationMethod;
	LumEqualization::Type m_lumEqualType;

	QImage m_result;

	// == METHODS ==
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	// Call all functions to initialise UI
	void InitUI();
	// Init default settings
	void InitSettings();
	// Creating, applying settings to status bar
	void InitStatusBar();
	// Put default picture to all labels on MainWindow
	void InitImgsLabels();
	// Put default picture to one of three labels on MainWindow
	void InitImg(Images::Types t_imgType);
	// Show warning window with title and some text
	void ShowWarning(const QString &t_title, const QString &t_text);
	// Check if app status if OK (application not performing some calculations)
	bool CanOperate();

	// Automatic colorization: all methods, all luminance equalization types. Test!
	void TestAutoColorization();

signals:
	void SignalNewIDB(const QString &t_name);
	void SignalOpenIDB(const QString &t_name);
	void SignalAddImagesToIDB(const QStringList &t_names);
	void SignalFindSimilarImgInIDB();
	void SignalNewTargetImg(const QString &t_str);
	void SignalNewSourceImg(const QString &t_str);
	void SignalSaveResultImg(const QString &t_imgPath);
	void SignalUseImgPassport(const Passport::Type &t_type);
	void SignalUseColorMethod(const Methods::Type &t_type);
	void SignalUseLumEqual(const LumEqualization::Type &t_type);
	void SignalStartColorization();
	void SignalGetOrigTargImg();
	void SignalGetColorTargImg();
	void SignalGetSourceImg();
	void SignalSendImg(const Image &t_img);

public slots:
	// Slot for getting new Target image
	void SlotGetTargetImg(const QString &t_targetImgPath);
	// Slot for getting new Source image
	void SlotGetSourceImg(const QString &t_sourceImgPath);
	// Slot for getting new Result image
	void SlotGetResultImg(QImage t_resultImg);
	// Slot to set SKO value
	void SlotGetImagesSKO(const double &t_sko);
	// Slot for getting type of image which needs Histogram window
	void SlotGetImgType(const ImageKind::Type &t_type);
	// Get image from Image Handler and send it to Histogram Window
	void SlotRecieveImg(const Image &t_img);
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
	void SlotGetPassportType(const Passport::Type &t_passType);
	void SlotGetColorMethodType(const Methods::Type &t_colorMethodType);
	void SlotGetLumEqualType(const LumEqualization::Type &t_lumEqualType);
	void on_actionFormHist_triggered();
};

#endif // MAINWINDOW_H
