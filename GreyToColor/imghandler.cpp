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

ImgHandler::~ImgHandler()
{
	m_targetOriginal.Clear();
	m_source.Clear();
	m_target.Clear();
}

// This slot get signal to save result (colorized or not) image and send it copy signal to some (MainWindow) UI
// @input:
// - QString - unempty path for saving target image
// @output:
void ImgHandler::SlotSaveResultImg(QString t_imgPath)
{
	if ( true == t_imgPath.isEmpty() )
	{
		qDebug() << "SlotSaveResultImg(): Error - invalid arguments";
		return;
	}

	Image imageToSave = m_target.GetResultImage();
	if ( true == imageToSave.IsNull() )
	{
		qDebug() << "SlotSaveResultImg(): nothing to save";
		emit SignalNoTargetImg();
		return;
	}

	bool imageSaved = imageToSave.SaveImg(t_imgPath);
	if ( false == imageSaved )
	{
		qDebug() << "SlotSaveResultImg(): Error - fail to save result image";
		emit SignalFailTargetImgSave();
		return;
	}
}

// This slot get path to new original image
// @input:
// - QString - unempty path to new original target image
// @output:
void ImgHandler::SlotGetNewTargetImg(const QString &t_imgPath)
{
	if ( true == t_imgPath.isEmpty() )
	{
		qDebug() << "SlotGetNewTargetImg(): Error - invalid arguments";
		return;
	}

	bool originalLoaded = m_targetOriginal.LoadImg(t_imgPath);
	if ( false == originalLoaded )
	{
		qDebug() << "SlotGetNewTargetImg(): Error - can't load original target image";
		emit SignalFailLoadOrigTargImg();
		return;
	}

	bool targetLoaded = m_target.LoadImg(t_imgPath);
	if ( false == targetLoaded )
	{
		qDebug() << "SlotGetNewTargetImg(): Error - can't load target image";
		emit SignalFailLoadTargImg();
		return;
	}

	SendResultImg();
}

// Send out current result image
// @input:
// @output:
void ImgHandler::SendResultImg()
{
	// TODO:
	// - change signal to SignalTargetImgError()

	Image resultImage = m_target.GetResultImage();
	if ( true == resultImage.IsNull() )
	{
		qDebug() << "SendResultImg(): Error - can't get result image";
		emit SignalNoTargetImg();
		return;
	}

	QImage result = resultImage.GetImg();
	if ( true == result.isNull() )
	{
		qDebug() << "SendResultImg(): Error - can't get result image";
		emit SignalNoTargetImg();
		return;
	}

	emit SignalGetResultImg(result);
}
