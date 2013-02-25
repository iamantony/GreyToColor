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

#include "imagepixels.h"

ImagePixels::ImagePixels()
{
	m_width = 0;
	m_height = 0;
}

ImagePixels::~ImagePixels()
{
	m_width = 0;
	m_height = 0;
}

// Clear all info (set to defaults)
// @input:
// @output:
void ImagePixels::Clear()
{
	for ( int i = m_pixels.size() - 1; i >= 0; i-- )
	{
		int listsize = m_pixels[i].size();
		for ( int j = listsize - 1; j >= 0; j-- )
		{
			Pixel *pix = (Pixel *)m_pixels[i][j];
			if ( NULL != pix )
			{
				delete pix;
			}
		}
	}
}

// Transform all image pixels from RGB color space to LAB
// @input:
// @output:
void ImagePixels::TransAllPixRGB2LAB()
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
void ImagePixels::TransformPixRGB2LAB(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "TransformPixRGB2LAB(): Error - invalid arguments";
		return;
	}

	m_pixels[t_width][t_height]->TransformRGB2LAB();
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
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void ImagePixels::TransformPixLAB2RGB(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "TransformPixLAB2RGB(): Error - invalid arguments";
		return;
	}

	m_pixels[t_width][t_height]->TransformLAB2RGB();
}

// Check if we have pixel with such coords
// @input:
// - unsigned int - width (x) position of pixel
// - unsigned int - height (y) position of pixel
// @output:
// - true - pixels with such coords exist
// - false - pixel don't exist
bool ImagePixels::IsPixelExist(const unsigned int &t_width, const unsigned int &t_height) const
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
	if ( (0 == m_width) || (0 == m_height) )
	{
		return false;
	}

	return true;
}

// Get Luminance of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel.
// - double - luminance of pixel
double ImagePixels::GetPixChLum(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChLum(): Error - invalid arguments";
		return NO_INFO;
	}

	return m_pixels[t_width][t_height]->GetChL();
}

// Get value of channel A of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel A of pixel
double ImagePixels::GetPixChA(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChA(): Error - invalid arguments";
		return NO_INFO;
	}

	return m_pixels[t_width][t_height]->GetChA();
}

// Get value of channel B of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel B of pixel
double ImagePixels::GetPixChB(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixChB(): Error - invalid arguments";
		return NO_INFO;
	}

	return m_pixels[t_width][t_height]->GetChB();
}

// Set value for channels A and B of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
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

	m_pixels[t_width][t_height]->SetChA(t_chA);
	m_pixels[t_width][t_height]->SetChB(t_chB);
}

// Find among all pixels in image value of max luminance
// @input:
// @output:
// - ERROR - can't find max luminance
// - double - positive found max luminance of images pixels
double ImagePixels::FindMaxLum() const
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
			double pixelLum = m_pixels[width][height]->GetChL();
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
double ImagePixels::FindMinLum() const
{
	if ( false == HasPixels() )
	{
		qDebug() << "FindMinLum(): Error - no pixels";
		return ERROR;
	}

	double minLum = DEFAULT_MIN_LUM;
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			double pixelLum = m_pixels[width][height]->GetChL();
			if ( pixelLum < minLum )
			{
				minLum = pixelLum;
			}
		}
	}

	return minLum;
}

// Get list of luminances of neighbor pixels (to calc SKO, for example)
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - empty QList<double> - don't have pixels
// - unempy QList<double> - luminances of neighbor pixels
QList<double> ImagePixels::GetPixNeighborsLum(const unsigned int &t_width, const unsigned int &t_height) const
{
	QList<double> luminances;

	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixNeighborsLum(): Error - invalid arguments";
		return luminances;
	}

	// This is length of side of a rect, which is form a mask. Central pixel in mask is pixel with input coords.
	// Other pixels are neighbors of central pixel.
	int maskRectSide = MASK_RECT_SIDE_LENGTH;
	if ( maskRectSide < 0 )
	{
		maskRectSide *= (-1);
	}

	// In current version we use mask with an odd length of a rect side. But it's OK if mask side length is even.
	// Calc offset to get to extreme pixels in mask
	int offset = maskRectSide / 2;
	int minWidthCoord = (int)t_width - offset;
	int minHeightCoord = (int)t_height - offset;

	// Calc position of extreme pixels
	unsigned int widthStart = (unsigned int)qMax( 0, minWidthCoord );
	unsigned int widthEnd = qMin( m_width, t_width + (unsigned int)offset + 1 );
	unsigned int heightStart = (unsigned int)qMax( 0, minHeightCoord );
	unsigned int heightEnd = qMin( m_height, t_height + (unsigned int)offset + 1 );

//	qDebug() << "Pixel" << t_width << t_height;
//	qDebug() << "widthStart =" << widthStart << "widthEnd =" << widthEnd;
//	qDebug() << "heightStart =" << heightStart << "heightEnd =" << heightEnd;

	for ( unsigned int width = widthStart; width < widthEnd; width++ )
	{
		for ( unsigned int height = heightStart; height < heightEnd; height++ )
		{
			if ( (width == t_width) && (height == t_height) )
			{
				// We take luminance of neighbor pixels, so we don't interested in value of luminance of current
				// (central) pixel
				continue;
			}

			double pixelLum = m_pixels[width][height]->GetChL();
			luminances.append(pixelLum);
		}
	}

	return luminances;
}

// Check if pixel with certain coords is greyscale
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - true - pixel is grey
// - false - pixel is colourful
bool ImagePixels::IsPixGrey(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "IsPixGrey(): Error - invalid arguments";
		return false;
	}

	return m_pixels[t_width][t_height]->IsGrey();
}
