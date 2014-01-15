/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2014, Antony Cherepanov <antony.cherepanov@gmail.com>
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

#include <QDebug>
#include "lab.h"

LAB::LAB(const double &t_L,
		 const double &t_A,
		 const double &t_B)
{
	SetColor(t_L,
			 t_A,
			 t_B);
}

LAB::~LAB()
{
	m_Lum = 0.0;
	m_A = 0.0;
	m_B = 0.0;
}

// Set LAB color
// @input:
// - t_chL - positive value of Luminance channel
// - t_chA - value of A channel
// - t_chB - value of B channel
// @output:
// - true - color is possible
// - false - color is impossible
bool LAB::SetColor(const double &t_chL,
				   const double &t_chA,
				   const double &t_chB)
{
	bool lumIsOK = CheckLuminance(t_chL);
	if ( false == lumIsOK )
	{
		m_Lum = 0.0;
		m_A = 0.0;
		m_B = 0.0;

		return false;
	}

	m_Lum = t_chL;
	m_A = t_chA;
	m_B = t_chB;

	return true;
}

// Check value for Luminance channel
// @input:
// - t_lum - value >= 0 for luminance channel
// @output:
// - true - value for luminance channel is possible
// - false - value is impossible
bool LAB::CheckLuminance(const double &t_lum) const
{
	if ( t_lum < 0.0 )
	{
		qDebug() << "CheckLuminance(): Error - impossible luminance:" << t_lum;
		return false;
	}

	return true;
}

// Get Luminance channel value
// @input:
// @output:
// - double - value >= 0 of Luminance channel
double LAB::GetChL() const
{
	return m_Lum;
}

// Get A-channel value
// @input:
// @output:
// - double - value of A channel
double LAB::GetChA() const
{
	return m_A;
}

// Get B-channel value
// @input:
// @output:
// - double - value of B channel
double LAB::GetChB() const
{
	return m_B;
}

// Set new luminance
// @input:
// - t_chL - value >= 0 of Luminance channel
// @output:
// - true - new value set
// - false - impossible value
bool LAB::SetChL(const double &t_chL)
{
	bool lumIsOK = CheckLuminance(t_chL);
	if ( false == lumIsOK )
	{
		qDebug() << "SetChL(): Error - can't set luminance" << t_chL;
		return false;
	}

	m_Lum = t_chL;

	return true;
}

// Set new channel A
// @input:
// - double - value of channel A
// @output:
void LAB::SetChA(const double &t_chA)
{
	m_A = t_chA;
}

// Set new channel B
// @input:
// - t_chB - value of channel B
// @output:
void LAB::SetChB(const double &t_chB)
{
	m_B = t_chB;
}
