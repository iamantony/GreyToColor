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
	pixels->FormImgPixels(currentImg);
	pixels->TransAllPixRGB2LAB();
	CalcPixelsSKO();
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

// Unscale luminance of all pixels in image
// @input:
// @output:
void TargetImage::UnScaleLABLum()
{
	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	pixels->UnScaleLum();
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

// Get result image. It could be colorized (if we perform colorization) or
// greyscale as original target (if we have not performed colorizztion yet).
// @input:
// @output:
// - null Image - can't return colorized image
// - Image - colorized image
Image TargetImage::GetColorizedImage()
{
	if ( (true == m_img.IsNull()) || ( true == m_imgPixels->HasPixels() ) )
	{
		qDebug() << "GetColorizedImage(): Error - nothing to save";
		Image empty;
		return empty;
	}

	// Go reverse:
	// - bring back original value of luminance for all image pixels
	UnScaleLABLum();
	// - get from LAB pixels (myabe, their value was changed) new values for RGB pixels
	TransformImgLAB2GRB();

	TargetImgPixels *pixels = (TargetImgPixels *)m_imgPixels;
	QImage formedImg = pixels->FormImage();
	if ( true == formedImg.isNull() )
	{
		qDebug() << "GetColorizedImage(): Error - can't form image";
		Image empty;
		return empty;
	}

	Image colorizedImage;
	colorizedImage.SetImage(formedImg);

	return colorizedImage;
}
