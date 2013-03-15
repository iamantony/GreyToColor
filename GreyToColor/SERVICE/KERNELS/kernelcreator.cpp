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

#include "kernelcreator.h"

KernelCreator::KernelCreator()
{

}

// Get kernel matrix
// @input:
// - Kernel::Type - exist kernel type
// @output:
// - empty QList< QList< QList<double> > > - failed to create kernel
// - QList< QList< QList<double> > > - kernel matrix
QList< QList< QList<double> > > KernelCreator::GetKernel(const Kernel::Type &t_type)
{
	QList< QList< QList<double> > > kernel;
	switch(t_type)
	{
		case Kernel::SOBEL:
			kernel = GetSobelKernel();
			break;

		case Kernel::DEFAULT_LAST:
		default:
		{
			qDebug() << "GetKernel(): Error - invalid irguments";
			QList< QList< QList<double> > > empty;
			return empty;
		}
	}

	return kernel;
}

// Create Sobel kernel matrix
// @input:
// @output:
// - QList< QList< QList<double> > > - Sobel kernel matrix
QList< QList< QList<double> > > KernelCreator::GetSobelKernel()
{
	QList< QList< QList<double> > > sobelKernel;

	// Form first matrix (X matrix rotated to -45 degrees)
	QList< QList<double> > xKernelMinus45;
	QList<double> xKM45FirstLine;
	xKM45FirstLine << 0 << -1 << -2;

	QList<double> xKM45SecondLine;
	xKM45SecondLine << 1 << 0 << -1;

	QList<double> xKM45ThirdLine;
	xKM45ThirdLine << 2 << 1 << 0;

	xKernelMinus45 << xKM45FirstLine << xKM45SecondLine << xKM45ThirdLine;

	// Form second matrix (X matrix rotated to +45 degrees)
	QList< QList<double> > xKernelPlus45;
	QList<double> xKP45FirstLine;
	xKP45FirstLine << 2 << 1 << 0;

	QList<double> xKP45SecondLine;
	xKP45SecondLine << 1 << 0 << -1;

	QList<double> xKP45ThirdLine;
	xKP45ThirdLine << 0 << -1 << -2;

	xKernelPlus45 << xKP45FirstLine << xKP45SecondLine << xKP45ThirdLine;

	// Form third matrix (Y matrix rotated to -45 degrees)
	QList< QList<double> > yKernelMinus45;
	QList<double> yKM45FirstLine;
	yKM45FirstLine << 2 << 1 << 0;

	QList<double> yKM45SecondLine;
	yKM45SecondLine << 1 << 0 << -1;

	QList<double> yKM45ThirdLine;
	yKM45ThirdLine << 0 << -1 << -2;

	yKernelMinus45 << yKM45FirstLine << yKM45SecondLine << yKM45ThirdLine;

	// Form forth matrix (Y matrix rotated to +45 degrees)
	QList< QList<double> > yKernelPlus45;
	QList<double> yKP45FirstLine;
	yKP45FirstLine << 0 << 1 << 2;

	QList<double> yKP45SecondLine;
	yKP45SecondLine << -1 << 0 << 1;

	QList<double> yKP45ThirdLine;
	yKP45ThirdLine << -2 << -1 << 0;

	yKernelPlus45 << yKP45FirstLine << yKP45SecondLine << yKP45ThirdLine;

	// Add all kernel matrix
	sobelKernel.append(xKernelMinus45);
	sobelKernel.append(xKernelPlus45);
	sobelKernel.append(yKernelMinus45);
	sobelKernel.append(yKernelPlus45);

	return sobelKernel;
}
