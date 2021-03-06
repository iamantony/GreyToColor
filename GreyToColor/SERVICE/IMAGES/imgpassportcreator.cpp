/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2013, Antony Cherepanov <antony.cherepanov@gmail.com>
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

#include "imgpassportcreator.h"

ImgPassportCreator::ImgPassportCreator()
{

}

// Get image passport of certain type
// @input:
// - Image - unnull image (color/grey)
// - Passport::Type - exist image passport type
// @output:
// - empty QList<double> - failed to create image passport
// - QList<double> - image passport
QList<double> ImgPassportCreator::GetImgPassport(const Image &t_img, const Passport::Type &t_type)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "GetImgPassport(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	QList<double> passport;

	switch(t_type)
	{
		case Passport::LUM_HISTOGRAM:
			passport = GetLuminancePassport(t_img);
			break;

		case Passport::LUM_SUBSAMPLE:
			passport = GetSubsamplLumPassport(t_img);
			break;

		case Passport::LUM_AND_GRAD_HIST:
			passport = GetLumGradHistPassport(t_img);
			break;

		case Passport::LUM_AND_GRAD_SUB:
			passport = GetSubsamplLumGradPassport(t_img);
			break;

		case Passport::DEFAULT_LAST:
		{
			qDebug() << "GetImgPassport(): Error - no such passport";
			QList<double> empty;
			return empty;
		}
	}

	if ( PASSPORT_LENGTH != passport.size() )
	{
		qDebug() << "GetImgPassport(): Error - failed to create image passport";
		QList<double> empty;
		return empty;
	}

	return passport;
}

// Get image passport based on luminance histogram of image
// @input:
// - Image - unnull image (color/grey)
// @output:
// - empty QList<double> - failed to create image passport
// - QList<double> - image passport
QList<double> ImgPassportCreator::GetLuminancePassport(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "GetLuminancePassport(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	ImgHistogram histogramer;
	QList<double> passport = histogramer.RGBLumHistogram(t_img, PASSPORT_LENGTH);

	return passport;
}

// Get image passport based on luminance of sunbsampled image
// @input:
// - Image - unnull image (color/grey)
// @output:
// - empty QList<double> - failed to create image passport
// - QList<double> - image passport
QList<double> ImgPassportCreator::GetSubsamplLumPassport(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "GetSubsamplLumPassport(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	ImgSubsampler sampler;
	QList<double> passport = sampler.SubsampleImg(t_img,
												  SAMPLES_ON_FACET,
												  SAMPLES_ON_FACET);

	return passport;
}

// Get image passport based on luminance and gradien histograms of image
// @input:
// - Image - unnull image (color/grey)
// @output:
// - empty QList<double> - failed to create image passport
// - QList<double> - image passport
QList<double> ImgPassportCreator::GetLumGradHistPassport(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "GetLumGradHistPassport(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	ImgFilter filter;
	Image gradImg = filter.GetGradientImage(t_img, Kernel::SOBEL);

	ImgHistogram histogramer;
	QList<double> lumPassport = histogramer.RGBLumHistogram(t_img, PASSPORT_LENGTH / 2);
	QList<double> gradPassport = histogramer.RGBLumHistogram(gradImg, PASSPORT_LENGTH / 2);

	QList<double> resultPassport;
	resultPassport.append(lumPassport);
	resultPassport.append(gradPassport);

	return resultPassport;
}

// Get image passport based on luminance and gradien of subsampled image
// @input:
// - Image - unnull image (color/grey)
// @output:
// - empty QList<double> - failed to create image passport
// - QList<double> - image passport
QList<double> ImgPassportCreator::GetSubsamplLumGradPassport(const Image &t_img)
{
	if ( true == t_img.IsNull() )
	{
		qDebug() << "GetLumGradHistPassport(): Error - invalid arguments";
		QList<double> empty;
		return empty;
	}

	ImgFilter filter;
	Image gradImg = filter.GetGradientImage(t_img, Kernel::SOBEL);

	ImgSubsampler sampler;
	QList<double> lumPassport = sampler.SubsampleImg(t_img,
													 SAMPLES_ON_FACET,
													 SAMPLES_ON_FACET / 2);

	QList<double> gradPassport = sampler.SubsampleImg(gradImg,
													  SAMPLES_ON_FACET,
													  SAMPLES_ON_FACET / 2);

	QList<double> resultPassport;
	resultPassport.append(lumPassport);
	resultPassport.append(gradPassport);

	return resultPassport;
}

// Create dummy passport
// @input:
// @output:
// - QList<double> - dummy passport, full of (-1)
QList<double> ImgPassportCreator::CreateDummyPassport()
{
	QList<double> dummyPass;
	for ( int ent = 0; ent < PASSPORT_LENGTH; ent++ )
	{
		dummyPass.append(ERROR);
	}

	return dummyPass;
}
