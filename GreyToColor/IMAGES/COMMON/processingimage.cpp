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

#include "processingimage.h"

ProcessingImage::ProcessingImage()
{

}

// Clear class info
// @input:
// @output:
void ProcessingImage::Clear()
{
	m_img.Clear();
	if ( NULL != m_imgPixels )
	{
		delete m_imgPixels;
		m_imgPixels = NULL;
	}
}

// Set image
// @input:
// - QImage - unempty image
// @output:
// - true - image set
// - false - can't set this image
bool ProcessingImage::SetImg(const QImage &t_image)
{
	bool imgSet = m_img.SetImage(t_image);
	if ( true == imgSet )
	{
		ConstructImgPixels();
	}

	return imgSet;
}

// Set image path
// @input:
// - QString - unempty path to image
// @output:
// - true - path saved
// - false - invalid path
bool ProcessingImage::SetImgPath(const QString &t_imgPath)
{
	return m_img.SetImgPath(t_imgPath);
}

// Load image from path
// @input:
// - QString - unempty path to image
// @output:
// - true - image loaded
// - false - can't load image from input path
bool ProcessingImage::LoadImg(const QString &t_imagePath)
{
	bool imgLoaded = m_img.LoadImg(t_imagePath);
	if ( true == imgLoaded )
	{
		ConstructImgPixels();
	}

	return imgLoaded;
}

// Construct custom pixels of loaded image
// @input:
// @output:
void ProcessingImage::ConstructImgPixels()
{
	// It's a base class. We don't use it so we don't need construct some pixel-custom-objects
}

// Get width of image
// @input:
// @output:
// - unsigned int - positive width of image (could be 0 if we don't have image)
unsigned int ProcessingImage::GetImageWidth() const
{
	return m_img.GetImgWidth();
}

// Get height of image
// @input:
// @output:
// - unsigned int - positive height of image (could be 0 if we don't have image)
unsigned int ProcessingImage::GetImageHeight() const
{
	return m_img.GetImgHeight();
}

// Transform custom pixels from RGB to LAB
// @input:
// @output:
void ProcessingImage::TransformImgRGB2LAB()
{
	m_imgPixels->TransAllPixRGB2LAB();
}

// Transform custom pixels from LAB to RGB
// @input:
// @output:
void ProcessingImage::TransformImgLAB2GRB()
{
	m_imgPixels->TransAllPixLAB2RGB();
}

// Get pixel luminance (LAB)
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel.
// - double - luminance of pixel
double ProcessingImage::PixelChLum(const unsigned int &t_width, const unsigned int &t_height) const
{
	return m_imgPixels->GetPixChLum(t_width, t_height);
}

// Get value of channel A of pixel
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel A of pixel
double ProcessingImage::PixelChA(const unsigned int &t_width, const unsigned int &t_height) const
{
	return m_imgPixels->GetPixChA(t_width, t_height);
}

// Get value of channel B of pixel
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel B of pixel
double ProcessingImage::PixelChB(const unsigned int &t_width, const unsigned int &t_height) const
{
	return m_imgPixels->GetPixChB(t_width, t_height);
}

// Set value for channels A and B of pixel
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// - double - value for pixels channel A
// - double - value for pixels channel B
// @output:
void ProcessingImage::SetPixelChAB(const unsigned int &t_width,
								   const unsigned int &t_height,
								   const double &t_chA,
								   const double &t_chB)
{
	m_imgPixels->SetPixChannelsAB(t_width,
								  t_height,
								  t_chA,
								  t_chB);
}

// Find among all pixels in image value of max luminance
// @input:
// @output:
// - ERROR - can't find max luminance
// - double - positive found max luminance of images pixels
double ProcessingImage::GetMaxLABLum() const
{
	return m_imgPixels->FindMaxLum();
}

// Check if pixel with certain coords is greyscale
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - true - pixel is grey
// - false - pixel is colourful
bool ProcessingImage::IsPixelGrey(const unsigned int &t_width, const unsigned int &t_height) const
{
	return m_imgPixels->IsPixGrey(t_width, t_height);
}

// TODO:
// - test adding area

// Add image similiarity area
// @input:
// - ImgSimilarityArea - valid image similarity area
// @output:
// - true - area added
// - false - can't add such area
bool ProcessingImage::AddSimilarityArea(const ImgSimilarityArea &t_area)
{
	if ( true == m_img.IsNull() )
	{
		qDebug() << "AddSimilarityArea(): Error - no image - no area";
		return false;
	}

	if ( false == ValidateSimArea(t_area) )
	{
		qDebug() << "AddSimilarityArea(): Error - invalid area";
		return false;
	}

	// Check if we already have area with the same ID
	const unsigned int newAreaID = t_area.GetAreaID();
	const int numOfAreas = m_similarAreas.size();
	for ( int area = 0; area < numOfAreas; area++ )
	{
		unsigned int existAreaID = m_similarAreas.at(area).GetAreaID();
		if ( newAreaID == existAreaID )
		{
			// If we found such area - remove it
			m_similarAreas.removeAt(area);
		}
	}

	m_similarAreas.append(t_area);
	return true;
}

// Validate similarity area
// @input:
// - ImgSimilarityArea - valid image area
// @output:
// - true - area is valid
// - false - area is invalid
bool ProcessingImage::ValidateSimArea(const ImgSimilarityArea &t_area) const
{
	if ( false == t_area.IsValid() )
	{
		qDebug() << "ValidateSimArea(): Error - invalid arguments";
		return false;
	}

	const unsigned int imgWidth = m_img.GetImgWidth();
	const unsigned int imgHeight = m_img.GetImgHeight();

	QRect imgRect = t_area.GetAreaRect();
	const int startWidth = imgRect.x();
	const int startHeight = imgRect.y();

	if ( (startWidth < 0) ||
		 (imgWidth <= (unsigned int)startWidth) ||
		 (startHeight < 0) ||
		 (imgHeight <= (unsigned int)startHeight))
	{
		qDebug() << "ValidateSimArea(): Error - area start coords are invalid";
		return false;
	}

	const unsigned int endWidth = (unsigned int)startWidth + (unsigned int)imgRect.width();
	const unsigned int endHeight = (unsigned int)startHeight + (unsigned int)imgRect.height();
	if ( (imgWidth <= endWidth) || (imgHeight <= endHeight) )
	{
		qDebug() << "ValidateSimArea(): Error - area end coords are invalid";
		return false;
	}

	return true;
}

// Find image similarity area by ID
// @input:
// - unsigned int - area ID
// @output:
// - zero (invalid) ImgSimilarityArea - didn't find area with such id
// - ImgSimilarityArea - exist image similarity area
ImgSimilarityArea ProcessingImage::FindSimilarityArea(const unsigned int &t_id) const
{
	ImgSimilarityArea imgSimArea;
	const int numOfAreas = m_similarAreas.size();
	for ( int area = 0; area < numOfAreas; area++ )
	{
		unsigned int existAreaID = m_similarAreas.at(area).GetAreaID();
		if ( t_id == existAreaID )
		{
			imgSimArea = m_similarAreas.at(area);
		}
	}

	return imgSimArea;
}
