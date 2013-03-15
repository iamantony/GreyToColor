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

#include "statusbar.h"

QProgressBar *StatusBar::m_progrBar = NULL;
int StatusBar::m_maxEntries = 0;
int StatusBar::m_entriesInOnePercent = 0;
int StatusBar::m_currEntriesNum = 0;

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
	return PROGRESS_MIN;
}

// Get maximum value of progress, which could be shown
// @input:
// @output:
// - int - positive integer value
int StatusBar::GetProgressMax()
{
	return m_maxEntries;
}

// Set max number of entries
// @input:
// - int - positive integer value
// @output:
void StatusBar::SetMaxProcesEntries(const int t_max)
{
	if ( t_max <= 0 )
	{
		qDebug() << "SetMaxEntries(): Error - invalid arguments";
		return;
	}

	m_maxEntries = t_max;
	m_entriesInOnePercent = m_maxEntries / PROGRESS_MAX;
	m_currEntriesNum = 0;
}

// Signal to progress bar that we have one more new entry
// @input:
// @output:
void StatusBar::AddProcesEntry()
{
	m_currEntriesNum++;
	if ( m_currEntriesNum == m_entriesInOnePercent )
	{
		m_currEntriesNum = 0;
		int currProgress = m_progrBar->value();
		currProgress++;
		if ( PROGRESS_MAX < currProgress )
		{
			currProgress = PROGRESS_MAX;
		}

		m_progrBar->setValue(currProgress);
	}
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

		case Program::LOAD_TARGET:
			m_infoString->setText(tr("Loadin Target Image..."));
			break;

		case Program::LOAD_SOURCE:
			m_infoString->setText(tr("Loadin Source Image..."));
			break;

		case Program::CALC_TARGET:
			m_infoString->setText(tr("Calculating pixels of Target Image..."));
			break;

		case Program::CALC_SOURCE:
			m_infoString->setText(tr("Calculating pixels of Source Image..."));
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

		case Program::SAVING:
			m_infoString->setText(tr("Saving Result image..."));
			break;

		case Program::ERR:
			m_infoString->setText(tr("Error!"));
			break;

		case Program::DEFAULT_LAST:
		default:
			qDebug() <<"StatusBar::SetStatus(): Error - invalid status";
	}
}
