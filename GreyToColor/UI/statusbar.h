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
