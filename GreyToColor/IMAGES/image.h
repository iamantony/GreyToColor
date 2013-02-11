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

#ifndef IMAGE_H
#define IMAGE_H

#include <QObject>
#include <QImage>
#include <QDebug>


class Image : public QObject
{
	Q_OBJECT

	// == DATA ==
private:
	QString m_pathToImg;
	QImage m_image;

	// == METHODS ==
public:
	explicit Image(QObject *parent = 0);
	~Image();

	// Loading image from path
	bool LoadImg(const QString &t_path);
	// Get path to loaded image
	QString GetImgPath();
	// Check if image is null (unloaded)
	bool IsNull();

private:


signals:

public slots:

};

#endif // IMAGE_H
