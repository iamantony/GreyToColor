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
	m_pathToImg.clear();
}

Image::~Image()
{
	m_pathToImg.clear();
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

// Set new path of image
// @input:
// - QString - unempty string with path of image
// @output:
// - true - path is OK
// - false - problems with new path
bool Image::SetPath(const QString &t_path)
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
QString Image::GetImgPath()
{
	if ( true == m_image.isNull() )
	{
		m_pathToImg.clear();
		return m_pathToImg;
	}

	QImage testImg;
	bool canLoad = testImg.load(m_pathToImg);
	if ( false == canLoad )
	{
		m_image = QImage();
	}

	return m_pathToImg;
}

// Get copy of image
// @input:
// @output:
// - QImage - current image. Possibly empty.
QImage Image::GetImg()
{
	return m_image;
}

// TODO:
// we can choose format of image in which we want save it
// add states of object: NULL, HAS_STRING, HAS_IMAGE, FULL ?

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

	return m_image.save(t_path);
}

// Check if image is null (unloaded)
// @input:
// @output:
// - true - image is null
// - false - image has something loaded
bool Image::IsNull()
{
	return m_image.isNull();
}
