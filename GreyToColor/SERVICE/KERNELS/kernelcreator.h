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

#ifndef KERNELCREATOR_H
#define KERNELCREATOR_H

#include <QList>
#include <QDebug>
#include "./DEFINES/imgservice.h"

class KernelCreator
{
public:
	KernelCreator();

	QList< QList< QList<double> > > GetKernel(const Kernel::Type &t_type);

private:
	// Create Sobel kernel matrix
	QList< QList< QList<double> > > GetSobelKernel();
};

#endif // KERNELCREATOR_H
