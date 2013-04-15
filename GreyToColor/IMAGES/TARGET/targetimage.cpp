/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2013, Antony Cherepanov <antony.cherepanov@gmail.com>
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

#include "targetimage.h"

TargetImage::TargetImage()
{
	if ( NULL != m_imgPixels )
	{
		delete m_imgPixels;
	}

	m_imgPixels = new TargetImgPixels();
}

TargetImage::~TargetImage()
{
	m_img.Clear();
	m_similarAreas.clear();

	if ( NULL != m_imgPixels )
	{
		TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
		delete pixels;
		m_imgPixels = NULL;
	}
}

// Clear all info
// @input:
// @output:
void TargetImage::Clear()
{
	m_img.Clear();
	m_similarAreas.clear();

	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	if ( NULL != pixels )
	{
		pixels->TargetImgPixels::Clear();
	}
}

// Construct custom pixels of loaded image
// @input:
// @output:
void TargetImage::ConstructImgPixels()
{
	QImage currentImg = m_img.GetImg();
	if ( true == currentImg.isNull() )
	{
		qDebug() << "ConstructImgPixels(): Error - can't construct pixels of null image";
		return;
	}

	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	if ( NULL == pixels )
	{
		pixels = new TargetImgPixels();
	}

	pixels->Clear();
	pixels->FormImgPixels(currentImg);

	TransformImgRGB2LAB();
}

// Scale relative luminance of all pixels in image with certain scale factor
// @input:
// - double - positive unnull scale factor for pixel LAB luminance
// @output:
// - true - relative luminance of all pixels scaled
// - false - can't scale relative luminance
bool TargetImage::ScaleLABRelLum(const double &t_scaleFactor)
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	return pixels->ScaleRelLum(t_scaleFactor);
}

// Restore relative luminance of all pixels in image
// @input:
// @output:
void TargetImage::RestoreLABRelLum()
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	pixels->RestoreRelLum();
}

// Normalise relative luminance of all pixels in image by min/max borders
// @input:
// - double - positive value of new min LAB relative luminance
// - double - positive value of new max LAB relative luminance
// @output:
// - true - relative luminance of all pixels normalised
// - false - can't normalise relative luminance
bool TargetImage::NormaliseLABRelLumByBorders(const double &t_newMinLABRelLum, const double &t_newMaxLABRelLum)
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	return pixels->NormaliseRelLumByBorders(t_newMinLABRelLum, t_newMaxLABRelLum);
}

// Normalise relative luminance of all pixels in image by center
// @input:
// - double - positive value of new min LAB relative luminance
// - double - positive value of new center (common) LAB relative luminance
// - double - positive value of new max LAB relative luminance
// @output:
// - true - relative luminance of all pixels normalised
// - false - can't normalise relative luminance
bool TargetImage::NormaliseLABRelLumByCenter(const double &t_newMinLABRelLum,
											 const double &t_newCenterLABRelLum,
											 const double &t_newMaxLABRelLum)
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	return pixels->NormaliseRelLumByCenter(t_newMinLABRelLum,
										   t_newCenterLABRelLum,
										   t_newMaxLABRelLum);
}

// Set prefered color for certain pixel
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// - RGB - valid color from RGB color space
// @output:
void TargetImage::SetPixPrefColor(const unsigned int &t_width,
								  const unsigned int &t_height,
								  const RGB &t_prefColor)
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	pixels->SetPixPreferedColor(t_width,
								t_height,
								t_prefColor);
}

// Set flag that pixel colored
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void TargetImage::SetPixColoured(const unsigned int &t_width, const unsigned int &t_height)
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	pixels->SetPixColoured(t_width, t_height);
}

// Set flag that pixel uncolored
// @input:
// @output:
void TargetImage::SetPixelsUncoloured()
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	pixels->SetPixelsUncoloured();
}

// Check if pixel is colored
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
bool TargetImage::IsPixColoured(const unsigned int &t_width, const unsigned int &t_height) const
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	return pixels->IsPixColoured(t_width, t_height);
}

// Get result image. It could be colorized (if we had performed colorization) or
// greyscale as original target (if we had not performed colorization yet).
// @input:
// @output:
// - null Image - can't return colorized image
// - Image - colorized image
Image TargetImage::GetResultImage()
{
	if ( (true == m_img.IsNull()) || ( false == m_imgPixels->HasPixels() ) )
	{
		qDebug() << "GetResultImage(): Error - nothing to save";
		Image empty;
		return empty;
	}

	// Transform LAB pixels to new RGB pixels (maybe we have changed LAB pixel so we need to update RGB pixel)
	TransformImgLAB2GRB();

	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	QImage formedImg = pixels->FormImage();
	if ( true == formedImg.isNull() )
	{
		qDebug() << "GetResultImage(): Error - can't form image";
		Image empty;
		return empty;
	}

	Image colorizedImage;
	colorizedImage.SetImage(formedImg);

	return colorizedImage;
}
