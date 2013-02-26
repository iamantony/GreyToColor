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

#include "imgfilesservice.h"

ImgFilesService::ImgFilesService()
{

}

// Delete image file
// @input:
// - QString - unempty string with full image file path
// @output:
// - true - image deleted
// - false - can't delete image
bool ImgFilesService::RemoveImg(const QString &t_imgPath)
{
	return RemoveFile(t_imgPath);
}

// Check if image file exist
// @input:
// - QString - unempty string with full image file path
// @output:
// - true - image exist
// - false - can't check image file existance or image don't exist
bool ImgFilesService::CheckImgExist(const QString &t_imgPath)
{
	return CheckFileExistance(t_imgPath);
}

// Get image file name from it's full path
// @input:
// - QString - unempty full image file path
// @output:
// - empty QString - can't get image file name
// - QString - image name with suffix
QString ImgFilesService::GetImgName(const QString &t_imgPath)
{
	return GetFileName(t_imgPath);
}

// Move image to a project path "img"
// @input:
// - QString - unempty full image file path
// @output:
// - empty QString - can't move image
// - same QString - image is already in project folder
// - new unempty QString - copied image path
QString ImgFilesService::MoveImageToProject(const QString &t_imgPath)
{
	if ( true == t_imgPath.isEmpty() )
	{
		qDebug() << "MoveImageToProject(): Error - invalid arguments";
		QString empty;
		return empty;
	}

	if ( false == CheckImgExist(t_imgPath) )
	{
		qDebug() << "MoveImageToProject(): Error - nothing to move";
		QString empty;
		return empty;
	}

	// Images have to be stored in directory PROJECT_IMG_PATH
	QDir directory;
	QString pathToImgDir = directory.currentPath();
	pathToImgDir.append(PROJECT_IMG_PATH);
	pathToImgDir = directory.toNativeSeparators(pathToImgDir);
	directory.mkpath(pathToImgDir);

	QString imgToMove;
	imgToMove = directory.toNativeSeparators(t_imgPath);

	// We should check if user choosed image from PROJECT_IMG_PATH
	if ( true == imgToMove.startsWith(pathToImgDir) )
	{
		qDebug() << "File" << imgToMove << "is already in project";
		return t_imgPath;
	}

	QFileInfo imgCopyInfo(imgToMove);
	QString imgCopyPath;
	for (int i = 0; imgCopyInfo.exists(); i++)
	{
		imgCopyInfo.setFile(imgToMove);
		imgCopyPath = pathToImgDir + imgCopyInfo.baseName();
		if ( 0 == i )
		{
			imgCopyPath += QString(".%1").arg(imgCopyInfo.completeSuffix());
		}
		else
		{
			imgCopyPath += QString("_%1.%2").arg(i).arg(imgCopyInfo.completeSuffix());
		}

		imgCopyInfo.setFile(imgCopyPath);
	}

	bool fileCopiedSuccessfully = QFile::copy(imgToMove, imgCopyPath);
	if ( false == fileCopiedSuccessfully )
	{
		qDebug() << "MoveImgToProjectPath(): error - cant copy file" << imgToMove;
		QString empty;
		return empty;
	}

	return imgCopyPath;
}

// Move images to a project path "img"
// @input:
// - QStringList - unempty full image file paths
// @output:
// - empty QStringList - can't move images
// - unempty QStringList with:
// -- empty QString - can't move that image
// -- same Qstring - image is already in project folder
// -- new QString - new images path
QStringList ImgFilesService::MoveImagesToProject(const QStringList &t_imgsPath)
{
	if ( true == t_imgsPath.isEmpty() )
	{
		qDebug() << "MoveImageToProject(): Error - invalid arguments";
		QStringList empty;
		return empty;
	}

	int numOfImages = t_imgsPath.size();
	QStringList pathsOfCopiedImgs;
	for( int img = 0; img < numOfImages; img++ )
	{
		QString copiedImgPath = MoveImageToProject(t_imgsPath.at(img));
		pathsOfCopiedImgs << copiedImgPath;
	}

	return pathsOfCopiedImgs;
}

// Save image
// @input:
// - QImage - unnull image to save
// - QString - unempty path where we want to save image
// - Image::Format - exist format in which we want to save image
// @output:
// - true - image saved
// - false - can't save image
bool ImgFilesService::SaveImage(const QImage &t_imgToSave,
								const QString &t_path,
								const ImageFormat::FormatType &t_format)
{
	if ( (true == t_imgToSave.isNull()) || (true == t_path.isEmpty()) )
	{
		qDebug() << "SaveImage(): Error - invalid arguments";
		return false;
	}

	// Get rid of image format in it's path
	QString cuttedPath = CutSuffix(t_path);
	if ( true == cuttedPath.isEmpty() )
	{
		qDebug() << "SaveImage(): Error - can't cut suffix from image file path";
		return false;
	}

	QString format = FormatToString(t_format);
	if ( true == format.isEmpty() )
	{
		qDebug() << "SaveImage(): Error - invalid image file format. Can't save image";
		return false;
	}

	cuttedPath.append('.');
	cuttedPath.append(format);

	bool imgSaved = t_imgToSave.save(cuttedPath, 0, 100);
	return imgSaved;
}

// Cut from string (image path) it's suffix (image file format)
// @input:
// - QString - unempty image path
// @output:
// - empty QString - can't cut image path
// - unempty QString - image path without suffix
QString ImgFilesService::CutSuffix(const QString &t_path)
{
	if ( true == t_path.isEmpty() )
	{
		qDebug() << "CutSuffix(): Error - invalid arguments";
		QString empty;
		return empty;
	}

	QString imgPath = t_path;
	int pathSize = imgPath.size();
	int lastSymbol = ERROR;
	for ( int i = pathSize - 1; i >= 0; i-- )
	{
		if ( '.' == imgPath[i] )
		{
			lastSymbol = i;
			break;
		}

		if ( ('/' == imgPath[i]) || ('\\' == imgPath[i]) )
		{
			// In this string there is no info about image file format, so we don't cut anything
			lastSymbol = ERROR;
			break;
		}
	}

	if ( 0 < lastSymbol )
	{
		imgPath.truncate(lastSymbol);
	}

	return imgPath;
}

// Transform image format to its string equivalent
// @input:
// - Image::Format - exist image format that we know
// @output:
// - empty QString - can't transform image format to QString
// - QString - image format as string
QString ImgFilesService::FormatToString(const ImageFormat::FormatType &t_format)
{
	QString format;
	switch(t_format)
	{
		case ImageFormat::BMP:
			format.append("bmp");
			break;

		case ImageFormat::PNG:
			format.append("png");
			break;

		case ImageFormat::TIFF:
			format.append("tiff");
			break;

		case ImageFormat::JPG:
			format.append("jpg");
			break;

		case ImageFormat::JPEG:
			format.append("jpeg");
			break;

		case ImageFormat::DEFAULT_LAST:
		default:
			qDebug() << "FormatToString(): Error - invalid arguments";
	}

	return format;
}

// Test image moving function
void ImgFilesService::TestImgMoving()
{
	QWidget wdt;
	QString imgPath = QFileDialog::getOpenFileName(&wdt,
												   "Open test image...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	QString copiedImgPath = MoveImageToProject(imgPath);
	qDebug() << copiedImgPath;
}

// Test image saving
void ImgFilesService::TestImgSaving()
{
	QWidget wdt;
	QString imgPath = QFileDialog::getOpenFileName(&wdt,
												   "Open test image...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	QString pathToSave = QFileDialog::getSaveFileName(&wdt,
													  "Save as...",
													  QDir::currentPath(),
													  "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	qDebug() << "From:" << imgPath;
	qDebug() << "To:" << pathToSave;

	QImage img(imgPath);

	SaveImage(img, pathToSave, ImageFormat::DEFAULT_LAST);
}
