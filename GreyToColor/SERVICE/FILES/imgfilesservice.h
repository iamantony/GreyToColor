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

#ifndef IMGFILESSERVICE_H
#define IMGFILESSERVICE_H

#include <QFileDialog>
#include "filesservice.h"
#include "./DEFINES/images.h"
#include "./DEFINES/global.h"

class ImgFilesService : protected FilesService
{
	// == DATA ==

	// == METHODS ==
public:
	ImgFilesService();

	// Delete image file
	bool RemoveImg(const QString &t_imgPath);
	// Check if image file exist
	bool CheckImgExist(const QString &t_imgPath);
	// Get image file name from it's full path
	QString GetImgName(const QString &t_imgPath);
	// Move image to a project path "img"
	QString MoveImageToProject(const QString &t_imgPath);
	// Move images to a project path "img"
	QStringList MoveImagesToProject(const QStringList &t_imgsPath);
	// Save image
	bool SaveImage(const QImage &t_imgToSave, const QString &t_path);

	// Test image moving function
	void TestImgMoving();
	// Test image saving
	void TestImgSaving();

private:
	// Cut from string (image path) it's suffix (image file format)
	QString CutSuffix(const QString &t_path);
};

#endif // IMGFILESSERVICE_H
