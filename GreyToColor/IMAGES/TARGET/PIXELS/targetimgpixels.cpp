/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2014, Antony Cherepanov <antony.cherepanov@gmail.com>
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
	Clear();
}

TargetImgPixels::~TargetImgPixels()
{
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
	m_pixels.reserve(m_width * m_height);

	for ( unsigned int wdt = 0; wdt < m_width; ++wdt )
	{
		for ( unsigned int hgt = 0; hgt < m_height; ++hgt )
		{
			QRgb pixel = t_img.pixel(wdt, hgt);

			RGB rgbPixel(qRed(pixel),
						 qGreen(pixel),
						 qBlue(pixel) );

			TargetPixel *targPix = new TargetPixel(&rgbPixel);
			m_pixels.push_back(targPix);
		}
	}

	return true;
}

// Scale relative luminance of all pixels in image with certain scale factor
// @input:
// - t_scaleFactor - positive unnull scale factor for pixel relative luminance
// @output:
// - true - relative luminance of all pixels scaled
// - false - can't scale relative luminance
bool TargetImgPixels::ScaleRelLum(const double &t_scaleFactor)
{
	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		TargetPixel *pixel = (TargetPixel *)m_pixels[pix];
		bool pixelScaled = pixel->ScaleRelLum(t_scaleFactor);
		if ( false == pixelScaled )
		{
			qDebug() << "ScaleRelLum(): Error - can't scale relative" <<
						"luminance for pixel" << pix << ". Luminance restored!";

			RestoreRelLum();
			return false;
		}
	}

	return true;
}

// Restore original relative luminance of all pixels in image
// @input:
// @output:
void TargetImgPixels::RestoreRelLum()
{
	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		TargetPixel *pixel = (TargetPixel *)m_pixels[pix];
		pixel->RestoreRelLum();
	}
}

// Normalise pixels relative luminances by min/max borders
// @input:
// - t_newMinRelLum - positive value of new min relative LAB luminance
// - t_newMaxRelLum - positive value of new max relative LAB luminance
// @output:
// - true - relative luminance of all pixels normalised
// - false - can't normalise relative luminance
bool TargetImgPixels::NormaliseRelLumByBorders(const double &t_newMinRelLum,
											   const double &t_newMaxRelLum)
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
		qDebug() << "NormaliseRelLumByBorders(): Error - invalid current"
					<< "min/max relative luminances";

		return false;
	}

	const double diffLum = currMaxLum - currMinLum;

	double scaleFactor = ( t_newMaxRelLum - t_newMinRelLum ) / diffLum;
	if ( scaleFactor <= 0.0 )
	{
		scaleFactor = 1.0;
	}

	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		TargetPixel *pixel = (TargetPixel *)m_pixels[pix];
		double relLum = ( pixel->GetRelativeLum() - currMinLum ) * scaleFactor +
						t_newMinRelLum;

		bool pixNormalised = pixel->SetNormalizedRelLum(relLum);
		if ( false == pixNormalised )
		{
			qDebug() << "NormaliseRelLumByBorders(): Error - can't normalize" <<
						"relative luminance for pixel" << pix <<
						". Luminance restored!";
				RestoreRelLum();
				return false;
		}
	}

	return true;
}

// Normalise pixels relative luminance by center
// @input:
// - t_newMinRelLum - positive value of new min relative LAB luminance
// - t_newCenterRelLum - positive value of new center (common) relative LAB luminance
// - t_newMaxRelLum - positive value of new max relative LAB luminance
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
		qDebug() << "NormaliseRelLumByCenter(): Error - invalid current" <<
					"min/common/max luminances";

		return false;
	}

	// Params for lower area (current luminance between min and common)
	const double currDiffLumLA = currCommonLum - currMinLum;
	const double newDiffLumLA = t_newCenterRelLum - t_newMinRelLum;
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

	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		TargetPixel *pixel = (TargetPixel *)m_pixels[pix];
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
			qDebug() << "NormaliseRelLumByCenter(): Error - can't normalize" <<
						"luminance for pixel" << pix << ". Luminance restored!";

			RestoreRelLum();
			return false;
		}
	}

	return true;
}

// Set prefered color for certain pixel
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// - t_prefColor - valid color from RGB color space
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

	const unsigned int index = GetPixelIndex(t_width, t_height);
	TargetPixel *pixel = (TargetPixel *)m_pixels[index];
	pixel->SetPreferedColor(t_prefColor);
}

// Set flag that pixel coloured
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
void TargetImgPixels::SetPixColoured(const unsigned int &t_width,
									 const unsigned int &t_height)
{
	const unsigned int index = GetPixelIndex(t_width, t_height);
	TargetPixel *pixel = (TargetPixel *)m_pixels[index];
	pixel->SetColored();
}

// Set flag that pixel uncoloured
// @input:
// @output:
void TargetImgPixels::SetPixelsUncoloured()
{
	const unsigned int maxPixels = m_pixels.size();
	for ( unsigned int pix = 0; pix < maxPixels; ++pix )
	{
		TargetPixel *pixel = (TargetPixel *)m_pixels[pix];
		pixel->SetUncolored();
	}
}

// Check if pixel is coloured
// @input:
// - t_width - exist width (x) position of pixel
// - t_height - exist height (y) position of pixel
// @output:
bool TargetImgPixels::IsPixColoured(const unsigned int &t_width,
									const unsigned int &t_height) const
{
	const unsigned int index = GetPixelIndex(t_width, t_height);
	TargetPixel *pixel = (TargetPixel *)m_pixels[index];
	return pixel->IsColored();
}

// Form from current pixels values entire QImage
// @input:
// @output:
// - QImage - image from pixels
// - empty QImage - can't form image
QImage TargetImgPixels::FormImage()
{
	if ( false == HasPixels() )
	{
		qDebug() << "FormImage(): Error - can't form image without pixels";
		return QImage();
	}

	QImage outputImg(m_width, m_height, QImage::Format_RGB32);
	RGB pixelRGB;
	int pixIndex = 0;
	for ( unsigned int wdt = 0; wdt < m_width; ++wdt )
	{
		for ( unsigned int hgt = 0; hgt < m_height; ++hgt )
		{
			pixelRGB = m_pixels[pixIndex]->GetRGB();
			QRgb pixel = qRgb(pixelRGB.GetRed(),
							  pixelRGB.GetGreen(),
							  pixelRGB.GetBlue());

			outputImg.setPixel(wdt, hgt, pixel);

			++pixIndex;
		}
	}

	return outputImg;
}
