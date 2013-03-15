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

#include "rgblab.h"

RGBLAB::RGBLAB()
{
}

// Transform color from RGB color space to LAB color space
// @input:
// - RGB - RGB color
// @output:
// - LAB - mapped RGB color in LAB color space
LAB RGBLAB::RGB2LAB(const RGB &t_rgbColor)
{
	const int R = t_rgbColor.GetRed();
	const int G = t_rgbColor.GetGreen();
	const int B = t_rgbColor.GetBlue();

	double L = 0.3811*R + 0.5783*G + 0.0402*B;
	double M = 0.1967*R + 0.7244*G + 0.0782*B;
	double S = 0.0241*R + 0.1288*G + 0.8444*B;

	if ( 0 == L )
	{
		L = 0.0001;
	}

	if ( 0 == M )
	{
		M = 0.0001;
	}

	if ( 0 == S )
	{
		S = 0.0001;
	}

	L = log10(L);
	M = log10(M);
	S = log10(S);

	double chL = 0.5774*L + 0.5774*M + 0.5774*S;
	double chA = 0.4082*L + 0.4082*M - 0.8165*S;
	double chB = 0.7071*L - 0.7071*M;

	if ( chL < 0 )
	{
		chL = 0;
	}

	LAB labColor(chL,
				 chA,
				 chB);

	return labColor;
}

// Transform color from LAB color space to RGB color space
// @input:
// - LAB - LAB color
// @output:
// - RGB - mapped LAB color in RGB color space
RGB RGBLAB::LAB2RGB(const LAB &t_labColor)
{
	const double chL = t_labColor.GetChL();
	const double chA = t_labColor.GetChA();
	const double chB = t_labColor.GetChB();

	double L = 0.5774*chL + 0.4082*chA + 0.7071*chB;
	double M = 0.5774*chL + 0.4082*chA - 0.7071*chB;
	double S = 0.5774*chL - 0.8165*chA;

	L = pow(10, L);
	M = pow(10, M);
	S = pow(10, S);

	int R = 4.4679*L - 3.5873*M + 0.1193*S;
	int G = (-1.2186)*L + 2.3809*M - 0.1624*S;
	int B = 0.0497*L - 0.2439*M + 1.2045*S;

	if(R < 0)
	{
		R = 0;
	}
	else if( 255 < R )
	{
		R = 255;
	}

	if(G < 0)
	{
		G = 0;
	}
	else if( 255 < G )
	{
		G = 255;
	}

	if(B < 0)
	{
		B = 0;
	}
	else if( 255 < B )
	{
		B = 255;
	}

	RGB rgbColor(R, G, B);

	return rgbColor;
}
