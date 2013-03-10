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

#ifndef TARGETIMAGE_H
#define TARGETIMAGE_H

#include "../COMMON/processingimage.h"
#include "../TARGET/PIXELS/targetimgpixels.h"
#include "../COMMON/PIXELS/rgb.h"
#include "./PARAMS/IMAGES/imgpassport.h"
#include "./SERVICE/IMAGES/imgtransform.h"
#include "./SERVICE/IMAGES/imgpassportcreator.h"
#include "./DEFINES/images.h"

class TargetImage : public ProcessingImage
{
	// == DATA ==
private:
	QList<ImgPassport> m_passports;

	// == METHODS ==
public:
	TargetImage();
	~TargetImage();

	// Clear all info
	virtual void Clear();
	// Calc for each pixel in image it's SKO
	void CalcPixelsSKO();
	// Get SKO of pixel with certain coords
	double GetPixelsSKO(const unsigned int &t_width, const unsigned int &t_height) const;
	// Scale luminance of all pixels in image with certain scale factor
	bool ScaleLABLum(const double &t_scaleFactor);
	// Unscale luminance of all pixels in image
	void UnScaleLABLum();
	// Set prefered color for certain pixel
	void SetPixPrefColor(const unsigned int &t_width,
						 const unsigned int &t_height,
						 const RGB &t_prefColor);

	// Get image passport of certain type
	ImgPassport GetPassport(const Passport::Type &t_type) const;
	// Get all passports of image
	QList<ImgPassport> GetAllPassports() const;
	// Form image passport of certain type for Target Image
	bool FormPassport(const Passport::Type &t_type);
	// Form all exist image passports
	bool FormAllPassports();
	// Get result image. It could be colorized (if we perform colorization) or
	// greyscale as original target (if we have not performed colorizztion yet).
	Image GetResultImage();

private:
	// Construct custom pixels of loaded image
	virtual void ConstructImgPixels();
	// Add new passport to list of pasports of current image
	void AddPasport(const ImgPassport &t_passport);
};

#endif // TARGETIMAGE_H
