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

#ifndef PROCESSINGIMAGE_H
#define PROCESSINGIMAGE_H

#include "image.h"
#include "../COMMON/PIXELS/imagepixels.h"

class ProcessingImage
{
	// == DATA ==
protected:
	Image m_img;
	// Do not create! It's a base class! Init only in children classes
	ImagePixels *m_imgPixels;

	// == METHODS ==
public:
	ProcessingImage();

	// Clear class info
	virtual void Clear();
	// Set image
	bool SetImg(const QImage &t_image);
	// Set image path
	bool SetImgPath(const QString &t_imgPath);
	// Load image from path
	bool LoadImg(const QString &t_imagePath);
	// Get width of image
	unsigned int GetImageWidth() const;
	// Get height of image
	unsigned int GetImageHeight() const;
	// Transform custom pixels from RGB to LAB
	void TransformImgRGB2LAB();
	// Transform custom pixels from LAB to RGB
	void TransformImgLAB2GRB();
	// Get pixel luminance (LAB)
	double PixelChLum(const unsigned int &t_width, const unsigned int &t_height) const;
	// Get value of channel A of pixel
	double PixelChA(const unsigned int &t_width, const unsigned int &t_height) const;
	// Get value of channel B of pixel
	double PixelChB(const unsigned int &t_width, const unsigned int &t_height) const;
	// Set value for channels A and B of pixel
	void SetPixelChAB(const unsigned int &t_width,
					  const unsigned int &t_height,
					  const double &t_chA,
					  const double &t_chB);

	// Find among all pixels in image value of max luminance
	double GetMaxLABLum() const;
	// Check if pixel with certain coords is greyscale
	bool IsPixelGrey(const unsigned int &t_width, const unsigned int &t_height) const;

protected:
	// Construct custom pixels of loaded image
	virtual void ConstructImgPixels();
};

#endif // PROCESSINGIMAGE_H
