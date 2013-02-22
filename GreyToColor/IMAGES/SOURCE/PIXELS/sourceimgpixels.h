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

#ifndef SOURCEIMGPIXELS_H
#define SOURCEIMGPIXELS_H

#include <QImage>
#include <QDebug>
#include "../../COMMON/PIXELS/imagepixels.h"
#include "colorpixel.h"
#include "./SERVICE/calculatorsko.h"
#include "./DEFINES/pixels.h"

class SourceImgPixels : public ImagePixels
{
	// == DATA ==
	QList< QList<ColorPixel> > m_pixels;

	// == METHODS ==
public:
	SourceImgPixels();
	~SourceImgPixels();

	// Clear all info
	void ClearPixels();
	// Save all pixels from input QImage as custom pixels
	bool FormImgPixels(const QImage &t_img);
	// Transform all image pixels from RGB color space to LAB
	void TransAllPixRGB2LAB();
	// Transform all image pixels from LAB color space to RGB
	void TransAllPixLAB2RGB();
	// Get Luminance of pixel with certain coords
	double GetPixChLum(const unsigned int &t_width, const unsigned int &t_height) const;
	// Get value of channel A of pixel with certain coords
	double GetPixChA(const unsigned int &t_width, const unsigned int &t_height) const;
	// Get value of channel B of pixel with certain coords
	double GetPixChB(const unsigned int &t_width, const unsigned int &t_height) const;
	// Set value for channels A and B of pixel with certain coords
	void SetPixChannelsAB(const unsigned int &t_width,
						  const unsigned int &t_height,
						  const double &t_chA,
						  const double &t_chB);

	// Find among all pixels in image value of max luminance
	double FindMaxLum() const;
	// Find among all pixels in image value of min luminance
	double FindMinLum() const;


private:
	// Transform certain pixel from RGB color space to LAB
	void TransformPixRGB2LAB(const unsigned int &t_width, const unsigned int &t_height);
	// Transform certain pixel from LAB color space to RGB
	void TransformPixLAB2RGB(const unsigned int &t_width, const unsigned int &t_height);
	// Calc for certain pixel in image it's SKO
	void CalcPixSKO(const unsigned int &t_width, const unsigned int &t_height);
	// Get list of luminances of neighbor pixels (to calc SKO)
	QList<double> GetPixNeighborsLum(const unsigned int &t_width, const unsigned int &t_height) const;
};

#endif // SOURCEIMGPIXELS_H
