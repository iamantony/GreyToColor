#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "statusbar.h"

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
};

#endif // MAINWINDOW_H
