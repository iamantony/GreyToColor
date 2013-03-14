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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QThread>
#include "mainwindow.h"
#include "imghandler.h"
#include "idbhandler.h"
#include "colormethodshandler.h"
#include "DEFINES/programstatus.h"
#include "IMAGES/COMMON/image.h"
#include "DEFINES/colorization.h"

class Application : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	MainWindow *m_mainUI;

	ImgHandler *m_imgHandler;
	QThread *m_imgHandlerThread;

	IDBHandler *m_idbHandler;
	QThread *m_idbHandlerThread;

	ColorMethodsHandler *m_colorMethHandler;
	QThread *m_colorMethHandlerThread;

	// == METHODS ==
public:
	explicit Application(QObject *parent = 0);
	~Application();

	// Construct all main objects of application
	void Construct();

private:
	// Construct all objectf for UI
	void CreateUI();
	// Construct all objects for Image Handler
	void CreateImgHandler();
	// Construct all objects for Image Database Handler
	void CreateIDBHandler();
	// Construct all objects for Colorization Methods Handler
	void CreateColorMethHandler();
	// Create signal-slot connections between UI and ImgHandler object
	void ConnectUIandImgHand();
	// Create signal-slot connections between UI and IDBHandler object
	void ConnectUIandIDBHand();
	// Create signal-slot connections between UI and ColorMethodsHandler object
	void ConnectUIandColMethHand();
	// Create signal-slot connections between ImgHandler and IDBHandler objects
	void ConnectImgHandAndIDBHand();
	// Create signal-slot connections between ImgHandler and ColorMethodsHandler objects
	void ConnectImgHandAndColMethHand();
	// Start all threads with application objects and show UI
	void StartApp();
	// Delete all application objects
	void DeleteObjects();
	// Disconnect UI and ImgHandler object
	void DisconnectUIandImgHand();
	// Disconnect UI and IDBHandler object
	void DisconnectUIandIDBHand();
	// Disconnect UI and ColorMethodsHandler object
	void DisconnectUIandColMethHand();
	// Disconnect ImgHandler and IDBHandler objects
	void DisconnectImgHandAndIDBHand();
	// Disconnect ImgHandler and IDBHandler objects
	void DisconnectImgHandAndColMethHand();
	// Delete all objects for Colorization Methods Handler
	void DeleteColMethHandler();
	// Delete all objects for Image Database Handler
	void DeleteIDBHandler();
	// Delete all objects for Image Handler
	void DeleteImgHandler();
	// Delete all objectf for UI
	void DeleteUI();
};

#endif // APPLICATION_H
