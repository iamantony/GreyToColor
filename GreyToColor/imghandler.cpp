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
	Clear();
}

// Clear all data
// @input:
// @output:
void ImgHandler::Clear()
{
	m_targetOriginal.Clear();
	m_source.Clear();
	m_target.Clear();
}

// This slot get signal to save result (colorized or not) image and send it copy signal to some (MainWindow) UI
// @input:
// - QString - unempty path for saving target image
// @output:
void ImgHandler::SlotSaveResultImg(const QString &t_imgPath)
{
	if ( true == t_imgPath.isEmpty() )
	{
		qDebug() << "SlotSaveResultImg(): Error - invalid arguments";
		return;
	}

	emit SignalCurrentProc(Program::SAVING);

	if ( false == m_target.HasImage() )
	{
		qDebug() << "SlotSaveResultImg(): Error - no Target Image";
		emit SignalProcError(tr("Can't save Result image because ther is no Target Image"));
		return;
	}

	Image imageToSave = m_target.GetResultImage();
	if ( true == imageToSave.IsNull() )
	{
		qDebug() << "SlotSaveResultImg(): Error - nothing to save";
		emit SignalProcError(tr("Can't save Result image: nothing to save"));
		return;
	}

	bool imageSaved = imageToSave.SaveImg(t_imgPath);
	if ( false == imageSaved )
	{
		qDebug() << "SlotSaveResultImg(): Error - fail to save result image";
		emit SignalProcError(tr("Can't save Result image"));
		return;
	}

	emit SignalProcDone();
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

	emit SignalCurrentProc(Program::LOAD_TARGET);

	bool originalLoaded = m_targetOriginal.LoadImg(t_imgPath);
	if ( false == originalLoaded )
	{
		qDebug() << "SlotGetNewTargetImg(): Error - can't load original target image";
		emit SignalProcError(tr("Can't load original Target Image. Try another one"));
		return;
	}

	bool targetLoaded = m_target.LoadImg(t_imgPath);
	if ( false == targetLoaded )
	{
		qDebug() << "SlotGetNewTargetImg(): Error - can't load target image";
		emit SignalProcError(tr("Can't load Target Image. Try another one"));
		return;
	}

	GetGreyTarget();

	emit SignalProcDone();
}

// Send greyscale version of target image
void ImgHandler::GetGreyTarget()
{
	if( true == m_targetOriginal.IsNull() )
	{
		qDebug() << "GetGreyTarget(): Error - no Target Original Image";
		emit SignalProcError(tr("Can't get greyscaled image from empty Target Image"));
		return;
	}

	QImage target = m_targetOriginal.GetImg();
	if ( true == target.isNull() )
	{
		qDebug() << "GetGreyTarget(): Error - can't get Target Original Image";
		emit SignalProcError(tr("No Target Image"));
		return;
	}

	CandidateImage greyCand;
	bool imgSet = greyCand.SetColorImg(target);
	if ( false == imgSet )
	{
		qDebug() << "GetGreyTarget(): Error - can't set Candidate Image";
		emit SignalProcError(tr("Fail to set Target Image as Candidate Image"));
		return;
	}

	Image greyTarget = greyCand.GetGreyImg();
	if ( true == greyTarget.IsNull() )
	{
		qDebug() << "GetGreyTarget(): Error - can't get grey Target Image";
		emit SignalProcError(tr("Fail to greyscale Target Image"));
		return;
	}

	QImage greyscaledTarget = greyTarget.GetImg();
	if ( true == greyscaledTarget.isNull() )
	{
		qDebug() << "GetGreyTarget(): Error - can't get greyscaled image";
		emit SignalProcError(tr("Fail to get grey Target Image"));
		return;
	}

	emit SignalGetResultImg(greyscaledTarget);
}

// Send out current result image
// @input:
// @output:
void ImgHandler::SendResultImg()
{
	if ( false == m_target.HasImage() )
	{
		qDebug() << "SendResultImg(): Error - no Target Image";
		emit SignalProcError(tr("No Target Image - No Result Image"));
		return;
	}

	Image resultImage = m_target.GetResultImage();
	if ( true == resultImage.IsNull() )
	{
		qDebug() << "SendResultImg(): Error - can't get result image";
		emit SignalProcError(tr("Can't get Target Image"));
		return;
	}

	QImage result = resultImage.GetImg();
	if ( true == result.isNull() )
	{
		qDebug() << "SendResultImg(): Error - can't get result image";
		emit SignalProcError(tr("Can't get Result Image"));
		return;
	}

	emit SignalGetResultImg(result);
}

// This slot get path to new source image
// @input:
// - QString - unempty path to new source image
// @output:
void ImgHandler::SlotGetNewSourceImg(const QString &t_imgPath)
{
	if ( true == t_imgPath.isEmpty() )
	{
		qDebug() << "SlotGetNewSourceImg(): Error - invalid arguments";
		return;
	}

	emit SignalCurrentProc(Program::LOAD_SOURCE);

	bool sourceLoaded = m_source.LoadImg(t_imgPath);
	if ( false == sourceLoaded )
	{
		qDebug() << "SlotGetNewSourceImg(): Error - can't load Source Image";
		emit SignalProcError(tr("Can't load Source Image. Try another one"));
		return;
	}

	emit SignalCurrentSourceImg(t_imgPath);
	emit SignalProcDone();
}

// Start process of searching image in IDB
// @input:
// @output:
void ImgHandler::SlotFindSimilarForTarget()
{
	Image currentTarget = m_target.GetCurrentImage();
	if ( true == currentTarget.IsNull() )
	{
		qDebug() << "SlotSearchSimilarImgForTarget(): Error - no Target Image";
		emit SignalProcError(tr("Target Image is not loaded yet"));
		return;
	}

	emit SignalFindSimilarInIDB(currentTarget);
}
