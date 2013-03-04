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

#include "application.h"

Application::Application(QObject *parent) :
	QObject(parent)
{
}

Application::~Application()
{
	// TODO:
	// - stop threads
}

// Construct all main objects of application
void Application::Construct()
{
	m_mainUI = new MainWindow();
	m_mainUIThread = new QThread(this);
	m_mainUI->moveToThread(m_mainUIThread);

	m_imgHandler = new ImgHandler(this);
	m_imgHandlerThread = new QThread(this);
	m_imgHandler->moveToThread(m_imgHandlerThread);

	QObject::connect(m_mainUI,
					 SIGNAL(SignalNewTargetImg(const QString &)),
					 m_imgHandler,
					 SLOT(SlotGetNewTargetImg(const QString &)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalFailLoadOrigTargImg()),
					 m_mainUI,
					 SLOT(SlotFailLoadTargetImg()));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalFailLoadTargImg()),
					 m_mainUI,
					 SLOT(SlotFailLoadTargetImg()));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalNoTargetImg()),
					 m_mainUI,
					 SLOT(SlotNoTargetImg()));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalFailTargetImgSave()),
					 m_mainUI,
					 SLOT(SlotFailSaveTargetImg()));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalNewSourceImg(const QString &)),
					 m_imgHandler,
					 SLOT(SlotGetNewSourceImg(const QString &)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalFailLoadSourceImg()),
					 m_mainUI,
					 SLOT(SlotFailLoadSourceImg()));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalGetResultImg(QImage)),
					 m_mainUI,
					 SLOT(SlotGetResultImg(QImage)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalNoResultImg()),
					 m_mainUI,
					 SLOT(SlotNoResultImg()));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalSaveResultImg(const QString &)),
					 m_imgHandler,
					 SLOT(SlotSaveResultImg(const QString &)));

	m_imgHandlerThread->start();
	m_mainUIThread->start();

	m_mainUI->show();
}
