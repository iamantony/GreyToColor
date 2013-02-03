#include "pixelentity.h"

// TODO:
// 1 - save color in QRgb
// 2 - save greay color in QRgb
// 3 - For transformation RGB -> grey use http://en.wikipedia.org/wiki/Grayscale
// 4 - Don't use QRgb.grey()

PixelEntity::PixelEntity()
{
	m_Red = ERROR;
	m_Green = ERROR;
	m_Blue = ERROR;
	m_L = ERROR;
	m_A = ERROR;
	m_B = ERROR;
	m_SKO = ERROR;
	m_lumScaleFactor = 1;
	m_haveColor = false;
}

void PixelEntity::SetRed(const int &t_Red)
{
	if ( t_Red < 0 )
	{
		m_Red = 0;
	}
	else if ( 255 < t_Red )
	{
		m_Red = 255;
	}
	else
	{
		m_Red = t_Red;
	}
}

int PixelEntity::GetRed()
{
	return m_Red;
}

void PixelEntity::SetGreen(const int &t_Green)
{
	if ( t_Green < 0 )
	{
		m_Green = 0;
	}
	else if ( 255 < t_Green )
	{
		m_Green = 255;
	}
	else
	{
		m_Green = t_Green;
	}
}

int PixelEntity::GetGreen()
{
	return m_Green;
}

void PixelEntity::SetBlue(const int &t_Blue)
{
	if ( t_Blue < 0 )
	{
		m_Blue = 0;
	}
	else if ( 255 < t_Blue )
	{
		m_Blue = 255;
	}
	else
	{
		m_Blue = t_Blue;
	}
}

int PixelEntity::GetBlue()
{
	return m_Blue;
}

void PixelEntity::SetRGB(const int &t_Red, const int &t_Green, const int &t_Blue)
{
	SetRed(t_Red);
	SetGreen(t_Green);
	SetBlue(t_Blue);
}

void PixelEntity::SetL(const double &t_L)
{
	m_L = t_L;
}

double PixelEntity::GetL()
{
	return m_L;
}

void PixelEntity::SetA(const double &t_A)
{
	m_A = t_A;
}

double PixelEntity::GetA()
{
	return m_A;
}

void PixelEntity::SetB(const double &t_B)
{
	m_B = t_B;
}

double PixelEntity::GetB()
{
	return m_B;
}

bool PixelEntity::TransToLAB()
{
	if ( (ERROR == m_Red) || (ERROR == m_Green) || (ERROR == m_Blue) )
	{
		qDebug() << "TransToLAB(): Error - value of RGB pixel undefined.";
		return false;
	}

	RGBLAB colorTransform;
	QList<double> LAB = colorTransform.RGB2LAB(m_Red, m_Green, m_Blue);
	if ( true == LAB.isEmpty() )
	{
		qDebug() << "TransToLAB(): Error - transformation to LAB failed";
		return false;
	}

	m_L = LAB[0];
	m_A = LAB[1];
	m_B = LAB[2];

	return true;
}

bool PixelEntity::TransToRGB()
{
	if ( (ERROR == m_L) || (ERROR == m_A) || (ERROR == m_B) )
	{
		qDebug() << "TransToRGB(): Error - value of LAB pixel undefined.";
		return false;
	}

	RGBLAB colorTransform;
	QList<int> RGB = colorTransform.LAB2RGB(m_L, m_A, m_B);
	if ( true == RGB.isEmpty() )
	{
		qDebug() << "TransToRGB(): Error - transformation to RBG failed";
		return false;
	}

	m_Red = RGB[0];
	m_Green = RGB[1];
	m_Blue = RGB[2];

	return true;
}

void PixelEntity::SetSKO(const double &t_SKO)
{
	m_SKO = t_SKO;
}

double PixelEntity::GetSKO()
{
	return m_SKO;
}

void PixelEntity::ScaleLum(const double &t_scaleFactor)
{
	if ( t_scaleFactor <= 0 )
	{
		qDebug() << "ScaleLum(): Error - scale factor is less or equal zero.";
		return;
	}

	m_lumScaleFactor = t_scaleFactor;
	if ( 1 != m_lumScaleFactor )
	{
		m_L *= m_lumScaleFactor;
	}
}

double PixelEntity::GetLumScaleFactor()
{
	return m_lumScaleFactor;
}

void PixelEntity::ScaleLumBack()
{
	m_L *= (1/m_lumScaleFactor);
}

void PixelEntity::SetPixHasColor()
{
	m_haveColor = true;
}

void PixelEntity::SetPixHasNoColor()
{
	m_haveColor = false;
}

bool PixelEntity::IsPixHasColor()
{
	return m_haveColor;
}
