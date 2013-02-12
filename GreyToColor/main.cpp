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

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "imghandler.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ImgHandler imgHandler;
	MainWindow w;

	QObject::connect(&w,
					 SIGNAL(SignalSaveResultImg()),
					 &imgHandler,
					 SLOT(SlotSaveResultImg()));

	QObject::connect(&imgHandler,
					 SIGNAL(SignalGetResultImg(QImage)),
					 &w,
					 SLOT(SlotSaveResult(QImage)));

	QObject::connect(&w,
					 SIGNAL(SignalStrToOriginalImg(QString)),
					 &imgHandler,
					 SLOT(SlotGetOriginalImg(QString)));

	w.show();

	return a.exec();
}
