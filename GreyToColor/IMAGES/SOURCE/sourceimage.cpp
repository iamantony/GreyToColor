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

#include "sourceimage.h"

SourceImage::SourceImage()
{
	if ( NULL != m_imgPixels )
	{
		delete m_imgPixels;
	}

	m_imgPixels = new SourceImgPixels();
}

SourceImage::~SourceImage()
{
	m_img.Clear();
	m_similarAreas.clear();

	if ( NULL != m_imgPixels )
	{
		SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
		delete pixels;
		m_imgPixels = NULL;
	}
}

// Clear all info
// @input:
// @output:
void SourceImage::Clear()
{
	m_img.Clear();
	m_similarAreas.clear();

	SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	if ( NULL != pixels )
	{
		pixels->Clear();
	}
}

// Transform custom pixels from RGB to LAB
// @input:
// @output:
void SourceImage::TransformImgRGB2LAB()
{
	SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	pixels->TransAllPixRGB2LAB();
}

// Construct custom pixels of loaded image
// @input:
// @output:
void SourceImage::ConstructImgPixels()
{
	QImage currentImg = m_img.GetImg();
	if ( true == currentImg.isNull() )
	{
		qDebug() << "ConstructImgPixels(): Error - can't construct pixels of null image";
		return;
	}

	SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	if ( NULL == pixels )
	{
		pixels = new SourceImgPixels();
	}

	pixels->Clear();
	pixels->FormImgPixels(currentImg);
	TransformImgRGB2LAB();
}

// Get relative luminance of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - double in range [0, 1] - pixels relative luminance
// - double < 0 - can't find such pixel
double SourceImage::GetPixelsRelLum(const unsigned int &t_width, const unsigned int &t_height) const
{
	const SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	return pixels->GetPixelsRelativeLum(t_width, t_height);
}

// Calc for each pixel in image it's SKO
// @input:
// @output:
void SourceImage::CalcPixelsSKO()
{
	SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	pixels->CalcPixelsSKO();
}

// Get SKO of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - ERROR - can't find such pixel
// - double - pixels SKO
double SourceImage::GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const
{
	const SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	return pixels->GetPixelsSKO(t_width, t_height);
}

// Calc for each pixel in image it's Entropy
// @input:
// @output:
void SourceImage::CalcPixelsEntropy()
{
	SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	pixels->CalcPixelsEntropy();
}

// Get Entropy of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - double - pixels Entropy
// - ERROR - can't find such pixel
double SourceImage::GetPixelsEntropy(const unsigned int &t_width, const unsigned int &t_height) const
{
	const SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	return pixels->GetPixelsEntropy(t_width, t_height);
}

// Get maximum value of relative LAB luminance in image
// - double - positive found max relative luminance of images pixels
// - ERROR - can't find max relative luminance
double SourceImage::GetMaxRelLum()
{
	const SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	return pixels->FindMaxRelLum();
}

// Get minimum value of relative LAB luminance in image
// - double - positive found min relative luminance of images pixels
// - ERROR - can't find min relative luminance
double SourceImage::GetMinRelLum()
{
	const SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	return pixels->FindMinRelLum();
}

// Get average value of relative LAB luminance in image
// - double - positive found average relative luminance of images pixels
// - ERROR - can't find average relative luminance
double SourceImage::GetAverageRelLum()
{
	const SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	return pixels->FindAverageRelLum();
}

// Get most common value of relative LAB luminance in image
// - double - positive found most common relative luminance of images pixels
// - ERROR - can't find most common relative luminance
double SourceImage::GetMostCommonRelLum()
{
	const SourceImgPixels *pixels = (SourceImgPixels *)m_imgPixels;
	return pixels->FindMostCommonRelLum();
}

// Test initialising
void SourceImage::TestInit()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												 "Open source image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	LoadImg(imgName);
}

// Test find LAB histogram central pixel
void SourceImage::TestFindCentral()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												 "Open source image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	LoadImg(imgName);
	TransformImgRGB2LAB();
	double commonLum = GetMostCommonRelLum();
	qDebug() << "commonLum = " << commonLum;
}
