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

#include "targetimgpixels.h"

TargetImgPixels::TargetImgPixels()
{

}

TargetImgPixels::~TargetImgPixels()
{
	Clear();
}

// Clear info about pixels (call this function before deleting object TargetImgPixels!)
// @input:
// @output:
void TargetImgPixels::Clear()
{
	for ( int width = m_pixels.size() - 1; width >= 0; width-- )
	{
		int pixInColumn = m_pixels[width].size();
		for ( int height = pixInColumn - 1; height >= 0; height-- )
		{
			TargetPixel *pix = (TargetPixel *)m_pixels[width][height];
			if ( NULL != pix )
			{
				delete pix;
			}
		}
	}
}

// Save all pixels from input QImage as custom grey pixels
// @input:
// - QImage - unnull image
// @output:
bool TargetImgPixels::FormImgPixels(const QImage &t_img)
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
		QList<Pixel *> columnOfPixels;

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

			TargetPixel *targetPix = new TargetPixel;
			targetPix->SetAsGrey(rgbPixel);

			columnOfPixels.append(targetPix);
		}

		m_pixels.append(columnOfPixels);
	}

	return true;
}

// Calc for each pixel in image it's SKO
// @input:
// @output:
void TargetImgPixels::CalcPixelsSKO()
{
	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
	{
		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
		{
			CalcPixSKO(wdt, hgt);
		}
	}
}

// Calc for certain pixel in image it's SKO
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void TargetImgPixels::CalcPixSKO(const unsigned int &t_width, const unsigned int &t_height)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "CalcPixSKO(): Error - invalid arguments";
		return;
	}

	QList<double> lumInMask = GetPixNeighborsLum(t_width, t_height);
	if ( true == lumInMask.isEmpty() )
	{
		qDebug() << "CalcPixSKO(): Error - no pixels - no SKO";
		return;
	}

	double pixelLum = m_pixels[t_width][t_height]->GetChL();

	CalculatorSKO calc;
	double pixelSKO = calc.PixelMaskSKO(pixelLum, lumInMask);
	if ( pixelSKO < 0 )
	{
		qDebug() << "CalcPixSKO(): Error - can't calc pixel SKO" << t_width << t_height;
		return;
	}

	TargetPixel *centralPixel = (TargetPixel *)m_pixels[t_width][t_height];
	centralPixel->SetSKO(pixelSKO);
}

// Get SKO of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - ERROR - can't find such pixel
// - double - pixels SKO
double TargetImgPixels::GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsSKO(): Error - invalid arguments";
		return ERROR;
	}

	const TargetPixel *pixel = (TargetPixel *)m_pixels[t_width][t_height];
	return pixel->GetSKO();
}

// Scale luminance of all pixels in image with certain scale factor
// @input:
// - double - positive unnull scale factor for pixel luminance
// @output:
// - true - luminance of all pixels scaled
// - false - can't scale luminance
bool TargetImgPixels::ScaleLum(const double &t_scaleFactor)
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			bool pixelScaled = pixel->ScaleLum(t_scaleFactor);
			if ( false == pixelScaled )
			{
				qDebug() << "ScaleLum(): Error - can't scale luminance for pixel" << width << height;
				qDebug() << "Luminance unscaled!";
				UnScaleLum();
				return false;
			}
		}
	}

	return true;
}

// Unscale luminance of all pixels in image
// @input:
// @output:
void TargetImgPixels::UnScaleLum()
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			pixel->UnScaleLum();
		}
	}
}

// Test functions
void TargetImgPixels::TestFunctionality()
{
	QWidget wdt;
	wdt.show();
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												   "Open target image...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.bmp)");

	if ( true == imgName.isEmpty() )
	{
		return;
	}

	QImage image(imgName);
	bool imgFormed = FormImgPixels(image);
	if ( false == imgFormed )
	{
		qDebug() << "Fail: Can't form image";
		return;
	}

	TransAllPixRGB2LAB();

	TargetPixel *pixel = (TargetPixel *)m_pixels[0][0];
	qDebug() << "Before scaling:" << pixel->GetChL();

	double scaleFactor = 1.5;
	ScaleLum(scaleFactor);
	qDebug() << "After scaling:" << pixel->GetChL();

	UnScaleLum();
	qDebug() << "After unscaling:" << pixel->GetChL();
}
