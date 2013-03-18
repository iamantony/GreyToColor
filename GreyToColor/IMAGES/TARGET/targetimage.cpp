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
	m_imgPixels = new TargetImgPixels();
}

TargetImage::~TargetImage()
{
	Clear();

	if ( NULL != m_imgPixels )
	{
		delete m_imgPixels;
	}
}

// Clear all info
// @input:
// @output:
void TargetImage::Clear()
{
	m_img.Clear();
	m_imgPixels->Clear();
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
	pixels->Clear();
	pixels->FormImgPixels(currentImg);
}

// Calc for each pixel in image it's SKO
// @input:
// @output:
void TargetImage::CalcPixelsSKO()
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	pixels->CalcPixelsSKO();
}

// Get SKO of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - ERROR - can't find such pixel
// - double - pixels SKO
double TargetImage::GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const
{
	const TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	return pixels->GetPixelsSKO(t_width, t_height);
}

// Scale luminance of all pixels in image with certain scale factor
// @input:
// - double - positive unnull scale factor for pixel LAB luminance
// @output:
// - true - luminance of all pixels scaled
// - false - can't scale luminance
bool TargetImage::ScaleLABLum(const double &t_scaleFactor)
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	return pixels->ScaleLum(t_scaleFactor);
}

// Normalise luminance of all pixels in image
// @input:
// - double - positive value of new min LAB luminance
// - double - positive value of new max LAB luminance
// @output:
// - true - luminance of all pixels normalised
// - false - can't normalise luminance
bool TargetImage::NormaliseLABLum(const double &t_newMinLABLum, const double &t_newMaxLABLum)
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	return pixels->NormaliseLum(t_newMinLABLum, t_newMaxLABLum);
}

// Restore luminance of all pixels in image
// @input:
// @output:
void TargetImage::RestoreLABLum()
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	pixels->RestoreLum();
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

// Get result image. It could be colorized (if we perform colorization) or
// greyscale as original target (if we have not performed colorizztion yet).
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

	// Go reverse:
	// - bring back original value of luminance for all image pixels
	RestoreLABLum();
	// - get from LAB pixels (myabe, their value was changed) new values for RGB pixels
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

// Get current version of target image
// @input:
// @output:
// - null Image - can't get Target image
// - Image - current Target image
Image TargetImage::GetCurrentImage()
{
	if ( false == HasImage() )
	{
		qDebug() << "GetCurrentImage(): Error - no Target image";
		Image empty;
		return empty;
	}

	return m_img;
}
