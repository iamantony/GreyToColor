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

#ifndef IMGFILTER_H
#define IMGFILTER_H

#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include "./IMAGES/COMMON/image.h"
#include "./SERVICE/KERNELS/kernelcreator.h"
#include "imgtransform.h"
#include "./DEFINES/imgservice.h"
#include "./DEFINES/global.h"

class ImgFilter
{
	// == DATA ==

	// == METHODS ==
public:
	ImgFilter();

	// Get gradiented image, processed by special kernel (operator)
	Image GetGradientImage(const Image &t_img, const Kernel::Type &t_type);

	// Test image gradient processing
	void TestGradientProc();

private:
	// Form gradient image copy
	QImage FormGradientImgCopy(const QImage &t_img,
							   const Kernel::Type &t_type,
							   const QList<QList<QList<double> > > &t_kernels);

	// Get pixel result value
	int PixelResultValue(const QList<double> t_results, const Kernel::Type &t_type);
};

#endif // IMGFILTER_H
