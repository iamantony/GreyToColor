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

}

SourceImgPixels::~SourceImgPixels()
{

}

//void SourceImgPixels::Init()
//{
//	for ( int i = 0; i < 5; ++i )
//	{
//		QList <Pixel*> list;
//		for ( int j = 0; j < 5; ++j )
//		{
//			ColorPixel *pix = new ColorPixel();
//			RGB color;
//			color.SetColor(50, 50, 50);
//			pix->SetRGB(color);
//			pix->SetSKO(120);
//			list.append( (Pixel *)(pix) );
//		}
//		m_pixels.append(list);
//	}
//}

//void SourceImgPixels::Show()
//{
//	ColorPixel *pix = (ColorPixel *)m_pixels[0][0];
//	RGB rgb = pix->GetRGB();
//	qDebug() << "SourceImgPixels: red is" << rgb.GetRed();
//	qDebug() << "SourceImgPixels: SKO is" << pix->GetSKO();
//}

// Clear info about pixels (call this function before deleting object SourceImgPixels!)
// @input:
// @output:
void SourceImgPixels::Clear()
{
	for ( int width = m_pixels.size() - 1; width >= 0; width-- )
	{
		int pixInColumn = m_pixels[width].size();
		for ( int height = pixInColumn - 1; height >= 0; height-- )
		{
			ColorPixel *pix = (ColorPixel *)m_pixels[width][height];
			if ( NULL != pix )
			{
				delete pix;
			}
		}
	}
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

			ColorPixel *colorPix = new ColorPixel;
			colorPix->SetRGB(rgbPixel);

			columnOfPixels.append(colorPix);
		}

		m_pixels.append(columnOfPixels);
	}

	return true;
}

// Calc for each pixel in image it's SKO
// @input:
// @output:
void SourceImgPixels::CalcPixelsSKO()
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
void SourceImgPixels::CalcPixSKO(const unsigned int &t_width, const unsigned int &t_height)
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

	ColorPixel *centralPixel = (ColorPixel *)m_pixels[t_width][t_height];
	centralPixel->SetSKO(pixelSKO);
}

// Get SKO of pixel with certain coords
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - ERROR - can't find such pixel
// - double - pixels SKO
double SourceImgPixels::GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "GetPixelsSKO(): Error - invalid arguments";
		return ERROR;
	}

	const ColorPixel *pixel = (ColorPixel *)m_pixels[t_width][t_height];
	return pixel->GetSKO();
}





// TODO:
// - create test function that test mask construction

//
