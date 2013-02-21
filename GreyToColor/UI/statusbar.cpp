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

#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent):
	QStatusBar(parent)
{
	SetInfoString();
	SetProgressBar();
}

// Setup information string
// @input:
// @output:
void StatusBar::SetInfoString()
{
	m_infoString = new QLabel();
	SetStatus(Program::OK);

	this->insertPermanentWidget(0, m_infoString, 70);
}

// Set Progress Bar as permanent widget
// @input:
// @output:
void StatusBar::SetProgressBar()
{
	m_progrBar = new QProgressBar(this);

	m_progrBar->setMinimum(PROGRESS_MIN);
	m_progrBar->setMaximum(PROGRESS_MAX);

	this->insertPermanentWidget(1, m_progrBar, 30);
}

// Get minimum value of progress, which could be shown
// @input:
// @output:
// - int - positive integer value
int StatusBar::GetProgressMin()
{
	int min = m_progrBar->minimum();
	if ( min != PROGRESS_MIN )
	{
		qDebug() << "StatusBar::GetProgressMin(): wrong minimum progress value. Set to default.";
		m_progrBar->setMinimum(PROGRESS_MIN);
		min = PROGRESS_MIN;
	}

	return min;
}

// Get maximum value of progress, which could be shown
// @input:
// @output:
// - int - positive integer value
int StatusBar::GetProgressMax()
{
	int max = m_progrBar->maximum();
	if ( max != PROGRESS_MAX )
	{
		qDebug() << "StatusBar::GetProgressMin(): wrong maximum progress value. Set to default.";
		m_progrBar->setMaximum(PROGRESS_MAX);
		max = PROGRESS_MAX;
	}

	return max;
}

// Set new progress value of some process
// @input:
// - int - positive integer value between PROGRESS_MIN and PROGRESS_MAX
// @output:
void StatusBar::SetProcesProgress(const int &t_progress)
{
	if ( (t_progress < PROGRESS_MIN) || (PROGRESS_MAX < t_progress) )
	{
		qDebug() << "StatusBar::SetProcesProgress(): Error - invalid progress value:" << t_progress;
		return;
	}

	m_progrBar->setValue(t_progress);
}

// Reset progress bar to it's minimum value
// @input:
// @output:
void StatusBar::ResetProcesProgress()
{
	m_progrBar->reset();
}

// Set program status
// @input:
// - Program::Status - one of the existed Program Statuses
// @output:
void StatusBar::SetStatus(Program::Status t_status)
{
	switch(t_status)
	{
		case Program::OK:
			m_infoString->setText(tr("OK"));
			break;

		case Program::COLORIZATION:
			m_infoString->setText(tr("Colorization of grey image..."));
			break;

		case Program::SEARCHING_IMAGE_IN_DB:
			m_infoString->setText(tr("Searching for color image in database..."));
			break;

		case Program::DB_FORMING:
			m_infoString->setText(tr("Updating database of images..."));
			break;

		case Program::ERROR:
			m_infoString->setText(tr("Error!"));
			break;

		case Program::DEFAULT_LAST:
		default:
			qDebug() <<"StatusBar::SetStatus(): Error - invalid status";
	}
}
