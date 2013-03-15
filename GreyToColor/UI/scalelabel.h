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

#ifndef SCALELABEL_H
#define SCALELABEL_H

#include <QLabel>
#include <QImage>
#include <QDebug>

class ScaleLabel : public QLabel
{
	Q_OBJECT

	// == DATA ==
private:
	QString m_defaultImgPath;
	QImage m_originalImg;

	// == METHODS ==
public:
	explicit ScaleLabel(QWidget *parent = 0);
	~ScaleLabel();

	// Set path to default image
	bool SetDefaultImgPath(const QString &t_pathToDefault);
	// Put to label default image
	void ShowDefaultImg();
	// Set image to label
	bool SetImage(const QImage &t_image);
	bool SetImage(const QString &t_pathToImg);

protected:
	void resizeEvent(QResizeEvent *);

private:
	void SetImgOnLabel();

};

#endif // SCALELABEL_H
