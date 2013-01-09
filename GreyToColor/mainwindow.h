#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QActionGroup>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include "defines.h"
#include "imghandler.h"
#include "idbhandler.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	// Menues and actions
	QMenu *m_fileMenu;
	QAction *m_openGrayImg;
	QAction *m_openColorImg;
	QAction *m_exit;

	QMenu *m_colorizationMenu;
	QActionGroup *m_colorActGroup;
	QAction *m_mWSimple;
	QAction *m_mWNeighbor;

	QMenu *m_IDBMenu;
	QAction *m_addNewPicsToIDB;
	QAction *m_updateIDB;

	// Constructive layouts
	QVBoxLayout *m_vBoxMain;
	QHBoxLayout *m_hBoxImgs;
	QHBoxLayout *m_hBoxButts;
	QVBoxLayout *m_vBoxLow;
	QHBoxLayout *m_hBoxLowLine;

	// Labels for images
	QLabel *m_grayImg;
	QLabel *m_colorImg;
	QLabel *m_resultImg;
	// Label for SKO
	QLabel *m_labelSKO;

	// Buttons for setting images
	QPushButton *m_grayImgButt;
	QPushButton *m_colorImgButt;
	QPushButton *m_startProcButt;
	QPushButton *m_colorIDBImgButt;

	// Lines with info
	QLineEdit *m_lineSKO;

	ImgHandler *m_ih;
	IDBHandler *m_idbh;

	enum ImgLoadStates {NONE,
						ONLY_TARGET,
						ONLY_ORIGINAL,
						BOTH};

	ImgLoadStates m_imgState;

	enum LoadedParts {NONE_PARTS,
						TARGET_IMG};

	LoadedParts m_loadedState;

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void constructWindow();
	void construcMenu();
	void initLabels();
	void initButtons();
	void initLines();
	void constructWindowView();

public slots:
	void slotSetTargetImg(QImage);
	void slotSetResultImg(QImage);
	void slotSetOriginalImg(QImage);
	void slotColoriseButton (int t_lbl);
	void slotGetImgIDBButton(int t_loaded);
	void slotSetSKO(QString t_str);

private slots:
	void slotMethodWSimple();
	void slotMethodWNeighbor();
	void slotWalshSimple();
	void slotWalshNeighbor();

	void slotGetGrayImg();
	void slotGetColorImg();
	void slotGetColorImgFromIDB();

	void slotAddPicsToIDB();
	void slotUpdateIDB();
};

#endif // MAINWINDOW_H
