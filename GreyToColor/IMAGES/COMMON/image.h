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
#include "./DEFINES/global.h"
#include "./SERVICE/FILES/imgfilesservice.h"

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

	// Clear all info
	void Clear();
	// Loading image from path
	bool LoadImg(const QString &t_path);
	// Reload image
	bool ReloadImg();
	// Set new path of image
	bool SetImgPath(const QString &t_path);
	// Get new QImage
	bool SetImage(const QImage &t_img);
	// Get path to loaded image
	QString GetImgPath() const;
	// Get copy of image
	QImage GetImg() const;
	// Save image in original path m_pathToImg
	bool SaveImg();
	// Save image in path t_path
	bool SaveImg(const QString &t_path);
	// Check if image is null (unloaded)
	bool IsNull() const;
};

#endif // IMAGE_H
