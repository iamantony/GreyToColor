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

#include "scalelabel.h"

ScaleLabel::ScaleLabel(QWidget *parent) :
	QLabel(parent)
{
}

// Set image to label
// @input:
// - t_image - unnull loaded image
// @output:
// - true - image set
// - false - can't set image
bool ScaleLabel::SetImage(const QImage &t_image)
{
	if ( true == t_image.isNull() )
	{
		return;
	}

	m_originalImg = t_image;

	SetImgOnLabel();

	return true;
}

// Set image to label
// @input:
// - t_pathToImg - unnull path to existing image
// @output:
// - true - image set
// - false - can't set image
bool ScaleLabel::SetImage(const QString &t_pathToImg)
{
	if ( true == t_pathToImg.isNull() )
	{
		qDebug() << "SetImage(): Error - path to image is empty -" << t_pathToImg;
		return false;
	}

	bool imgLoaded = m_originalImg.load(t_pathToImg);
	if ( false == imgLoaded )
	{
		qDebug() << "SetImage(): Error - can't load image" << t_pathToImg;
		return false;
	}

	SetImgOnLabel();

	return true;
}

// Get scaled image from previously loaded original image and set it as pixmap to label
// @input:
// @output:
void ScaleLabel::SetImgOnLabel()
{
	if ( true == m_originalImg.isNull() )
	{
		return;
	}

	QImage imgToSet = m_originalImg.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
	this->setPixmap(QPixmap::fromImage(imgToSet));
}

// On resize rescale image
// @input:
// @output:
void ScaleLabel::resizeEvent(QResizeEvent *)
{
	if ( true == this->pixmap()->isNull() )
	{
		return;
	}

	SetImgOnLabel();
}
