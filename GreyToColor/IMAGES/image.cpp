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
// - t_path - unnull string with path to existing image
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
}

// Get path to loaded image
// @input:
// @output:
// - string - unempty path to existing image
// - empty string - object doesn't have image
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

//bool Image::SetPath(const QString &t_path)
//{

//}

//bool Image::Save(const QString &t_apth = 0)
//{

//}

// TODO:
// add states of object: NULL, HAS_STRING, HAS_IMAGE, FULL

// Check if image is null (unloaded)
// @input:
// @output:
// - true - image is null
// - false - image has something loaded
bool Image::IsNull()
{
	return m_image.isNull();
}
