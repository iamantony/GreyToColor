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

#include "candidateimage.h"

CandidateImage::CandidateImage()
{
	Clear();
}

CandidateImage::~CandidateImage()
{
	Clear();
}

// Clear all info
// @input:
// @output:
void CandidateImage::Clear()
{
	m_colorImg.Clear();
	m_greyImg.Clear();
	m_passports.clear();
}

// Load color image
// @input:
// - QString - unempty path to exist image
// @output:
// - true - image loaded, grey image-copy created
// - false - can't load image
bool CandidateImage::LoadColorImg(const QString &t_imgPath)
{
	if ( true == t_imgPath.isEmpty() )
	{
		qDebug() << "LoadColorImg(): Error - invalid arguments";
		return false;
	}

	bool imageLoaded = m_colorImg.LoadImg(t_imgPath);
	if ( false == imageLoaded )
	{
		qDebug() << "LoadColorImg(): Error - can't load image";
		return false;
	}

	bool getGreyCopy = ToGreyImg();
	if ( false == getGreyCopy )
	{
		qDebug() << "LoadColorImg(): Error - can't get greyscale copy of input image";
		Clear();
		return false;
	}

	return true;
}

// Set color image
// @input:
// - QImage - unnull image
// @output:
// - true - image set, grey image-copy created
// - false - can't set image
bool CandidateImage::SetColorImg(const QImage &t_img)
{
	if ( true == t_img.isNull() )
	{
		qDebug() << "SetColorImg(): Error - invalid arguments";
		return false;
	}

	bool imageSet = m_colorImg.SetImage(t_img);
	if ( false == imageSet )
	{
		qDebug() << "SetColorImg(): Error - can't set image";
		return false;
	}

	bool getGreyCopy = ToGreyImg();
	if ( false == getGreyCopy )
	{
		qDebug() << "SetColorImg(): Error - can't get greyscale copy of input image";
		Clear();
		return false;
	}

	return true;
}

// Get from color image it's greyscale copy
// @input:
// @output:
// - true - greyscale image created
// - false - can't get greyscale image
bool CandidateImage::ToGreyImg()
{
	if ( true == m_colorImg.IsNull() )
	{
		qDebug() << "ToGreyImg(): Error - no color image";
		return false;
	}

	ImgTransform imgTransformer;
	Image greyscaleImg = imgTransformer.ToGrey(m_colorImg);
	if ( true == greyscaleImg.IsNull() )
	{
		qDebug() << "ToGreyImg(): Error - no color image";
		return false;
	}

	// NOTE: greyscaleImg should have the same data (besides image) as its parent (m_colorImg)! This rule will
	// provide us copied and saved greyscale image
	m_greyImg = greyscaleImg;
	return true;
}

// Get color image
// @input:
// @output:
// - Image - get current color image (could be NULL!)
Image CandidateImage::GetColorImg() const
{
	return m_colorImg;
}

// Get grey-copy of color image
// @input:
// @output:
// - Image - get current grey image (could be NULL!)
Image CandidateImage::GetGreyImg() const
{
	return m_greyImg;
}

// Get image passport of certain type
// @input:
// - Passport::Type - exist type of image passport
// @output:
// - empty ImgPassport - can't find passport of such type
// - ImgPassport - image passport
ImgPassport CandidateImage::GetPassport(const Passport::Type &t_type) const
{
	if ( true == m_passports.isEmpty() )
	{
		qDebug() << "GetPassport(): image hasn't passports";
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
// - empty QList<ImgPassport> - image hasn't passports
// - QList<ImgPassport> - image passports
QList<ImgPassport> CandidateImage::GetAllPassports() const
{
	if ( true == m_passports.isEmpty() )
	{
		qDebug() << "GetPassport(): image hasn't passports";
		QList<ImgPassport> empty;
		return empty;
	}

	return m_passports;
}

// Form image passport of certain type
// @input:
// - Passport::Type - exist type of image passport
// @output:
// - true - passport formed
// - false - passport forming failed
bool CandidateImage::FormPassport(const Passport::Type &t_type)
{
	if ( Passport::DEFAULT_LAST == t_type )
	{
		qDebug() << "FormPassport(): Error - invalid arguments";
		return false;
	}

	if ( true == m_greyImg.IsNull() )
	{
		if ( true == m_colorImg.IsNull() )
		{
			qDebug() << "FormPassport(): Error - can't form passports for an nonexistent image";
			return false;
		}
		else
		{
			bool greyImgFormed = ToGreyImg();
			if ( false == greyImgFormed )
			{
				qDebug() << "FormPassport(): Error - can't form grey image. Can't create passport.";
				return false;
			}
		}
	}

	// TODO;
	// - form passport
	// - check if it already exist in list. If yes - delete it from list
	// - add new passport to list

	return true;
}

// Form all exist image passports
// @input:
// @output:
// - true - all (or some of them) passports formed
// - false - no passports formed
bool CandidateImage::FormAllPassports()
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
			qDebug() << "FormAllPassports(): Error - can't form passport" << type;
		}
	}

	return hasSomePassports;
}

// Test loading
void CandidateImage::TestImageLoad()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												 "Open target image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	LoadColorImg(imgName);
	m_greyImg.SaveImg("./test_grey.bmp");
}
