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

#ifndef COLORPIXEL_H
#define COLORPIXEL_H

#include <QDebug>

#include "../../COMMON/PIXELS/pixel.h"
#include "./DEFINES/pixels.h"
#include "./DEFINES/global.h"

class ColorPixel : public Pixel
{
	// == DATA ==
private:
	// In m_relativeLum we save relative LAB Luminance. It has range [0, 1]
	double m_relativeLum;
	// All other characteristics values also relative. They have range [0, 1]
	double m_sko;
	double m_entropy;
	double m_skewness;
	double m_kurtosis;

	// == METHODS ==
public:
	ColorPixel();
	~ColorPixel();

	// Clear color pixel
	void ClearColor();
	// Calc relative value of LAB luminance
	void CalcRelativeLum();
	// Get relative LAB luminance value
	double GetRelativeLum() const;
	// Set relative LAB luminance value
	bool SetRelativeLum(const double &t_lum);
	// Set SKO for pixel of image
	bool SetSKO(const double &t_sko);
	// Set SKO for pixel of image
	double GetSKO() const;
	// Set entropy for pixel of image
	bool SetEntropy(const double &t_entropy);
	// Set entropy for pixel of image
	double GetEntropy() const;
	// Set skewness for pixel of image
	bool SetSkewness(const double &t_skewness);
	// Set skewness for pixel of image
	double GetSkewness() const;
	// Set kurtosis for pixel of image
	bool SetKurtosis(const double &t_kurtosis);
	// Set kurtosis for pixel of image
	double GetKurtosis() const;
};

#endif // COLORPIXEL_H
