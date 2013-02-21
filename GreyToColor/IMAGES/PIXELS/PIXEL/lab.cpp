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
	m_Lum = 0;
	m_A = 0;
	m_B = 0;
}

// Set LAB color
// @input:
// - double - positive value of Luminance channel
// - double - value of A channel
// - double - value of B channel
// @output:
// - true - color is possible
// - false - problems with seting such values
bool LAB::SetColor(const double &t_L,
				   const double &t_A,
				   const double &t_B)
{
	bool lumIsOK = CheckLuminance(t_L);
	if ( false == lumIsOK )
	{
		m_Lum = 0;
		m_A = 0;
		m_B = 0;

		return false;
	}

	m_Lum = t_L;
	m_A = t_A;
	m_B = t_B;

	return true;
}

// Check value for Luminance channel
// @input:
// - double - value >= 0 for luminance channel
// @output:
// - true - value for luminance channel is possible
// - false - value is impossible
bool LAB::CheckLuminance(const double &t_lum)
{
	if ( t_lum < 0 )
	{
		qDebug() << "CheckLuminance(): Error - impossible luminance:" << t_lum;
		return false;
	}

	return true;
}

// Return Luminance channel value
// @input:
// @output:
// - double - value >= 0 of Luminance channel
double LAB::GetChL() const
{
	return m_Lum;
}

// Return A-channel value
// @input:
// @output:
// - double - value of A channel
double LAB::GetChA() const
{
	return m_A;
}

// Return B-channel value
// @input:
// @output:
// - double - value of B channel
double LAB::GetChB() const
{
	return m_B;
}

// Set new luminance
// @input:
// - double - value >= 0 of Luminance channel
// @output:
// - true - new value set
// - false - impossible value
bool LAB::SetChL(const double &t_l)
{
	bool lumIsOK = CheckLuminance(t_l);
	if ( false == lumIsOK )
	{
		qDebug() << "SetChL(): Error - can't set luminance" << t_l;
		return false;
	}

	m_Lum = t_l;

	return true;
}

// Set new channel A
// @input:
// - double - value of channel A
// @output:
void LAB::SetChA(const double &t_a)
{
	m_A = t_a;
}

// Set new channel B
// @input:
// - double - value of channel B
// @output:
void LAB::SetChB(const double &t_b)
{
	m_B = t_b;
}
