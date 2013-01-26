#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QProgressBar>
#include <QLabel>
#include <QDebug>
#include "DEFINES/programstatus.h"

#define PROGRESS_MIN 0
#define PROGRESS_MAX 100

class StatusBar : public QStatusBar
{
	Q_OBJECT

	// == DATA ==
private:
	QLabel *m_infoString;
	QProgressBar *m_progrBar;

	// == METHODS ==
public:
	explicit StatusBar(QWidget *parent = 0);

	// Get minimum value of progress, which could be shown
	// @output: positive integer value
	int GetProgressMin();

	// Get maximum value of progress, which could be shown
	// @output: positive integer value
	int GetProgressMax();

	// Set new progress value of some process
	// @input: positive integer value between PROGRESS_MIN and PROGRESS_MAX
	void SetProcesProgress(const int &t_progress);

	// Reset progress bar to it's minimum value
	void ResetProcesProgress();

	// Set program status
	void SetStatus(Program::Status t_status);

private:
	void SetInfoString();
	void SetProgressBar();
};

#endif // STATUSBAR_H
