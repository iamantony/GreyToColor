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

	// WARNING: greyscaleImg should have the same data (besides image) as its parent (m_colorImg)! This rule will
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

// Get value of max RGB luminance (for grey/color images)
// @input:
// @output:
// - ERROR - can't get max luminance
// - int - posititve value of max luminance of this image
int CandidateImage::GetMaxRGBLum()
{
	ImgSearchParam imgSearcher;
	if ( false == m_greyImg.IsNull() )
	{
		return imgSearcher.FindMaxLum(m_greyImg);
	}
	else
	{
		if ( false == m_colorImg.IsNull() )
		{
			return imgSearcher.FindMaxLum(m_colorImg);
		}
	}

	qDebug() << "GetMaxRGBLum(): Error - no images";
	return ERROR;
}

// Get value of min RGB luminance (for grey/color images)
// @input:
// @output:
// - ERROR - can't get min luminance
// - int - posititve value of min luminance of this image
int CandidateImage::GetMinRGBLum()
{
	ImgSearchParam imgSearcher;
	if ( false == m_greyImg.IsNull() )
	{
		return imgSearcher.FindMinLum(m_greyImg);
	}
	else
	{
		if ( false == m_colorImg.IsNull() )
		{
			return imgSearcher.FindMinLum(m_colorImg);
		}
	}

	qDebug() << "GetMinRGBLum(): Error - no images";
	return ERROR;
}

// Get luminance histogram of this image
// @input:
// @output:
// - empty QList<int> - can't get luminance histogram
// - unempty QList<int> - luminance histogram of this image
QList<int> CandidateImage::GetRGBLumHistogram()
{
	QList<int> empty;
	return empty;
}

// Get histogram of each RGB channel (red, green, blue) of this image
// @input:
// @output:
// - empty QList< QList<int> > - can't get luminance histogram
// - unempty QList< QList<int> > - histogram of each RGB channels of this image
QList< QList<int> > CandidateImage::GetRGBHistogram()
{
	QList< QList<int> > empty;
	return empty;
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

	int minLim = GetMinRGBLum();
	int maxLim = GetMaxRGBLum();
	qDebug() << "Min luminance:" << minLim;
	qDebug() << "Max luminance:" << maxLim;
}
