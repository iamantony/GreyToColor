#include "fileoperations.h"

FileOperations::FileOperations(QObject *parent) :
	QObject(parent)
{
}

void FileOperations::MoveImagesToProject(QStringList &t_images)
{
	for (int img = t_images.size() - 1; img >= 0; img--)
	{
		QString imgNewPath = MoveImgToProjectPath(t_images.at(img));
		if ( NULL == imgNewPath )
		{
			// By some reason we didn't create copy of image and so we better delete this image from list
			if ( (0 == img) && (1 == t_images.size()) )
			{
				t_images.clear();
			}
			else
			{
				t_images.removeAt(img);
			}
		}
		else
		{
			// Image successfully copied
			t_images.replace(img, imgNewPath);
		}
	}
}

QString FileOperations::MoveImgToProjectPath(QString t_imgPath)
{
	// Images have to be stored in directory PROJECT_IMG_PATH
	QDir directory;
	QString pathToImgDir = directory.currentPath();
	pathToImgDir.append(PROJECT_IMG_PATH);
	pathToImgDir = directory.toNativeSeparators(pathToImgDir);
	directory.mkpath(pathToImgDir);

	// We should check if user choosed image from PROJECT_IMG_PATH
	if ( true == t_imgPath.startsWith(pathToImgDir) )
	{
		qDebug() << "File" << t_imgPath << "is already in project. Try to update database, if you think" <<
					"that it's not in database.";
		return NULL;
	}
	else
	{
		// If it is locte in some another directory, than we should copy this image to a project path PROJECT_IMG_PATH
		QFileInfo saveInfo(t_imgPath);
		QString saveFile;

		saveFile = pathToImgDir + saveInfo.baseName() + "." + saveInfo.completeSuffix();
		bool fileRemoved = RemoveFileIfExist(saveFile);
		if ( false == fileRemoved )
		{
			qDebug() << "MoveImgToProjectPath(): error - cant remove file:" << saveFile;
			return NULL;
		}

		bool fileCopiedSuccessfully = QFile::copy(t_imgPath, saveFile);
		if ( false == fileCopiedSuccessfully )
		{
			qDebug() << "MoveImgToProjectPath(): error - cant copy file:" << saveFile;
			return NULL;
		}

		// Returning path to a copy of the image in PROJECT_IMG_PATH
		return saveFile;
	}
}

QString FileOperations::CutImagePathToImageName(QString t_image)
{
	QFileInfo imgInfo(t_image);
	QString imgName;
	imgName = imgInfo.baseName() + "." + imgInfo.completeSuffix();

	return imgName;
}

bool FileOperations::RemoveFileIfExist(QString t_file)
{
	bool fileAlreadyExist = QFile::exists(t_file);
	if ( true == fileAlreadyExist )
	{
		bool fileRemoved = QFile::remove(t_file);
		if ( false == fileRemoved )
		{
			qDebug() << "RemoveFile(): error - cant remove file:" << t_file;
			return false;
		}
	}

	return true;
}

QString FileOperations::FormFullName(QString &t_name)
{
	QString fullName;
	QDir dir;
	fullName.append(dir.absolutePath());
	fullName.append(t_name);
	fullName = dir.toNativeSeparators(fullName);

	return fullName;
}

bool FileOperations::CheckFileExistance(QString t_file)
{
	return QFile::exists(t_file);
}
