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

#ifndef RGB_H
#define RGB_H

class RGB
{
	// == DATA ==
private:
	int m_red;
	int m_green;
	int m_blue;

	// == METHODS ==
public:
	RGB(const int &t_red = 0,
		const int &t_green = 0,
		const int &t_blue = 0);

	~RGB();

	// Set RGB color
	bool SetColor(const int &t_red = 0,
				   const int &t_green = 0,
				   const int &t_blue = 0);

	// Get red channel value
	int GetRed() const;
	// Get green channel value
	int GetGreen() const;
	// Get blue channel value
	int GetBlue() const;
	// Check if color is grey
	bool IsGreyColor() const;
	// Transform to grey color
	void ToGrey();

private:
	bool CheckChannelValue(const int &t_value) const;
};

#endif // RGB_H
