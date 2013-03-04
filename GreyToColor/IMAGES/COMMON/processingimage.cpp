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

#include "processingimage.h"

ProcessingImage::ProcessingImage()
{

}

// Clear class info
// @input:
// @output:
void ProcessingImage::Clear()
{
	m_img.Clear();
	if ( NULL != m_imgPixels )
	{
		delete m_imgPixels;
		m_imgPixels = NULL;
	}

	m_similarAreas.clear();
}

// Check if we have loaded image
// @input:
// @output:
// - true - we have loaded image and all pixels of it have constructed
// - false - no image or no pixels
bool ProcessingImage::HasImage()
{
	if ( (true == m_img.IsNull()) ||
		 (NULL == m_imgPixels) ||
		 (false == m_imgPixels->HasPixels()))
	{
		return false;
	}

	return true;
}

// Set image
// @input:
// - QImage - unempty image
// @output:
// - true - image set
// - false - can't set this image
bool ProcessingImage::SetImg(const QImage &t_image)
{
	bool imgSet = m_img.SetImage(t_image);
	if ( true == imgSet )
	{
		ConstructImgPixels();
		m_similarAreas.clear();
	}

	return imgSet;
}

// Set image path
// @input:
// - QString - unempty path to image
// @output:
// - true - path saved
// - false - invalid path
bool ProcessingImage::SetImgPath(const QString &t_imgPath)
{
	return m_img.SetImgPath(t_imgPath);
}

// Load image from path
// @input:
// - QString - unempty path to image
// @output:
// - true - image loaded
// - false - can't load image from input path
bool ProcessingImage::LoadImg(const QString &t_imagePath)
{
	bool imgLoaded = m_img.LoadImg(t_imagePath);
	if ( true == imgLoaded )
	{
		ConstructImgPixels();
		m_similarAreas.clear();
	}

	return imgLoaded;
}

// Construct custom pixels of loaded image
// @input:
// @output:
void ProcessingImage::ConstructImgPixels()
{
	// It's a base class. We don't use it so we don't need construct some pixel-custom-objects
}

// Get width of image
// @input:
// @output:
// - unsigned int - positive width of image (could be 0 if we don't have image)
unsigned int ProcessingImage::GetImageWidth() const
{
	return m_img.GetImgWidth();
}

// Get height of image
// @input:
// @output:
// - unsigned int - positive height of image (could be 0 if we don't have image)
unsigned int ProcessingImage::GetImageHeight() const
{
	return m_img.GetImgHeight();
}

// Transform custom pixels from RGB to LAB
// @input:
// @output:
void ProcessingImage::TransformImgRGB2LAB()
{
	m_imgPixels->TransAllPixRGB2LAB();
}

// Transform custom pixels from LAB to RGB
// @input:
// @output:
void ProcessingImage::TransformImgLAB2GRB()
{
	m_imgPixels->TransAllPixLAB2RGB();
}

// Get pixel luminance (LAB)
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel.
// - double - luminance of pixel
double ProcessingImage::PixelChLum(const unsigned int &t_width, const unsigned int &t_height) const
{
	return m_imgPixels->GetPixChLum(t_width, t_height);
}

// Get value of channel A of pixel
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel A of pixel
double ProcessingImage::PixelChA(const unsigned int &t_width, const unsigned int &t_height) const
{
	return m_imgPixels->GetPixChA(t_width, t_height);
}

// Get value of channel B of pixel
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - NO_INFO - can't find such pixel
// - double - cannel B of pixel
double ProcessingImage::PixelChB(const unsigned int &t_width, const unsigned int &t_height) const
{
	return m_imgPixels->GetPixChB(t_width, t_height);
}

// Set value for channels A and B of pixel
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// - double - value for pixels channel A
// - double - value for pixels channel B
// @output:
void ProcessingImage::SetPixelChAB(const unsigned int &t_width,
								   const unsigned int &t_height,
								   const double &t_chA,
								   const double &t_chB)
{
	m_imgPixels->SetPixChannelsAB(t_width,
								  t_height,
								  t_chA,
								  t_chB);
}

// Find among all pixels in image value of max luminance
// @input:
// @output:
// - ERROR - can't find max luminance
// - double - positive found max luminance of images pixels
double ProcessingImage::GetMaxLABLum() const
{
	return m_imgPixels->FindMaxLum();
}

// Check if pixel with certain coords is greyscale
// @input:
// - unsigned int - exist width (x) position of pixel
// - unsigned int - exist height (y) position of pixel
// @output:
// - true - pixel is grey
// - false - pixel is colourful
bool ProcessingImage::IsPixelGrey(const unsigned int &t_width, const unsigned int &t_height) const
{
	return m_imgPixels->IsPixGrey(t_width, t_height);
}

// Add image similiarity area
// @input:
// - ImgSimilarityArea - valid image similarity area
// @output:
// - true - area added
// - false - can't add such area
bool ProcessingImage::AddSimilarityArea(const ImgSimilarityArea &t_area)
{
	if ( true == m_img.IsNull() )
	{
		qDebug() << "AddSimilarityArea(): Error - no image - no area";
		return false;
	}

	if ( false == ValidateSimArea(t_area) )
	{
		qDebug() << "AddSimilarityArea(): Error - invalid area";
		return false;
	}

	// Check if we already have area with the same ID
	const unsigned int newAreaID = t_area.GetAreaID();
	const int numOfAreas = m_similarAreas.size();
	for ( int area = numOfAreas - 1; area >= 0; area-- )
	{
		unsigned int existAreaID = m_similarAreas.at(area).GetAreaID();
		if ( newAreaID == existAreaID )
		{
			// If we found such area - remove it
			m_similarAreas.removeAt(area);
		}
	}

	m_similarAreas.append(t_area);
	return true;
}

// Validate similarity area
// @input:
// - ImgSimilarityArea - valid image area
// @output:
// - true - area is valid
// - false - area is invalid
bool ProcessingImage::ValidateSimArea(const ImgSimilarityArea &t_area) const
{
	if ( false == t_area.IsValid() )
	{
		qDebug() << "ValidateSimArea(): Error - invalid arguments";
		return false;
	}

	const unsigned int imgWidth = m_img.GetImgWidth();
	const unsigned int imgHeight = m_img.GetImgHeight();

	QRect imgRect = t_area.GetAreaRect();
	const int startWidth = imgRect.x();
	const int startHeight = imgRect.y();

	if ( (startWidth < 0) ||
		 (imgWidth <= (unsigned int)startWidth) ||
		 (startHeight < 0) ||
		 (imgHeight <= (unsigned int)startHeight))
	{
		qDebug() << "ValidateSimArea(): Error - area start coords are invalid";
		return false;
	}

	const unsigned int endWidth = (unsigned int)startWidth + (unsigned int)imgRect.width();
	const unsigned int endHeight = (unsigned int)startHeight + (unsigned int)imgRect.height();
	if ( (imgWidth <= endWidth) || (imgHeight <= endHeight) )
	{
		qDebug() << "ValidateSimArea(): Error - area end coords are invalid";
		return false;
	}

	return true;
}

// Find image similarity area by ID
// @input:
// - unsigned int - area ID
// @output:
// - zero (invalid) ImgSimilarityArea - didn't find area with such id
// - ImgSimilarityArea - exist image similarity area
ImgSimilarityArea ProcessingImage::FindSimilarityArea(const unsigned int &t_id) const
{
	ImgSimilarityArea imgSimArea;
	const int numOfAreas = m_similarAreas.size();
	for ( int area = 0; area < numOfAreas; area++ )
	{
		unsigned int existAreaID = m_similarAreas.at(area).GetAreaID();
		if ( t_id == existAreaID )
		{
			imgSimArea = m_similarAreas.at(area);
		}
	}

	return imgSimArea;
}

// Test image area creating/adding/checking
void ProcessingImage::TestImgSimArea()
{
	qDebug() << endl << "TestImgSimArea():";

	qDebug() << endl << "1: Creating null area";
	TestInvalidArea();

	qDebug() << endl << "2: Creating normal area. No image";
	TestValidAreaWithoutImage();

	qDebug() << endl << "3: Adding valid area to list. Have image";
	TestValidAreaWithImage();

	qDebug() << endl << "4: Adding huge area to list. Have image";
	TestHugeValidAreaWithImage();

	qDebug() << endl << "5: Adding several areas to list. Have image";
	TestAddSevAreasWithImage();
}

// Test: create invalid area and try to add it to list
void ProcessingImage::TestInvalidArea()
{
	unsigned int nullAreaID = 0;
	QRect nullRect(0, 0, 0, 0);
	if ( true == nullRect.isEmpty() )
	{
		qDebug() << " - nullRect is empty";
	}

	if ( false == nullRect.isValid() )
	{
		qDebug() << " - nullRect is invalid";
	}

	ImgSimilarityArea testNullArea;
	bool nullAreaSet = testNullArea.SetArea(nullAreaID, nullRect);
	if ( false == nullAreaSet )
	{
		qDebug() << "PASS";
	}
	else
	{
		qDebug() << "FAIL!";
	}
}

// Test: create valid area and try to add it to list. No image
void ProcessingImage::TestValidAreaWithoutImage()
{
	unsigned int areaID = 0;
	QRect areaRect(3, 3, 10, 10);
	ImgSimilarityArea testArea;
	bool areaSet = testArea.SetArea(areaID, areaRect);
	if ( false == areaSet )
	{
		qDebug() << "FAIL!";
		return;
	}

	bool areaAdded = this->AddSimilarityArea(testArea);
	if ( false == areaAdded )
	{
		qDebug() << "PASS";
	}
	else
	{
		qDebug() << "FAIL!";
		return;
	}
}

// Test: create valid area and try to add it to list. Have image
void ProcessingImage::TestValidAreaWithImage()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												   "Open target image...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	bool imgLoaded = LoadImg(imgName);
	if ( false == imgLoaded )
	{
		qDebug() << "FAIL!";
		return;
	}

	unsigned int areaID = 0;
	QRect areaRect(1, 1, 2, 2);
	ImgSimilarityArea testArea;
	bool areaSet = testArea.SetArea(areaID, areaRect);
	if ( false == areaSet )
	{
		qDebug() << "FAIL!";
		return;
	}

	bool areaAdded = this->AddSimilarityArea(testArea);
	if ( true == areaAdded )
	{
		qDebug() << "PASS";
	}
	else
	{
		qDebug() << "FAIL!";
	}
}

// Test: create valid area and try to add it to list. Have image
void ProcessingImage::TestHugeValidAreaWithImage()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												   "Open target image...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	bool imgLoaded = LoadImg(imgName);
	if ( false == imgLoaded )
	{
		qDebug() << "FAIL!";
		return;
	}

	unsigned int areaID = 0;
	QRect areaRect(1, 1, 10000, 10000);
	ImgSimilarityArea testArea;
	bool areaSet = testArea.SetArea(areaID, areaRect);
	if ( false == areaSet )
	{
		qDebug() << "FAIL!";
		return;
	}

	bool areaAdded = this->AddSimilarityArea(testArea);
	if ( false == areaAdded )
	{
		qDebug() << "PASS";
	}
	else
	{
		qDebug() << "FAIL!";
		return;
	}
}

// Test: create several valid area and try to add them to list. Have image
void ProcessingImage::TestAddSevAreasWithImage()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												   "Open target image...",
												   QDir::currentPath(),
												   "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	bool imgLoaded = LoadImg(imgName);
	if ( false == imgLoaded )
	{
		qDebug() << "FAIL 1!";
		return;
	}

	for ( unsigned int i = 0; i < 5; i++)
	{
		unsigned int areaID = i;
		QRect areaRect(1, 1, 3, 3);
		ImgSimilarityArea testArea;
		bool areaSet = testArea.SetArea(areaID, areaRect);
		if ( false == areaSet )
		{
			qDebug() << "FAIL 2!";
			return;
		}

		bool areaAdded = this->AddSimilarityArea(testArea);
		if ( false == areaAdded )
		{
			qDebug() << "FAIL 3!";
			return;
		}
	}

	// Add new area with already used ID
	unsigned int areaID = 0;
	int pos = 2;
	int facet = 3;
	QRect areaRect(pos, pos, facet, facet);
	ImgSimilarityArea newArea;
	bool areaSet = newArea.SetArea(areaID, areaRect);
	if ( false == areaSet )
	{
		qDebug() << "FAIL 4!";
		return;
	}

	bool areaAdded = this->AddSimilarityArea(newArea);
	if ( false == areaAdded )
	{
		qDebug() << "FAIL 5!";
		return;
	}

	ImgSimilarityArea foundArea = this->FindSimilarityArea(areaID);
	if ( false == foundArea.IsValid() )
	{
		qDebug() << "FAIL 6!";
		return;
	}

	const unsigned int foundID = foundArea.GetAreaID();
	if ( foundID != areaID )
	{
		qDebug() << "FAIL 7!";
		return;
	}

	const QRect foundRect = foundArea.GetAreaRect();
	if ( (pos != foundRect.x()) ||
		 (pos != foundRect.y()) ||
		 (facet != foundRect.width()) ||
		 (facet != foundRect.height()) )
	{
		qDebug() << "FAIL 8!";
		return;
	}

	qDebug() << "PASS";
}
