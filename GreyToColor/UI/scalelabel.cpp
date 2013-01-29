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

void ScaleLabel::SetImage(const QImage &t_image)
{
	if ( true == t_image.isNull() )
	{
		return;
	}

	m_originalImg = t_image;

	SetImgOnLabel();
}

void ScaleLabel::SetImgOnLabel()
{
	if ( true == m_originalImg.isNull() )
	{
		return;
	}

	QImage imgToSet = m_originalImg.scaled(this->width(), this->height(), Qt::KeepAspectRatio);
	this->setPixmap(QPixmap::fromImage(imgToSet));
}

void ScaleLabel::resizeEvent(QResizeEvent *)
{
	if ( true == this->pixmap()->isNull() )
	{
		return;
	}

	SetImgOnLabel();
}
