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

#include "imghandler.h"

ImgHandler::ImgHandler(QObject *parent) :
	QObject(parent)
{
}

// This slot get signal to save result (colorized or not) image and send it copy signal to some (MainWindow) UI
void ImgHandler::SlotSaveResultImg()
{
	// TODO:
	// save target image, not original

	emit SignalGetResultImg(m_original.GetImg());
}

// This slot get path to new original image
void ImgHandler::SlotGetOriginalImg(const QString &t_imgPath)
{
	if ( true == t_imgPath.isEmpty() )
	{
		qDebug() << "SlotGetOriginalImg(): Error - invalid arguments";
		return;
	}

	bool originalLoaded = m_original.LoadImg(t_imgPath);
	if ( false == originalLoaded )
	{
		qDebug() << "SlotGetOriginalImg(): Error - can't load original image";
		return;
	}
}
