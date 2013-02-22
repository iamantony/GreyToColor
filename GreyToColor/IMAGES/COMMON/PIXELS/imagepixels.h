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

#ifndef IMAGEPIXELS_H
#define IMAGEPIXELS_H

#include <QObject>
#include <QImage>

class ImagePixels : public QObject
{
	Q_OBJECT

	// == DATA ==
public:
	unsigned int m_width;
	unsigned int m_height;

	// == METHODS ==
public:
	explicit ImagePixels(QObject *parent = 0);
	~ImagePixels();

	// Save all pixels from input QImage as custom pixels
	virtual bool FormImgPixels(const QImage &t_img) = 0;
	// Transform all image pixels from RGB color space to LAB
	virtual void TransAllPixRGB2LAB() = 0;
	// Transform all image pixels from LAB color space to RGB
	virtual void TransAllPixLAB2RGB() = 0;
	// Get Luminance of pixel with certain coords
	virtual double GetPixChLum(const unsigned int &t_width, const unsigned int &t_height) const = 0;
	// Get value of channel A of pixel with certain coords
	virtual double GetPixChA(const unsigned int &t_width, const unsigned int &t_height) const = 0;
	// Get value of channel B of pixel with certain coords
	virtual double GetPixChB(const unsigned int &t_width, const unsigned int &t_height) const = 0;
	// Set value for channels A and B of pixel with certain coords
	virtual void SetPixChannelsAB(const unsigned int &t_width,
								  const unsigned int &t_height,
								  const double &t_chA,
								  const double &t_chB)= 0;

	// Find among all pixels in image value of max luminance
	virtual double FindMaxLum() const = 0;
	// Find among all pixels in image value of min luminance
	virtual double FindMinLum() const = 0;

	// TODO:
	// - send that functions to TargetImgPixels
//	// Scale luminance of all pixels in image with certain scale factor
//	virtual void ScaleLum(const double &t_scaleFactor) = 0;
//	// Unscale luminance of all pixels in image
//	virtual void UnScaleLum() = 0;


	// Calc for each pixel in image it's SKO
	void CalcPixelsSKO();
//	// Get SKO of pixel with certain coords
//	virtual double GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const = 0;
//	// Check if pixel with certain coords is greyscale
//	virtual bool IsPixGrey(const unsigned int &t_width, const unsigned int &t_height) const = 0;

protected:
	// Clear all info (set to defaults)
	void Clear();
	// Check if we have pixel with such coords
	bool IsPixelExist(const unsigned int &t_width, const unsigned int &t_height) const;
	// Check if we have pixels of image
	bool HasPixels() const;
	// Transform certain pixel from RGB color space to LAB
	virtual void TransformPixRGB2LAB(const unsigned int &t_width, const unsigned int &t_height) = 0;
	// Transform certain pixel from LAB color space to RGB
	virtual void TransformPixLAB2RGB(const unsigned int &t_width, const unsigned int &t_height) = 0;
	// Calc for certain pixel in image it's SKO
	virtual void CalcPixSKO(const unsigned int &t_width, const unsigned int &t_height) = 0;
};

#endif // IMAGEPIXELS_H
