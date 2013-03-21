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
	for ( int width = 0; width < m_pixels.size(); width++ )
	{
		int pixInColumn = m_pixels[width].size();
		for ( int height = 0; height < pixInColumn; height++ )
		{
			TargetPixel *pix = (TargetPixel *)m_pixels[width][height];
			if ( NULL != pix )
			{
				delete pix;
			}
		}

		m_pixels[width].clear();
	}

	m_pixels.clear();
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
				qDebug() << "Luminance restored!";
				RestoreLum();
				return false;
			}
		}
	}

	return true;
}

// Normalise pixels luminances by min/max borders
// @input:
// - double - positive value of new min LAB luminance
// - double - positive value of new max LAB luminance
// @output:
// - true - luminance of all pixels normalised
// - false - can't normalise luminance
bool TargetImgPixels::NormaliseLumByBorders(const double &t_newMinLum, const double &t_newMaxLum)
{
	if ( (t_newMinLum < 0) ||
		 (t_newMaxLum < 0) ||
		 (t_newMaxLum < t_newMinLum ))
	{
		qDebug() << "NormaliseLum(): Error - invalid arguments";
		return false;
	}

	const double currMinLum = FindMinLum();
	const double currMaxLum = FindMaxLum();
	if ( (currMinLum < 0) || (currMaxLum < 0) )
	{
		qDebug() << "NormaliseLum(): Error - invalid current min/max luminances";
		return false;
	}

	const double diffLum = currMaxLum - currMinLum;

	double scaleFactor = ( t_newMaxLum - t_newMinLum ) / diffLum;
	if ( scaleFactor <= 0 )
	{
		scaleFactor = 1;
	}

	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			double luminance = pixel->GetChL();

			luminance = (luminance - currMinLum) * scaleFactor + t_newMinLum;

			bool pixNormalised = pixel->SetNormalizedLum(luminance);
			if ( false == pixNormalised )
			{
				qDebug() << "NormaliseLum(): Error - can't normalize luminance for pixel" << width << height;
				qDebug() << "Luminance restored!";
				RestoreLum();
				return false;
			}
		}
	}

	return true;
}

// Normalise pixels luminance by center
// @input:
// - double - positive value of new min LAB luminance
// - double - positive value of new center (common) LAB luminance
// - double - positive value of new max LAB luminance
// @output:
// - true - luminance of all pixels normalised
// - false - can't normalise luminance
bool TargetImgPixels::NormaliseLumByCenter(const double &t_newMinLum,
										   const double &t_newCenterLum,
										   const double &t_newMaxLum)
{
	if ( (t_newMinLum < 0) ||
		 (t_newCenterLum < 0) ||
		 (t_newMaxLum < 0) )
	{
		qDebug() << "NormaliseLumByCenter(): Error - invalid arguments";
		return false;
	}

	const double currMinLum = FindMinLum();
	const double currCommonLum = FindMostCommonLum();
	const double currMaxLum = FindMaxLum();
	if ( (currMinLum < 0) ||
		 (currCommonLum < 0) ||
		 (currMaxLum < 0) )
	{
		qDebug() << "NormaliseLumByCenter(): Error - invalid current min/common/max luminances";
		return false;
	}

	// Params for lower area (current luminance between min and common)
	const double currDiffLumLA = currCommonLum - currMinLum;
	const double newDiffLumLA = t_newCenterLum - t_newMinLum;
	const double scaleFactorLA = newDiffLumLA / currDiffLumLA;

	// Params for upper area (current luminance between common and max)
	const double currDiffLumUA = currMaxLum - currCommonLum;
	const double newDiffLumUA = t_newMaxLum - t_newCenterLum;
	const double scaleFactorUA = newDiffLumUA / currDiffLumUA;

	if ( (scaleFactorLA <= 0) || (scaleFactorUA <= 0) )
	{
		qDebug() << "NormaliseLumByCenter(): Error - invalid scale factors";
		return false;
	}

	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			double luminance = pixel->GetChL();

			if ( luminance <= currCommonLum )
			{
				luminance = (luminance - currMinLum) * scaleFactorLA + t_newMinLum;
			}
			else
			{
				luminance = (luminance - currCommonLum) * scaleFactorUA + t_newCenterLum;
			}

			bool pixNormalised = pixel->SetNormalizedLum(luminance);
			if ( false == pixNormalised )
			{
				qDebug() << "NormaliseLumByCenter(): Error - can't normalize luminance for pixel" << width << height;
				qDebug() << "Luminance restored!";
				RestoreLum();
				return false;
			}
		}
	}

	return true;
}

// Restore original luminance of all pixels in image
// @input:
// @output:
void TargetImgPixels::RestoreLum()
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			pixel->RestoreLum();
		}
	}
}

// Set prefered color for certain pixel
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// - RGB - valid color from RGB color space
// @output:
void TargetImgPixels::SetPixPreferedColor(const unsigned int &t_width,
										  const unsigned int &t_height,
										  const RGB &t_prefColor)
{
	if ( false == IsPixelExist(t_width, t_height) )
	{
		qDebug() << "SetPixPreferedColor(): Error - invalid arguments";
		return;
	}

	TargetPixel *pixel = (TargetPixel *)m_pixels[t_width][t_height];
	pixel->SetPreferedColor(t_prefColor);
}

// Set flag that pixel coloured
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
void TargetImgPixels::SetPixColoured(const unsigned int &t_width, const unsigned int &t_height)
{
	TargetPixel *pixel = (TargetPixel *)m_pixels[t_width][t_height];
	pixel->SetColored();
}

// Set flag that pixel uncoloured
// @input:
// @output:
void TargetImgPixels::SetPixelsUncoloured()
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			pixel->SetUncolored();
		}
	}
}

// Check if pixel is coloured
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
bool TargetImgPixels::IsPixColoured(const unsigned int &t_width, const unsigned int &t_height) const
{
	TargetPixel *pixel = (TargetPixel *)m_pixels[t_width][t_height];
	return pixel->IsColored();
}

// Form from current pixels values entire QImage
// @input:
// @output:
// - empty QImage - can't form image
// - QImage - image from pixels
QImage TargetImgPixels::FormImage()
{
	if ( false == HasPixels() )
	{
		qDebug() << "FormImage(): Error - can't form image without pixels";
		QImage empty;
		return empty;
	}

	QImage outputImg(m_width, m_height, QImage::Format_RGB32);
	RGB pixelRGB;
	for ( unsigned int wdt = 0; wdt < m_width; wdt++ )
	{
		for ( unsigned int hgt = 0; hgt < m_height; hgt++ )
		{
			pixelRGB = m_pixels[wdt][hgt]->GetRGB();
			QRgb pixel = qRgb(pixelRGB.GetRed(),
							  pixelRGB.GetGreen(),
							  pixelRGB.GetBlue());

			outputImg.setPixel(wdt, hgt, pixel);
		}
	}

	return outputImg;
}

// Test functions
void TargetImgPixels::TestFunctionality()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												   "Open target image...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

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

	RestoreLum();
	qDebug() << "After unscaling:" << pixel->GetChL();
}

// Test Calc SKO
void TargetImgPixels::TestSKO()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												   "Open target image...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

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

	QElapsedTimer timer;
	timer.start();

	// Calc SKO for some pixel (in the middle of the image)
	CalcPixSKO(5, 5);

	qint64 elapsed = timer.nsecsElapsed();
	qDebug() << "Elapsed:" << elapsed;
}
