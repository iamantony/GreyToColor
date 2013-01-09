#include "imgentity.h"

ImgEntity::ImgEntity()
{
	m_imgWidth = ERROR;
	m_imgHeight = ERROR;
	m_pixelsArray = NULL;
}

ImgEntity::~ImgEntity()
{
	for ( int pix = 0; pix < m_imgWidth; pix++ )
	{
		delete [] m_pixelsArray[pix];
	}

	delete [] m_pixelsArray;
}

bool ImgEntity::SetImg(QImage t_img)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "SetImg(): Error - invalid arguments";
		return false;
	}

	m_img = t_img;
	m_imgWidth = m_img.width();
	m_imgHeight = m_img.height();

	CreatePixelArray();

	return true;
}

QImage ImgEntity::GetImg()
{
	return m_img;
}

int ImgEntity::GetImgWidth()
{
	return m_imgWidth;
}

int ImgEntity::GetImgHeight()
{
	return m_imgHeight;
}

void ImgEntity::CreatePixelArray()
{
	m_pixelsArray = new PixelEntity* [m_imgWidth];
	for ( int pix = 0; pix < m_imgWidth; pix++ )
	{
		m_pixelsArray[pix] = new PixelEntity [m_imgHeight];
	}

	QColor pixel;
	for ( int x = 0; x < m_imgWidth; x++ )
	{
		for ( int y = 0; y < m_imgHeight; y ++ )
		{
			pixel = m_img.pixel(x, y);
			m_pixelsArray[x][y].SetRGB(pixel.red(), pixel.green(), pixel.blue());
		}
	}
}

PixelEntity* ImgEntity::PixelAt(const int &t_x, const int &t_y)
{
	if ( (NULL == m_pixelsArray) ||
		 (t_x < 0) ||
		 (m_imgWidth <= t_x) ||
		 (t_y < 0) ||
		 (m_imgHeight <= t_y) )
	{
		qDebug() << "PixelAt(): Error - invalid pixel coordinate";
		PixelEntity *null = new PixelEntity;
		return null;
	}

	return &m_pixelsArray[t_x][t_y];
}

void ImgEntity::TransformImgRGB2LAB()
{
	PixelEntity *pixel;
	bool transferSuccess = false;

	for ( int x = 0; x < m_imgWidth; x++ )
	{
		for ( int y = 0; y < m_imgHeight; y ++ )
		{
			pixel = &(m_pixelsArray[x][y]);
			transferSuccess = pixel->TransToLAB();
			if ( false == transferSuccess )
			{
				qDebug() << "Can't transform image fron RGB to LAB color space.";
				return;
			}
		}
	}
}

void ImgEntity::TransformImgLAB2RGB()
{
	bool transferSuccess = false;

	for ( int x = 0; x < m_imgWidth; x++ )
	{
		for ( int y = 0; y < m_imgHeight; y ++ )
		{
			transferSuccess = m_pixelsArray[x][y].TransToRGB();
			if ( false == transferSuccess )
			{
				qDebug() << "Can't transform image fron LAB to RGB color space.";
				return;
			}
		}
	}

	QRgb pixel;
	int R, G, B;

	for ( int x = 0; x < m_imgWidth; x++ )
	{
		for ( int y = 0; y < m_imgHeight; y ++ )
		{
			R = m_pixelsArray[x][y].GetRed();
			G = m_pixelsArray[x][y].GetGreen();
			B = m_pixelsArray[x][y].GetBlue();

			pixel = qRgb(R, G, B);
			m_img.setPixel(x, y, pixel);
		}
	}
}

double ImgEntity::PixelLum(const int &t_x, const int &t_y)
{
	PixelEntity *pixel = PixelAt(t_x, t_y);
	return pixel->GetL();
}

double ImgEntity::PixelChA(const int &t_x, const int &t_y)
{
	PixelEntity *pixel = PixelAt(t_x, t_y);
	return pixel->GetA();
}

double ImgEntity::PixelChB(const int &t_x, const int &t_y)
{
	PixelEntity *pixel = PixelAt(t_x, t_y);
	return pixel->GetB();
}

void ImgEntity::SetPixelChA(const int &t_x, const int &t_y, const double &t_chA)
{
	PixelEntity *pixel = PixelAt(t_x, t_y);
	pixel->SetA(t_chA);
}

void ImgEntity::SetPixelChB(const int &t_x, const int &t_y, const double &t_chB)
{
	PixelEntity *pixel = PixelAt(t_x, t_y);
	pixel->SetB(t_chB);
}

double ImgEntity::MaxLum()
{
	double maxLum = 0;
	double curLum = 0;
	for ( int x = 0; x < m_imgWidth; x++ )
	{
		for ( int y = 0; y < m_imgHeight; y ++ )
		{
			curLum = PixelLum(x, y);
			if ( curLum > maxLum )
			{
				maxLum = curLum;
			}
		}
	}

	return maxLum;
}

void ImgEntity::ScaleLum(const double &t_scaleFactor)
{
	for ( int x = 0; x < m_imgWidth; x++ )
	{
		for ( int y = 0; y < m_imgHeight; y ++ )
		{
			PixelEntity *pixel = PixelAt(x, y);
			if ( ERROR == pixel->GetRed() )
			{
				qDebug() << "SetLum(): Error - can't scale luminance.";
				return;
			}

			pixel->ScaleLum(t_scaleFactor);
		}
	}
}

void ImgEntity::ScaleLumBack()
{
	for ( int x = 0; x < m_imgWidth; x++ )
	{
		for ( int y = 0; y < m_imgHeight; y ++ )
		{
			PixelEntity *pixel = PixelAt(x, y);
			if ( ERROR == pixel->GetRed() )
			{
				qDebug() << "ScaleLumBack(): Error - can't scale luminance.";
				return;
			}

			pixel->ScaleLumBack();
		}
	}
}

void ImgEntity::CalcSKO()
{
	for (int x = 0; x < m_imgWidth; x++)
	{
		for (int y = 0; y < m_imgHeight; y++)
		{
			double average = 0;
			double count = 0;
			for (int k = x - 2; k < (x + 3); k++)
			{
				for (int m = y - 2; m < (y + 3); m++)
				{
					if( (k >= 0) &&
						(m >= 0) &&
						(k < m_imgWidth) &&
						(m < m_imgHeight) )
					{
						PixelEntity *pixel = PixelAt(k, m);
						if ( ERROR == pixel->GetRed() )
						{
							qDebug() << "CalcSKO(): Error - can't get pixel.";
							return;
						}

						average += pixel->GetL();
						count++;
					}
				}
			}

			average = average/count;

			double sko = 0;
			for (int k = x - 2; k < (x + 3); k++)
			{
				for (int m = y - 2; m < (y + 3); m++)
				{
					if( (k >= 0) &&
						(m >= 0) &&
						(k < m_imgWidth) &&
						(m < m_imgHeight) )
					{
						PixelEntity *pixel = PixelAt(k, m);
						if ( ERROR == pixel->GetRed() )
						{
							qDebug() << "CalcSKO(): Error - can't get pixel.";
							return;
						}

						sko+= pow((pixel->GetL() - average), 2);
					}
				}
			}

			sko = pow(sko, 0.5);

			PixelEntity *pixel = PixelAt(x, y);
			if ( ERROR == pixel->GetRed() )
			{
				qDebug() << "CalcSKO(): Error - can't get pixel.";
				return;
			}

			pixel->SetSKO(sko);
		}
	}
}

double ImgEntity::PixelSKO(const int &t_x, const int &t_y)
{
	PixelEntity *pixel = PixelAt(t_x, t_y);
	return pixel->GetSKO();
}

bool ImgEntity::PixelHasColor(const int &t_x, const int &t_y)
{
		PixelEntity *pixel = PixelAt(t_x, t_y);
		return pixel->IsPixHasColor();
}

void ImgEntity::SetPixelHasColor(const int &t_x, const int &t_y)
{
		PixelEntity *pixel = PixelAt(t_x, t_y);
		pixel->SetPixHasColor();
}
