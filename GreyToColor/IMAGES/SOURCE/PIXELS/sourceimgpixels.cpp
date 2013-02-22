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

#include "sourceimgpixels.h"

SourceImgPixels::SourceImgPixels()
{
	ClearPixels();
}

SourceImgPixels::~SourceImgPixels()
{
	ClearPixels();
}

// Clear all info
// @input:
// @output:
void SourceImgPixels::ClearPixels()
{
	m_pixels.clear();
	this->Clear();
}

// Save all pixels from input QImage as custom pixels
// @input:
// - QImage - unnull image
// @output:
bool SourceImgPixels::FormImgPixels(const QImage &t_img)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "FormImgPixels(): Error - invalid arguments";
		return false;
	}

	m_width = t_img.width();
	m_height = t_img.height();

	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
	{
		QList<ColorPixel> columnOfPixels;

		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
		{
			QRgb pixel = t_img.pixel(wdt, hgt);

			RGB rgbPixel;
			bool colorOK = rgbPixel.SetColor(qRed(pixel), qGreen(pixel), qBlue(pixel));
			if ( false == colorOK )
			{
				qDebug() << "FormImgPixels(): pixel with coords (" << wdt << "," << hgt <<
							") has problems with RGB channels: invalid value";
			}

			ColorPixel colorPix;
			colorPix.SetRGB(rgbPixel);

			columnOfPixels.append(colorPix);
		}

		m_pixels.append(columnOfPixels);
	}

	TransAllPixRGB2LAB();

	return true;
}

// Transform all image pixels from RGB color space to LAB
// @input:
// @output:
void SourceImgPixels::TransAllPixRGB2LAB()
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TransformPixRGB2LAB(width, height);
		}
	}
}

// Transform certain pixel from RGB color space to LAB
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void SourceImgPixels::TransformPixRGB2LAB(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "TransformPixRGB2LAB(): Error - invalid arguments";
		return;
	}

	m_pixels[t_width][t_height].TransformRGB2LAB();
}

// Transform all image pixels from LAB color space to RGB
// @input:
// @output:
void SourceImgPixels::TransAllPixLAB2RGB()
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TransformPixLAB2RGB(width, height);
		}
	}
}

// Transform certain pixel from LAB color space to RGB
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void SourceImgPixels::TransformPixLAB2RGB(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "TransformPixLAB2RGB(): Error - invalid arguments";
		return;
	}

	m_pixels[t_width][t_height].TransformLAB2RGB();
}

// Get Luminance of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel.
// - double - luminance of pixel
double SourceImgPixels::GetPixChLum(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChLum(): Error - invalid arguments";
		return NO_INFO;
	}

	return m_pixels[t_width][t_height].GetChL();
}

// Get value of channel A of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel A of pixel
double SourceImgPixels::GetPixChA(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChA(): Error - invalid arguments";
		return NO_INFO;
	}

	return m_pixels[t_width][t_height].GetChA();
}

// Get value of channel B of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel B of pixel
double SourceImgPixels::GetPixChB(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChB(): Error - invalid arguments";
		return NO_INFO;
	}

	return m_pixels[t_width][t_height].GetChB();
}

// Set value for channels A and B of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// - double - value for pixels channel A
// - double - value for pixels channel B
// @output:
void SourceImgPixels::SetPixChannelsAB(const unsigned int &t_width,
					  const unsigned int &t_height,
					  const double &t_chA,
					  const double &t_chB)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "SetPixChannelsAB(): Error - invalid arguments";
		return;
	}

	m_pixels[t_width][t_height].SetChA(t_chA);
	m_pixels[t_width][t_height].SetChB(t_chB);
}

// Find among all pixels in image value of max luminance
// @input:
// @output:
// - ERROR - can't find max luminance
// - double - positive found max luminance of images pixels
double SourceImgPixels::FindMaxLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMaxLum(): Error - no pixels";
		return ERROR;
	}

	double maxLum = DEFAULT_MAX_LUM;
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			double pixelLum = m_pixels[width][height].GetChL();
			if ( maxLum < pixelLum )
			{
				maxLum = pixelLum;
			}
		}
	}

	return maxLum;
}

// Find among all pixels in image value of min luminance
// @input:
// @output:
// - ERROR - can't find min luminance
// - double - positive found min luminance of images pixels
double SourceImgPixels::FindMinLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMinLum(): Error - no pixels";
		return ERROR;
	}

	double minLum = DEFAULT_MAX_LUM;
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			double pixelLum = m_pixels[width][height].GetChL();
			if ( pixelLum < minLum )
			{
				minLum = pixelLum;
			}
		}
	}

	return minLum;
}

// Calc for certain pixel in image it's SKO
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void SourceImgPixels::CalcPixSKO(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixSKO(): Error - invalid arguments";
		return;
	}

//	m_pixels[t_width][t_height].
}
