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
#include "./SERVICE/IMAGES/imghistogram.h"

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

// Scale relative luminance of all pixels in image with certain scale factor
// @input:
// - double - positive unnull scale factor for pixel relative luminance
// @output:
// - true - relative luminance of all pixels scaled
// - false - can't scale relative luminance
bool TargetImgPixels::ScaleRelLum(const double &t_scaleFactor)
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			bool pixelScaled = pixel->ScaleRelLum(t_scaleFactor);
			if ( false == pixelScaled )
			{
				qDebug() << "ScaleRelLum(): Error - can't scale relative luminance for pixel" << width << height;
				qDebug() << "Luminance restored!";
				RestoreRelLum();
				return false;
			}
		}
	}

	return true;
}

// Restore original relative luminance of all pixels in image
// @input:
// @output:
void TargetImgPixels::RestoreRelLum()
{
	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			pixel->RestoreRelLum();
		}
	}
}

// Normalise pixels relative luminances by min/max borders
// @input:
// - double - positive value of new min relative LAB luminance
// - double - positive value of new max relative LAB luminance
// @output:
// - true - relative luminance of all pixels normalised
// - false - can't normalise relative luminance
bool TargetImgPixels::NormaliseRelLumByBorders(const double &t_newMinRelLum, const double &t_newMaxRelLum)
{
	if ( (t_newMinRelLum < RELATIVE_MIN) ||
		 (t_newMaxRelLum < RELATIVE_MIN) ||
		 (RELATIVE_MAX < t_newMinRelLum) ||
		 (RELATIVE_MAX < t_newMaxRelLum) ||
		 (t_newMaxRelLum < t_newMinRelLum ))
	{
		qDebug() << "NormaliseRelLumByBorders(): Error - invalid arguments";
		return false;
	}

	const double currMinLum = FindMinRelLum();
	const double currMaxLum = FindMaxRelLum();
	if ( (currMinLum < RELATIVE_MIN) || (currMaxLum < RELATIVE_MIN) )
	{
		qDebug() << "NormaliseRelLumByBorders(): Error - invalid current min/max relative luminances";
		return false;
	}

	const double diffLum = currMaxLum - currMinLum;

	double scaleFactor = ( t_newMaxRelLum - t_newMinRelLum ) / diffLum;
	if ( scaleFactor <= 0.0 )
	{
		scaleFactor = 1.0;
	}

	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			double relLum = pixel->GetRelativeLum();

			relLum = (relLum - currMinLum) * scaleFactor + t_newMinRelLum;

			bool pixNormalised = pixel->SetNormalizedRelLum(relLum);
			if ( false == pixNormalised )
			{
				qDebug() << "NormaliseRelLumByBorders(): Error - can't normalize relative luminance for pixel" <<
							width << height;

				qDebug() << "Luminance restored!";
				RestoreRelLum();
				return false;
			}
		}
	}

	return true;
}

// Normalise pixels relative luminance by center
// @input:
// - double - positive value of new min relative LAB luminance
// - double - positive value of new center (common) relative LAB luminance
// - double - positive value of new max relative LAB luminance
// @output:
// - true - relative luminance of all pixels normalised
// - false - can't normalise relative luminance
bool TargetImgPixels::NormaliseRelLumByCenter(const double &t_newMinRelLum,
											  const double &t_newCenterRelLum,
											  const double &t_newMaxRelLum)
{
	if ( (t_newMinRelLum < RELATIVE_MIN) ||
		 (t_newCenterRelLum < RELATIVE_MIN) ||
		 (t_newMaxRelLum < RELATIVE_MIN) ||
		 (RELATIVE_MAX < t_newMinRelLum) ||
		 (RELATIVE_MAX < t_newCenterRelLum) ||
		 (RELATIVE_MAX < t_newMaxRelLum) ||
		 (t_newMaxRelLum < t_newMinRelLum ))
	{
		qDebug() << "NormaliseRelLumByCenter(): Error - invalid arguments";
		return false;
	}

	const double currMinLum = FindMinRelLum();
	const double currCommonLum = FindMostCommonRelLum();
	const double currMaxLum = FindMaxRelLum();
	if ( (currMinLum < RELATIVE_MIN) ||
		 (currCommonLum < RELATIVE_MIN) ||
		 (currMaxLum < RELATIVE_MIN) )
	{
		qDebug() << "NormaliseRelLumByCenter(): Error - invalid current min/common/max luminances";
		return false;
	}

	// Params for lower area (current luminance between min and common)
	const double currDiffLumLA = currCommonLum - currMinLum;
	const double newDiffLumLA = t_newCenterRelLum - t_newMinLum;
	const double scaleFactorLA = newDiffLumLA / currDiffLumLA;

	// Params for upper area (current luminance between common and max)
	const double currDiffLumUA = currMaxLum - currCommonLum;
	const double newDiffLumUA = t_newMaxRelLum - t_newCenterRelLum;
	const double scaleFactorUA = newDiffLumUA / currDiffLumUA;

	if ( (scaleFactorLA <= 0.0) || (scaleFactorUA <= 0.0) )
	{
		qDebug() << "NormaliseRelLumByCenter(): Error - invalid scale factors";
		return false;
	}

	for ( unsigned int width = 0; width < m_width; width++ )
	{
		for ( unsigned int height = 0; height < m_height; height++ )
		{
			TargetPixel *pixel = (TargetPixel *)m_pixels[width][height];
			double relLum = pixel->GetRelativeLum();

			if ( relLum <= currCommonLum )
			{
				relLum = (relLum - currMinLum) * scaleFactorLA + t_newMinRelLum;
			}
			else
			{
				relLum = (relLum - currCommonLum) * scaleFactorUA + t_newCenterRelLum;
			}

			bool pixNormalised = pixel->SetNormalizedRelLum(relLum);
			if ( false == pixNormalised )
			{
				qDebug() << "NormaliseRelLumByCenter(): Error - can't normalize luminance for pixel" <<
							width << height;

				qDebug() << "Luminance restored!";
				RestoreRelLum();
				return false;
			}
		}
	}

	return true;
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
