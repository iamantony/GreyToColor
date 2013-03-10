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

	m_passports.clear();
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
//	pixels->TransAllPixRGB2LAB();
//	CalcPixelsSKO();
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

// Get image passport of certain type
// @input:
// - Passport::Type - exist type of target image passport
// @output:
// - empty ImgPassport - can't find passport of such type
// - ImgPassport - target image passport
ImgPassport TargetImage::GetPassport(const Passport::Type &t_type) const
{
	if ( true == m_passports.isEmpty() )
	{
		qDebug() << "GetPassport(): Target Image hasn't passports";
		ImgPassport empty;
		return empty;
	}

	ImgPassport foundPassport;
	int numOfPassports = m_passports.size();
	for ( int pass = 0; pass < numOfPassports; pass++ )
	{
		Passport::Type passType = m_passports.at(pass).GetPassportType();
		if ( t_type == passType )
		{
			foundPassport = m_passports.at(pass);
			break;
		}
	}

	return foundPassport;
}

// Get all passports of image
// @input:
// @output:
// - empty QList<ImgPassport> - target image hasn't passports
// - QList<ImgPassport> - target image passports
QList<ImgPassport> TargetImage::GetAllPassports() const
{
	if ( true == m_passports.isEmpty() )
	{
		qDebug() << "GetPassport(): Target image hasn't passports";
		QList<ImgPassport> empty;
		return empty;
	}

	return m_passports;
}

// Form image passport of certain type for Target Image
// @input:
// - Passport::Type - exist type of image passport
// @output:
// - true - passport formed
// - false - passport forming failed
bool TargetImage::FormPassport(const Passport::Type &t_type)
{
	if ( Passport::DEFAULT_LAST == t_type )
	{
		qDebug() << "FormPassport(): Error - invalid arguments";
		return false;
	}

	ImgTransform transformer;
	Image greyImg = transformer.ToGrey(m_img);
	if ( true == greyImg.IsNull() )
	{
		qDebug() << "FormPassport(): Error - can't get greyscaled image";
		return false;
	}

	// Form passport
	ImgPassportCreator passCreator;
	QList<double> passport = passCreator.GetImgPassport(greyImg, t_type);
	if ( true == passport.isEmpty() )
	{
		qDebug() << "FormPassport(): Error - can't form passport" << t_type << "for Target image";
		return false;
	}

	ImgPassport newPassport;
	bool passportSet = newPassport.SetPassport(t_type, passport);
	if ( false == passportSet )
	{
		qDebug() << "FormPassport(): Error - can't set new passport" << t_type << "for Target image";
		return false;
	}

	// Add new passport to list
	AddPasport(newPassport);

	return true;
}

// Add new passport to list of pasports of current image
// @input:
// - ImgPassport - unnull image passport
// @output:
void TargetImage::AddPasport(const ImgPassport &t_passport)
{
	if ( true == t_passport.IsEmpty() )
	{
		qDebug() << "AddPasport(): Error - invalid arguments";
		return;
	}

	Passport::Type newPassType = t_passport.GetPassportType();

	// Check if passport of the same type already exist in list. If yes - delete all such passports
	int numOfPassports = m_passports.size();
	for ( int pass = 0; pass < numOfPassports; pass++ )
	{
		Passport::Type passType = m_passports.at(pass).GetPassportType();
		if ( newPassType == passType )
		{
			m_passports.removeAt(pass);
		}
	}

	// Add new passport to list
	m_passports.append(t_passport);
}

// Form all exist image passports
// @input:
// @output:
// - true - all (or some of them) passports formed
// - false - no passports formed
bool TargetImage::FormAllPassports()
{
	m_passports.clear();
	bool hasSomePassports = false;

	for ( int type = Passport::LUM_HISTOGRAM; type < Passport::DEFAULT_LAST; type++ )
	{
		Passport::Type passType = static_cast<Passport::Type>(type);
		bool passportFormed = FormPassport(passType);
		if ( true == passportFormed )
		{
			hasSomePassports = true;
		}
		else
		{
			qDebug() << "FormAllPassports(): Error - can't form passport" << type << "for Target image";
		}
	}

	return hasSomePassports;
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
	UnScaleLABLum();
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
