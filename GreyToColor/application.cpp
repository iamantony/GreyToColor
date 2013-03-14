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
	CreateColorMethHandler();

	ConnectUIandImgHand();
	ConnectUIandIDBHand();
	ConnectUIandColMethHand();
	ConnectImgHandAndIDBHand();
	ConnectImgHandAndColMethHand();

	StartApp();
}

// Construct all objectf for UI
// @input:
// @output:
void Application::CreateUI()
{
	m_mainUI = new MainWindow();

	qRegisterMetaType<Program::Status>("Program::Status");
	qRegisterMetaType<Passport::Type>("Passport::Type");
	qRegisterMetaType<Methods::Type>("Methods::Type");
	qRegisterMetaType<Image>("Image");
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
	m_idbHandler = new IDBHandler();
	m_idbHandlerThread = new QThread();
	m_idbHandler->moveToThread(m_idbHandlerThread);
}

// Construct all objects for Colorization Methods Handler
void Application::CreateColorMethHandler()
{
	m_colorMethHandler = new ColorMethodsHandler();
	m_colorMethHandlerThread = new QThread();
	m_colorMethHandler->moveToThread(m_colorMethHandlerThread);
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

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalGetTargetImg(QString)),
					 m_mainUI,
					 SLOT(SlotGetTargetImg(QString)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalNewSourceImg(const QString &)),
					 m_imgHandler,
					 SLOT(SlotGetNewSourceImg(const QString &)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalCurrentSourceImg(QString)),
					 m_mainUI,
					 SLOT(SlotGetSourceImg(QString)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalGetResultImg(QImage)),
					 m_mainUI,
					 SLOT(SlotGetResultImg(QImage)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalSaveResultImg(const QString &)),
					 m_imgHandler,
					 SLOT(SlotSaveResultImg(const QString &)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalFindSimilarImgInIDB()),
					 m_imgHandler,
					 SLOT(SlotFindSimilarForTarget()));

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

// Create signal-slot connections between UI and IDBHandler object
// @input:
// @output:
void Application::ConnectUIandIDBHand()
{
	QObject::connect(m_mainUI,
					 SIGNAL(SignalUseImgPassport(Passport::Type)),
					 m_idbHandler,
					 SLOT(SlotSetPassportType(Passport::Type)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalNewIDB(QString)),
					 m_idbHandler,
					 SLOT(SlotCreateNewIDB(QString)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalOpenIDB(QString)),
					 m_idbHandler,
					 SLOT(SlotOpenIDB(QString)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalAddImagesToIDB(QStringList)),
					 m_idbHandler,
					 SLOT(SlotAddImagesToIDB(QStringList)));

	QObject::connect(m_idbHandler,
					 SIGNAL(SignalCurrentProc(Program::Status)),
					 m_mainUI,
					 SLOT(SlotCurrProcess(Program::Status)));

	QObject::connect(m_idbHandler,
					 SIGNAL(SignalProcDone()),
					 m_mainUI,
					 SLOT(SlotProcessEnd()));

	QObject::connect(m_idbHandler,
					 SIGNAL(SignalProcError(const QString &)),
					 m_mainUI,
					 SLOT(SlotProcError(const QString &)));

	QObject::connect(m_idbHandler,
					 SIGNAL(SignalProcFatalError()),
					 m_mainUI,
					 SLOT(SlotProcessFail()));
}

// Create signal-slot connections between UI and ColorMethodsHandler object
// @input:
// @output:
void Application::ConnectUIandColMethHand()
{
	QObject::connect(m_mainUI,
					 SIGNAL(SignalUseColorMethod(Methods::Type)),
					 m_colorMethHandler,
					 SLOT(SlotSetMethodType(Methods::Type)));

	QObject::connect(m_mainUI,
					 SIGNAL(SignalStartColorization()),
					 m_colorMethHandler,
					 SLOT(SlotStartColorization()));

	QObject::connect(m_colorMethHandler,
					 SIGNAL(SignalCurrentProc(Program::Status)),
					 m_mainUI,
					 SLOT(SlotCurrProcess(Program::Status)));

	QObject::connect(m_colorMethHandler,
					 SIGNAL(SignalProcDone()),
					 m_mainUI,
					 SLOT(SlotProcessEnd()));

	QObject::connect(m_colorMethHandler,
					 SIGNAL(SignalProcError(const QString &)),
					 m_mainUI,
					 SLOT(SlotProcError(const QString &)));

	QObject::connect(m_colorMethHandler,
					 SIGNAL(SignalProcFatalError()),
					 m_mainUI,
					 SLOT(SlotProcessFail()));
}

// Create signal-slot connections between ImgHandler and IDBHandler objects
// @input:
// @output:
void Application::ConnectImgHandAndIDBHand()
{
	QObject::connect(m_imgHandler,
					 SIGNAL(SignalFindSimilarInIDB(Image)),
					 m_idbHandler,
					 SLOT(SlotFindSimilar(Image)));

	QObject::connect(m_idbHandler,
					 SIGNAL(SignalSimilarImg(QString)),
					 m_imgHandler,
					 SLOT(SlotGetNewSourceImg(QString)));
}

// Create signal-slot connections between ImgHandler and ColorMethodsHandler objects
// @input:
// @output:
void Application::ConnectImgHandAndColMethHand()
{
	QObject::connect(m_imgHandler,
					 SIGNAL(SignalTargetSet(TargetImage*)),
					 m_colorMethHandler,
					 SLOT(SlotGetTargetImg(TargetImage*)));

	QObject::connect(m_imgHandler,
					 SIGNAL(SignalSourceSet(SourceImage*)),
					 m_colorMethHandler,
					 SLOT(SlotGetSourceImg(SourceImage*)));
}

// Start all threads with application objects and show UI
// @input:
// @output:
void Application::StartApp()
{
	m_idbHandlerThread->start();
	m_imgHandlerThread->start();
	m_colorMethHandlerThread->start();

	m_mainUI->show();
}

// Delete all application objects
// @input:
// @output:
void Application::DeleteObjects()
{
	// 1. Disconnect all signals
	DisconnectUIandIDBHand();
	DisconnectUIandImgHand();
	DisconnectUIandColMethHand();
	DisconnectImgHandAndIDBHand();
	DisconnectImgHandAndColMethHand();

	// 2. Stop all threads and delete objects
	DeleteColMethHandler();
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

// Disconnect UI and IDBHandler object
// @input:
// @output:
void Application::DisconnectUIandIDBHand()
{
	m_idbHandler->disconnect(m_mainUI);
	m_mainUI->disconnect(m_idbHandler);
}

// Disconnect UI and ColorMethodsHandler object
// @input:
// @output:
void Application::DisconnectUIandColMethHand()
{
	m_colorMethHandler->disconnect(m_mainUI);
	m_mainUI->disconnect(m_colorMethHandler);
}

// Disconnect ImgHandler and IDBHandler objects
// @input:
// @output:
void Application::DisconnectImgHandAndIDBHand()
{
	m_imgHandler->disconnect(m_idbHandler);
	m_idbHandler->disconnect(m_imgHandler);
}

// Disconnect ImgHandler and IDBHandler objects
// @input:
// @output:
void Application::DisconnectImgHandAndColMethHand()
{
	m_imgHandler->disconnect(m_colorMethHandler);
	m_colorMethHandler->disconnect(m_imgHandler);
}

// Delete all objects for Colorization Methods Handler
// @input:
// @output:
void Application::DeleteColMethHandler()
{
	m_colorMethHandlerThread->quit();

	bool threadStoped = false;
	do
	{
		threadStoped = m_colorMethHandlerThread->wait();
	}
	while( false == threadStoped );

	delete m_colorMethHandlerThread;
	delete m_colorMethHandler;
}

// Delete all objects for Image Database Handler
// @input:
// @output:
void Application::DeleteIDBHandler()
{
	m_idbHandlerThread->quit();

	bool threadStoped = false;
	do
	{
		threadStoped = m_idbHandlerThread->wait();
	}
	while( false == threadStoped );

	delete m_idbHandlerThread;
	delete m_idbHandler;
}

// Delete all objects for Image Handler
// @input:
// @output:
void Application::DeleteImgHandler()
{
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
