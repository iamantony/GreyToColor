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

		case Passport::LUM_AND_GRAD:
		case Passport::LUM_AND_GRAD_SUBSAMPLE:
		{
			qDebug() << "GetImgPassport(): Warning - passport" << t_type << "created is dummy";
			passport = CreateDummyPassport();
			break;
		}

		case Passport::DEFAULT_LAST:
		{
			qDebug() << "GetImgPassport(): Error - no such passport";
			QList<double> empty;
			return empty;
		}
	}

	if ( true == passport.isEmpty() )
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
	QList<double> passport = histogramer.LuminanceHistogram(t_img);

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
	QList<double> passport = sampler.SubsampleImg(t_img, SAMPLES_ON_FACET);

	return passport;
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
		dummyPass.append(-1);
	}

	return dummyPass;
}
