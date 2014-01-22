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

#ifndef LAB_H
#define LAB_H

class LAB
{
	// == DATA ==
private:
	double m_Lum;
	double m_A;
	double m_B;

	// == METHODS ==
public:
	LAB(const double &t_L = 0.0,
		const double &t_A = 0.0,
		const double &t_B = 0.0);

	~LAB();

	// Set LAB color
	bool SetColor(const double &t_chL = 0.0,
				  const double &t_chA = 0.0,
				  const double &t_chB = 0.0);

	// Return Luminance channel value
	double GetChL() const;
	// Return A-channel value
	double GetChA() const;
	// Return B-channel value
	double GetChB() const;
	// Set new luminance
	bool SetChL(const double &t_chL);
	// Set new channel A
	void SetChA(const double &t_chA);
	// Set new channel B
	void SetChB(const double &t_chB);

private:
	// Clear color
	void Clear();
	// Check value for Luminance channel
	bool CheckLuminance(const double &t_lum) const;
};

#endif // LAB_H
