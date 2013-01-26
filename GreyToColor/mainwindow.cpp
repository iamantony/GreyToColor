#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	InitUI();
}

void MainWindow::InitUI()
{
	ui->setupUi(this);

	m_statusBar = new StatusBar();
	this->setStatusBar(m_statusBar);
}

MainWindow::~MainWindow()
{
	delete ui;
}

// TODO:
// 1) Open image... -> user picked image -> pop up dialog, in which user must choose type of image:
// target (grey) or source (color).
// 2) Resizing of labels on MainWindow
