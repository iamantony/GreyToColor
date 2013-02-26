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

#include "image.h"

Image::Image(QObject *parent) :
	QObject(parent)
{
	Clear();
}

Image::~Image()
{
	Clear();
}

// Clear all info
// @input:
// @output:
void Image::Clear()
{
	m_pathToImg.clear();
	m_image = QImage();
}

// Loading image from path
// @input:
// - QString - unnull string with path to existing image
// @output:
// - true - image loaded
// - false - can't load image
bool Image::LoadImg(const QString &t_path)
{
	if ( true == t_path.isEmpty() )
	{
		qDebug() << "LoadImg(): Error - invalid arguments";
		return false;
	}

	m_pathToImg.clear();
	m_image = QImage();

	bool imgLoaded = m_image.load(t_path);
	if ( false == imgLoaded )
	{
		qDebug() << "LoadImg(): Error - can't load image";
		return false;
	}

	m_pathToImg.clear();
	m_pathToImg.append(t_path);

	return true;
}

// Reload image
// @input:
// @output:
bool Image::ReloadImg()
{
	if ( true == m_pathToImg.isEmpty() )
	{
		qDebug() << "ReloadImg(): Error - path is empty";
		return false;
	}

	bool imgLoaded = m_image.load(m_pathToImg);
	if ( false == imgLoaded )
	{
		qDebug() << "ReloadImg(): Error - can't load image";
		return false;
	}
}

// Set new path of image
// @input:
// - QString - unempty string with path of image
// @output:
// - true - path is OK
// - false - problems with new path
bool Image::SetImgPath(const QString &t_path)
{
	if ( true == t_path.isEmpty() )
	{
		qDebug() << "SetPath(): Error - invalid arguments";
		return false;
	}

	m_pathToImg.clear();
	m_pathToImg.append(t_path);

	return true;
}

// Get path to loaded image
// @input:
// @output:
// - QString - unempty path to existing image
// - empty QString - object doesn't have image
QString Image::GetImgPath() const
{
	return m_pathToImg;
}

// Get copy of image
// @input:
// @output:
// - QImage - current image. Possibly empty.
QImage Image::GetImg() const
{
	return m_image;
}

// TODO:
// - we can choose format of image in which we want save it
// ? add states of object: NULL, HAS_STRING, HAS_IMAGE, FULL

// Save image in original path m_pathToImg
// @input:
// @output:
// - true - image saved
// - false - can't save image
bool Image::SaveImg()
{
	return SaveImg(m_pathToImg);
}

// Save image
// @input:
// - QString - unempty string with path where we should save image
// @output:
// - true - image saved
// - false - can't save image in path
bool Image::SaveImg(const QString &t_path)
{
	if ( true == t_path.isEmpty() )
	{
		qDebug() << "SaveImg(): Error - can't save image to empty path";
		return false;
	}

	// TODO:
	// - implement this function (with possibility to save image in different formats) in class ImgFileService

	return m_image.save(t_path, 0, 100);
}

// Check if image is null (unloaded)
// @input:
// @output:
// - true - image is null
// - false - image has something loaded
bool Image::IsNull() const
{
	return m_image.isNull();
}
