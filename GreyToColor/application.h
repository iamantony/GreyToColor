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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QThread>
#include "mainwindow.h"
#include "imghandler.h"

class Application : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	MainWindow *m_mainUI;
	QThread *m_mainUIThread;

	ImgHandler *m_imgHandler;
	QThread *m_imgHandlerThread;

	// == METHODS ==
public:
	explicit Application(QObject *parent = 0);
	~Application();

	// Construct all main objects of application
	void Construct();

signals:

public slots:

};

#endif // APPLICATION_H
