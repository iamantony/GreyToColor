#include "mainwindow_old.h"

MainWindowOld::MainWindowOld(QWidget *parent) :
	QMainWindow(parent)
{
//	m_ih = new ImgHandler();
//	connect(m_ih, SIGNAL(signalSetTargetImg(QImage)), this, SLOT(slotSetTargetImg(QImage)));
//	connect(m_ih, SIGNAL(signalSetResultImg(QImage)), this, SLOT(slotSetResultImg(QImage)));
//	connect(m_ih, SIGNAL(signalSetOriginalImg(QImage)), this, SLOT(slotSetOriginalImg(QImage)));

//	connect(m_ih, SIGNAL(signalEnableProcButtn(int)), this, SLOT(slotColoriseButton(int)));
//	connect(m_ih, SIGNAL(signalEnableProcButtn(int)), this, SLOT(slotGetImgIDBButton(int)));
//	connect(m_ih, SIGNAL(signalImagesSKO(QString)), this, SLOT(slotSetSKO(QString)));

//	m_idbh = new IDBHandler();

//	m_imgState = NONE;
//	m_loadedState = NONE_PARTS;

//	constructWindow();
//	construcMenu();
//	initLabels();
//	initButtons();
//	initLines();
//	constructWindowView();
}

MainWindowOld::~MainWindowOld()
{
//	delete m_ih;
//	delete m_idbh;
}

//// Set main parameters for Main Window
//void MainWindow::constructWindow()
//{
//	this->setGeometry(X_WINDOW, Y_WINDOW, W_WINDOW, H_WINDOW);
////	this->setFixedSize(W_WINDOW, H_WINDOW);
//}

//void MainWindow::construcMenu()
//{
//	// Set up File menu
//	m_fileMenu = new QMenu(MENU_FILE);

//	m_openGrayImg = new QAction (ACTION_OPEN_GRAY, m_fileMenu);
//	connect(m_openGrayImg, SIGNAL(triggered()), this, SLOT(slotGetGrayImg()));
//	m_fileMenu->addAction(m_openGrayImg);

//	m_openColorImg = new QAction (ACTION_OPEN_COLOR, m_fileMenu);
//	connect(m_openColorImg, SIGNAL(triggered()), this, SLOT(slotGetColorImg()));
//	m_fileMenu->addAction(m_openColorImg);

//	m_fileMenu->addSeparator();

//	m_exit = new QAction (ACTION_EXIT, m_fileMenu);
//	connect(m_exit, SIGNAL(triggered()), this, SLOT(close()));
//	m_fileMenu->addAction(m_exit);

//	// Set up Colorization menu
//	m_colorizationMenu = new QMenu (MENU_COLORIZATION);

//	m_colorActGroup = new QActionGroup(m_colorizationMenu);
//	m_colorActGroup->setExclusive(true);

//	m_mWSimple = new QAction (ACTION_MW_SIMPLE, m_colorizationMenu);
//	connect(m_mWSimple, SIGNAL(triggered()), this, SLOT(slotMethodWSimple()));
//	m_colorActGroup->addAction(m_mWSimple);
//	m_mWSimple->setChecked(true);
//	m_colorizationMenu->addAction(m_mWSimple);

//	m_mWNeighbor = new QAction (ACTION_MW_NEIGHBOR, m_colorizationMenu);
//	connect(m_mWNeighbor, SIGNAL(triggered()), this, SLOT(slotMethodWNeighbor()));
//	m_colorActGroup->addAction(m_mWNeighbor);
//	m_colorizationMenu->addAction(m_mWNeighbor);

//	// Set up Database menu
//	m_IDBMenu = new QMenu(MENU_DATABASE);

//	m_addNewPicsToIDB = new QAction(ACTION_ADD_NEW_PICS_IDB, m_IDBMenu);
//	connect(m_addNewPicsToIDB, SIGNAL(triggered()), this, SLOT(slotAddPicsToIDB()));
//	m_IDBMenu->addAction(m_addNewPicsToIDB);

//	m_updateIDB = new QAction(ACTION_UPDATE_IDB, m_IDBMenu);
//	connect(m_updateIDB, SIGNAL(triggered()), this, SLOT(slotUpdateIDB()));
//	m_IDBMenu->addAction(m_updateIDB);

//	// Set up main menu
//	this->menuBar()->addMenu(m_fileMenu);
//	this->menuBar()->addMenu(m_colorizationMenu);
//	this->menuBar()->addMenu(m_IDBMenu);

//	this->menuBar()->show();
//}

//// Initialisation of labels, which will show pictures
//void MainWindow::initLabels()
//{
//	// color labels
//	QPixmap pm(W_IMG, H_IMG);

//	m_grayImg = new QLabel(this);
//	m_grayImg->setGeometry(X_FIRST_IMG_OFFSET, Y_IMG_OFFSET, W_IMG, H_IMG);
//	pm.fill(Qt::red);
//	m_grayImg->setPixmap(pm);

//	m_resultImg = new QLabel(this);
//	m_resultImg->setGeometry(X_FIRST_IMG_OFFSET + W_IMG, Y_IMG_OFFSET, W_IMG, H_IMG);
//	pm.fill(Qt::green);
//	m_resultImg->setPixmap(pm);

//	m_colorImg = new QLabel(this);
//	m_colorImg->setGeometry(X_FIRST_IMG_OFFSET + 2*W_IMG, Y_IMG_OFFSET, W_IMG, H_IMG);
//	pm.fill(Qt::blue);
//	m_colorImg->setPixmap(pm);
//}

//// Initialisation of buttons, which will perform some usefull actions
//void MainWindow::initButtons()
//{
//	int yOffset = 0 /*Y_IMG_OFFSET + H_IMG + Y_BUTT_OFFSET*/;
//	int xOffset = 0 /*X_FIRST_IMG_OFFSET + X_FIRST_BUTT_OFFSET*/;

//	m_grayImgButt = new QPushButton(BUTTON_GREY_IMG ,this);
//	m_grayImgButt->setGeometry(xOffset, yOffset, W_BUTT, H_2LINE_BUTT);
//	connect(m_grayImgButt, SIGNAL(pressed()), this, SLOT(slotGetGrayImg()));

//	m_startProcButt = new QPushButton(BUTTON_START ,this);
//	m_startProcButt->setGeometry(xOffset/* + W_IMG*/, yOffset, W_BUTT, H_1LINE_BUTT);
//	m_startProcButt->setEnabled(false);

//	m_colorImgButt = new QPushButton(BUTTON_COLOR_IMG ,this);
//	m_colorImgButt->setGeometry(xOffset/* + 2*W_IMG*/, yOffset, W_BUTT, H_2LINE_BUTT);
//	connect(m_colorImgButt, SIGNAL(pressed()), this, SLOT(slotGetColorImg()));

//	m_colorIDBImgButt = new QPushButton(BUTTON_COLOR_IDB_IMG, this);
//	m_colorIDBImgButt->setGeometry(xOffset/* + 2*W_IMG*/, yOffset, W_BUTT, H_3LINE_BUTT);
//	connect(m_colorIDBImgButt, SIGNAL(pressed()), this, SLOT(slotGetColorImgFromIDB()));
//	m_colorIDBImgButt->setEnabled(false);
//}

//void MainWindow::initLines()
//{
//	m_labelSKO = new QLabel(LABEL_SKO, this);
//	int xOffset = 0 /*X_FIRST_IMG_OFFSET + X_FIRST_BUTT_OFFSET + W_IMG*/;
//	int yOffset = 0 /*Y_IMG_OFFSET + H_IMG + 2*Y_BUTT_OFFSET + H_BUTT*/;
//	m_labelSKO->setGeometry(xOffset, yOffset, 60, 40);

//	m_lineSKO = new QLineEdit(this);
//	m_lineSKO->setReadOnly(true);
//	m_lineSKO->setGeometry(xOffset + 40, yOffset, W_LINE_SKO, H_LINE_SKO);
//}

//void MainWindow::constructWindowView()
//{
//	m_hBoxImgs = new QHBoxLayout(this);
//	m_hBoxImgs->addWidget(m_grayImg);
//	m_hBoxImgs->addWidget(m_resultImg);
//	m_hBoxImgs->addWidget(m_colorImg);

//	m_hBoxButts = new QHBoxLayout(this);
//	m_hBoxButts->addStretch(3);
//	m_hBoxButts->addWidget(m_grayImgButt);
//	m_hBoxButts->addStretch(6);
//	m_hBoxButts->addWidget(m_startProcButt);
//	m_hBoxButts->addStretch(4);
//	m_hBoxButts->addWidget(m_colorImgButt);
//	m_hBoxButts->addStretch(1);
//	m_hBoxButts->addWidget(m_colorIDBImgButt);
//	m_hBoxButts->addStretch(1);

//	m_hBoxLowLine = new QHBoxLayout(this);
//	m_hBoxLowLine->addStretch(1);
//	m_hBoxLowLine->addWidget(m_labelSKO);
//	m_hBoxLowLine->addWidget(m_lineSKO);
//	m_hBoxLowLine->addStretch(1);

//	m_vBoxLow = new QVBoxLayout(this);
//	m_vBoxLow->addLayout(m_hBoxButts);
//	m_vBoxLow->addLayout(m_hBoxLowLine);

//	m_vBoxMain = new QVBoxLayout(this);
//	m_vBoxMain->addLayout(m_hBoxImgs);
//	m_vBoxMain->addLayout(m_vBoxLow);

//	QWidget *wdt = new QWidget(this);
//	wdt->setLayout(m_vBoxMain);

//	this->setCentralWidget(wdt);
//}

//// Write value of SKO to m_lineSKO
//void MainWindow::slotSetSKO(QString t_str)
//{
//	m_lineSKO->setText(t_str);
//}

//void MainWindow::slotGetGrayImg()
//{
//	QString fName = QFileDialog::getOpenFileName(this, "Open target image...", QDir::currentPath(),
//													  "IMG files (*.png *.jpg *.bmp)");

//	if(fName.isEmpty())
//		return;

//	m_ih->getGrayImg(fName);
//}

//void MainWindow::slotGetColorImg()
//{
//	QString fName = QFileDialog::getOpenFileName(this, "Open target image...", QDir::currentPath(),
//													  "IMG files (*.png *.jpg *.bmp)");

//	if(fName.isEmpty())
//		return;

//	m_ih->getColorImg(fName);
//}

//void MainWindow::slotGetColorImgFromIDB()
//{
//	QImage targetImg = m_ih->getImg(TARGET);

//	QString fName = m_idbh->FindSameImg(targetImg);

//	if(fName.isEmpty())
//		return;

//	m_ih->getColorImg(fName);
//}

//// connect start buttom to method Walsh Simple
//void MainWindow::slotMethodWSimple()
//{
//	disconnect(m_startProcButt, SIGNAL(clicked()), 0, 0);
//	connect(m_startProcButt, SIGNAL(clicked()), this, SLOT(slotWalshSimple()));
//}

//// connect start buttom to method Walsh Neighbor
//void MainWindow::slotMethodWNeighbor()
//{
//	disconnect(m_startProcButt, SIGNAL(clicked()), 0, 0);
//	connect(m_startProcButt, SIGNAL(clicked()), this, SLOT(slotWalshNeighbor()));
//}

//// start first method of colorization: Walsh Simple
//void MainWindow::slotWalshSimple()
//{
//	QImage result;
//	result = m_ih->startImgColorizationWSimple();
//	QImage scaledResult = result.scaled(W_IMG, H_IMG, Qt::KeepAspectRatio);
//	m_resultImg->setPixmap(QPixmap::fromImage(scaledResult));
//}

//// start second method of colorization: Walsh Neighbor
//void MainWindow::slotWalshNeighbor()
//{
//	QImage result;
//	result = m_ih->startImgColorizationWNeighbor();
//	QImage scaledResult = result.scaled(W_IMG, H_IMG, Qt::KeepAspectRatio);
//	m_resultImg->setPixmap(QPixmap::fromImage(scaledResult));
//}

//void MainWindow::slotSetTargetImg(QImage t_imgTarg)
//{
//	m_grayImg->setPixmap(QPixmap::fromImage(t_imgTarg));
//}

//void MainWindow::slotSetResultImg(QImage t_imgRes)
//{
//	m_resultImg->setPixmap(QPixmap::fromImage(t_imgRes));
//}

//void MainWindow::slotSetOriginalImg(QImage t_imgOrig)
//{
//	m_colorImg->setPixmap(QPixmap::fromImage(t_imgOrig));
//}

//// decide whether we schould activate button "Colorise" or not
//void MainWindow::slotColoriseButton (int t_lbl)
//{
//	switch (m_imgState)
//	{
//		case (NONE):
//		{
//			if (t_lbl == TARGET || t_lbl == RESULT)
//				m_imgState = ONLY_TARGET;
//			else if (t_lbl == ORIGINAL)
//				m_imgState = ONLY_ORIGINAL;
//		}
//		break;
//		case (ONLY_TARGET):
//		{
//			if(t_lbl == ORIGINAL)
//				m_imgState = BOTH;
//		}
//		break;
//		case (ONLY_ORIGINAL):
//		{
//			if(t_lbl == TARGET || t_lbl == RESULT)
//				m_imgState = BOTH;
//		}
//		break;
//		case (BOTH):
//		break;
//	}

//	// are we ready to enable button "Colorise"?
//	if (m_imgState == BOTH)
//		m_startProcButt->setEnabled(true);
//}

//void MainWindow::slotGetImgIDBButton(int t_loaded)
//{
//	switch(m_loadedState)
//	{
//		case (NONE_PARTS):
//		{
//			if ( TARGET == t_loaded )
//			{
//				m_loadedState = TARGET_IMG;
//			}
//		}
//		break;
//		case (TARGET_IMG):
//		break;
//	}

//	if ( TARGET_IMG == m_loadedState )
//	{
//		m_colorIDBImgButt->setEnabled(true);
//	}
//}

//void MainWindow::slotAddPicsToIDB()
//{
//	QStringList namesOfImagesToAdd =
//			QFileDialog::getOpenFileNames(this, "Select images to add to database...",
//										QDir::currentPath(),
//										"IMG files (*.png *.jpg *.bmp)");

//	if ( true == namesOfImagesToAdd.isEmpty() )
//	{
//		return;
//	}

//	m_idbh->AddImgsToDatabase(namesOfImagesToAdd);
//}

//void MainWindow::slotUpdateIDB()
//{
//	m_idbh->UpdateIDB();
//}

