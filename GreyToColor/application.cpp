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
	// Clear all images (show progress)
	DeleteObjects();
}

// Construct all main objects of application
// @input:
// @output:
void Application::Construct()
{
	CreateUI();
	CreateImgHandler();
	CreateIDBHandler();

	ConnectUIandImgHand();

	StartApp();
}

// Construct all objectf for UI
// @input:
// @output:
void Application::CreateUI()
{
	m_mainUI = new MainWindow();

	qRegisterMetaType<Program::Status>("Program::Status");
}

// Construct all objects for Image Handler
// @input:
// @output:
void Application::CreateImgHandler()
{
	m_imgHandler = new ImgHandler();
	m_imgHandlerThread = new QThread();
	m_imgHandler->moveToThread(m_imgHandlerThread);
}

// Construct all objects for Image Database Handler
// @input:
// @output:
void Application::CreateIDBHandler()
{

}

// Create signal-slot connections between UI and ImgHandler object
// @input:
// @output:
void Application::ConnectUIandImgHand()
{
	QObject::connect(m_mainUI,
					 SIGNAL(SignalNewTargetImg(const QString &)),
					 m_imgHandler,
					 SLOT(SlotGetNewTargetImg(const QString &)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalNewSourceImg(const QString &)),
					 m_imgHandler,
					 SLOT(SlotGetNewSourceImg(const QString &)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalGetResultImg(QImage)),
					 m_mainUI,
					 SLOT(SlotGetResultImg(QImage)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalSaveResultImg(const QString &)),
					 m_imgHandler,
					 SLOT(SlotSaveResultImg(const QString &)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalCurrentProc(Program::Status)),
					 m_mainUI,
					 SLOT(SlotCurrProcess(Program::Status)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalProcDone()),
					 m_mainUI,
					 SLOT(SlotProcessEnd()));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalProcError(const QString &)),
					 m_mainUI,
					 SLOT(SlotProcError(const QString &)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalProcFatalError()),
					 m_mainUI,
					 SLOT(SlotProcessFail()));
}

// Start all threads with application objects and show UI
// @input:
// @output:
void Application::StartApp()
{
	m_imgHandlerThread->start();

	m_mainUI->show();
}

// Delete all application objects
// @input:
// @output:
void Application::DeleteObjects()
{
	// 1. Disconnect all signals
	DisconnectUIandImgHand();

	// 2. Stop all threads and delete objects
	DeleteIDBHandler();
	DeleteImgHandler();

	// 3. Delete UI
	DeleteUI();
}

// Disconnect UI and ImgHandler object
// @input:
// @output:
void Application::DisconnectUIandImgHand()
{
	m_imgHandler->disconnect(m_mainUI);
	m_mainUI->disconnect(m_imgHandler);
}

// Delete all objects for Image Database Handler
// @input:
// @output:
void Application::DeleteIDBHandler()
{

}

// Delete all objects for Image Handler
// @input:
// @output:
void Application::DeleteImgHandler()
{
	m_imgHandler->Clear();


	m_imgHandlerThread->quit();

	bool threadStoped = false;
	do
	{
		threadStoped = m_imgHandlerThread->wait();
	}
	while( false == threadStoped );

	delete m_imgHandlerThread;
	delete m_imgHandler;
}

// Delete all objectf for UI
// @input:
// @output:
void Application::DeleteUI()
{
	delete m_mainUI;
}
