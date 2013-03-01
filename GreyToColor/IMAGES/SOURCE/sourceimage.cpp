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

#include "sourceimage.h"

SourceImage::SourceImage()
{
	m_imgPixels = new SourceImgPixels();
}

SourceImage::~SourceImage()
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
void SourceImage::Clear()
{
	m_img.Clear();
	m_imgPixels->Clear();
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
	pixels->FormImgPixels(currentImg);
	pixels->TransAllPixRGB2LAB();
	CalcPixelsSKO();
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

// Test initialising
void SourceImage::TestInit()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												 "Open target image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	LoadImg(imgName);
}
