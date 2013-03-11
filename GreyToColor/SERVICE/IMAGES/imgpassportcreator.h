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

#ifndef IMGPASSPORTCREATOR_H
#define IMGPASSPORTCREATOR_H

#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include "./IMAGES/COMMON/image.h"
#include "imghistogram.h"
#include "imgsubsampler.h"
#include "imgtransform.h"
#include "DEFINES/images.h"

class ImgPassportCreator
{
	// == DATA ==

	// == METHODS ==
public:
	ImgPassportCreator();

	// Get image passport of certain type
	QList<double> GetImgPassport(const Image &t_img, const Passport::Type &t_type);

private:
	// Get image passport based on luminance histogram of image
	QList<double> GetLuminancePassport(const Image &t_img);
	// Get image passport based on luminance of sunbsampled image
	QList<double> GetSubsamplLumPassport(const Image &t_img);
	// Get image passport based on luminance and gradien histograms of image
	QList<double> GetLumAndGradPassport(const Image &t_img);
	// Get image passport based on luminance and gradien of subsampled image
	QList<double> GetSubsamplLumAndGradPassport(const Image &t_img);
};

#endif // IMGPASSPORTCREATOR_H
