/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2014, Antony Cherepanov <antony.cherepanov@gmail.com>
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

#include <QDebug>
#include "imagepixels.h"
#include "./DEFINES/pixels.h"
#include "./DEFINES/global.h"

ImagePixels::ImagePixels()
{
	Clear();
}

ImagePixels::~ImagePixels()
{
	Clear();
}

// Clear all info (set to defaults)
// @input:
// @output:
void ImagePixels::Clear()
{
	const int numOfPixels = m_pixels.size();
	for ( int i = numOfPixels - 1; i >= 0; --i )
	{
		Pixel *pix = m_pixels[i];
		if ( nullptr != pix )
		{
			delete pix;
		}
	}

	m_pixels.clear();
	m_width = 0;
	m_height = 0;
}

// Transform all image pixels from RGB color space to LAB
// @input:
// @output:
void ImagePixels::TransAllPixRGB2LAB()
{
	for ( unsigned int width = 0; width < m_width; ++width )
	{
		for ( unsigned int height = 0; height < m_height; ++height )
		{
			TransformPixRGB2LAB(width, height);
		}
	}
}

// Transform certain pixel from RGB color space to LAB
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
void ImagePixels::TransformPixRGB2LAB(const unsigned int &t_width,
									  const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "TransformPixRGB2LAB(): Error - invalid arguments. " <<
					"Width =" << t_width << ", height =" << t_height;
		return;
	}

	const int index = GetPixelIndex(t_width, t_height);
	m_pixels[index]->TransformRGB2LAB();
}

// Transform all image pixels from LAB color space to RGB
// @input:
// @output:
void ImagePixels::TransAllPixLAB2RGB()
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
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
void ImagePixels::TransformPixLAB2RGB(const unsigned int &t_width,
									  const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "TransformPixLAB2RGB(): Error - invalid arguments";
		return;
	}

	const int index = GetPixelIndex(t_width, t_height);
	m_pixels[index]->TransformLAB2RGB();
}

// Calculate real index of pixel
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - unsigned int - real pixel position in pixels array
unsigned int ImagePixels::GetPixelIndex(const unsigned int &t_width,
										const unsigned int &t_height) const
{
	return t_height * m_width + t_width;
}

// Check if we have pixel with such coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - true - pixels with such coords exist
// - false - pixel don't exist
bool ImagePixels::IsPixelExist(const unsigned int &t_width,
							   const unsigned int &t_height) const
{
	if ( (m_width <= t_width) || (m_height <= t_height) )
	{
		return false;
	}

	return true;
}

// Check if we have pixels of image
// @input:
// @output:
// - true - yes, we have pixels
// - false - no, we don't have pixels
bool ImagePixels::HasPixels() const
{
	if ( (0 == m_width) ||
		 (0 == m_height) ||
		 (true == m_pixels.empty()) )
	{
		return false;
	}

	return true;
}

// Get Luminance of pixel with certain coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel.
// - double > 0 - luminance of pixel
double ImagePixels::GetPixChLum(const unsigned int &t_width,
								const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChLum(): Error - invalid arguments";
		return NO_INFO;
	}

	const int index = GetPixelIndex(t_width, t_height);
	return m_pixels[index]->GetChL();
}

// Get value of channel A of pixel with certain coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel A of pixel
double ImagePixels::GetPixChA(const unsigned int &t_width,
							  const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChA(): Error - invalid arguments";
		return NO_INFO;
	}

	const int index = GetPixelIndex(t_width, t_height);
	return m_pixels[index]->GetChA();
}

// Get value of channel B of pixel with certain coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel B of pixel
double ImagePixels::GetPixChB(const unsigned int &t_width,
							  const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChB(): Error - invalid arguments";
		return NO_INFO;
	}

	const int index = GetPixelIndex(t_width, t_height);
	return m_pixels[index]->GetChB();
}

// Set value for channels A and B of pixel with certain coords
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// - double - value for pixels channel A
// - double - value for pixels channel B
// @output:
void ImagePixels::SetPixChannelsAB(const unsigned int &t_width,
								   const unsigned int &t_height,
								   const double &t_chA,
								   const double &t_chB)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "SetPixChannelsAB(): Error - invalid arguments";
		return;
	}

	const int index = GetPixelIndex(t_width, t_height);
	m_pixels[index]->SetChA(t_chA);
	m_pixels[index]->SetChB(t_chB);
}

// Check if pixel with certain coords is greyscale
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
// - true - pixel is grey
// - false - pixel is colourful
bool ImagePixels::IsPixGrey(const unsigned int &t_width,
							const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "IsPixGrey(): Error - invalid arguments";
		return false;
	}

	const int index = GetPixelIndex(t_width, t_height);
	return m_pixels[index]->IsGrey();
}
