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

#ifndef CANDIDATEIMAGE_H
#define CANDIDATEIMAGE_H

#include <QFileDialog>
#include <QList>
#include "../COMMON/image.h"
#include "./PARAMS/IMAGES/imgpassport.h"
#include "./SERVICE/IMAGES/imgtransform.h"
#include "SERVICE/IMAGES/imgpassportcreator.h"
#include "./DEFINES/global.h"

class CandidateImage
{
	// == DATA ==
private:
	Image m_colorImg;
	Image m_greyImg;
	QList<ImgPassport> m_passports;

	// == METHODS ==
public:
	CandidateImage();
	~CandidateImage();

	// Clear all info
	void Clear();
	// Load color image
	bool LoadColorImg(const QString &t_imgPath);
	// Set color image
	bool SetColorImg(const QImage &t_img);
	// Get color image
	Image GetColorImg() const;
	// Get grey-copy of color image
	Image GetGreyImg() const;
	// Get image passport of certain type
	ImgPassport GetPassport(const Passport::Type &t_type) const;
	// Get all passports of image
	QList<ImgPassport> GetAllPassports() const;
	// Form image passport of certain type
	bool FormPassport(const Passport::Type &t_type);
	// Form all exist image passports
	bool FormAllPassports();

	// Test loading
	void TestImageLoad();
	// Test passport forming
	void TestPassportForming();

private:
	// Get from color image it's greyscale copy
	bool ToGreyImg();
};

#endif // CANDIDATEIMAGE_H
