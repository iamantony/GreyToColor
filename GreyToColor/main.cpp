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

	QObject::connect(&imgHandler,
					 SIGNAL(SignalGetResultImg(QImage)),
					 &w,
					 SLOT(SlotGetResultImg(QImage)));

	QObject::connect(&w,
					 SIGNAL(SignalSaveResultImg(QString)),
					 &imgHandler,
					 SLOT(SlotSaveResultImg(QString)));

	QObject::connect(&imgHandler,
					 SIGNAL(SignalFailLoadOrigTargImg()),
					 &w,
					 SLOT(SlotFailLoadTargetImg()));

	QObject::connect(&imgHandler,
					 SIGNAL(SignalFailLoadTargImg()),
					 &w,
					 SLOT(SlotFailLoadTargetImg()));

	QObject::connect(&imgHandler,
					 SIGNAL(SignalNoTargetImg()),
					 &w,
					 SLOT(SlotNoTargetImg()));

	QObject::connect(&imgHandler,
					 SIGNAL(SignalFailTargetImgSave()),
					 &w,
					 SLOT(SlotFailSaveTargetImg()));

	QObject::connect(&w,
					 SIGNAL(SignalNewTargetImg(QString)),
					 &imgHandler,
					 SLOT(SlotGetNewTargetImg(QString)));

	w.show();

	return a.exec();
}
