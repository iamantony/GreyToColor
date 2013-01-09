#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QObject>
#include <QDir>
#include <QDebug>
#include "../defines.h"

class FileOperations : public QObject
{
	Q_OBJECT
public:
	explicit FileOperations(QObject *parent = 0);
	void MoveImagesToProject(QStringList &t_images);
	bool RemoveFileIfExist(QString t_file);
	QString CutImagePathToImageName(QString t_image);
	QString FormFullName(QString &t_name);
	bool CheckFileExistance(QString t_file);

private:
	QString MoveImgToProjectPath(QString t_imgPath);

signals:

public slots:

};

#endif // FILEOPERATIONS_H
