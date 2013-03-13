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

#include "imgfilter.h"

ImgFilter::ImgFilter()
{

}

// Get gradiented image, processed by special kernel (operator)
// @input:
// - Image - unnull greyscale image
// - Kernel::Type - exist type of kernel
// @output:
// - null Image - failed to create gradient image
// - Image - gradient image
Image ImgFilter::GetGradientImage(const Image &t_img, const Kernel::Type &t_type)
{
	if ( (true == t_img.IsNull()) || (Kernel::DEFAULT_LAST == t_type) )
	{
		qDebug() << "GetGradientImage(): Error - invalid arguments";
		Image empty;
		return empty;
	}

	ImgTransform imgTransformer;
	Image greyscaledImg = imgTransformer.ToGrey(t_img);
	if ( true == greyscaledImg.IsNull() )
	{
		qDebug() << "GetGradientImage(): Error - can't greyscale image";
		Image empty;
		return empty;
	}

	// Get image
	QImage greyImg = greyscaledImg.GetImg();
	if ( (true == greyImg.isNull()) || (false == greyImg.isGrayscale()) )
	{
		qDebug() << "GetGradientImage(): Error - invalid image";
		Image empty;
		return empty;
	}

	// Get Kernels
	KernelCreator creator;
	QList< QList< QList<double> > > kernels = creator.GetKernel(t_type);
	if ( true == kernels.isEmpty() )
	{
		qDebug() << "GetGradientImage(): Error - invalid arguments";
		Image empty;
		return empty;
	}

	QImage gradientImg = FormGradientImgCopy(greyImg,
											t_type,
											kernels);

	Image resultImg = t_img;
	resultImg.SetImage(gradientImg);

	return resultImg;
}

// Form gradient image copy
// @input:
// - QImage - unnull greyscale image
// - Kernel::Type - exist type of kernel
// - QList< QList< QList<double> > >
// @output:
QImage ImgFilter::FormGradientImgCopy(const QImage &t_img,
									  const Kernel::Type &t_type,
									  const QList< QList< QList<double> > > &t_kernels)
{
	if ( (true == t_img.isNull()) ||
		 (false == t_img.isGrayscale()) ||
		 (Kernel::DEFAULT_LAST == t_type) ||
		 (true == t_kernels.isEmpty()))
	{
		qDebug() << "FormGradientImgCopy(): Error - invalid arguments";
		QImage empty;
		return empty;
	}

	QImage gradientImg = t_img;

	const int imgWidth = t_img.width();
	const int imgHeight = t_img.height();
	const int numOfKernels = t_kernels.size();
	// For each pixel...
	for ( int wdt = 0; wdt < imgWidth; wdt++ )
	{
		for ( int hgt = 0; hgt < imgHeight; hgt++ )
		{
			// ... calc result value by each kernel
			QList<double> kernelsResults;
			for ( int kern = 0; kern < numOfKernels; kern++ )
			{
				// Find coords of borders of matrix rectangle on image
				const QList< QList<double> > matrix = t_kernels.at(kern);
				const int facetLength = matrix.at(0).size();
				const int maxOffset = facetLength / 2;
				const int minWdt = wdt - maxOffset;
				const int maxWdt = wdt + maxOffset + 1;
				const int minHgt = hgt - maxOffset;
				const int maxHgt = hgt + maxOffset + 1;

				// Calc summ of  productions of pixels luminances and matrix cells values
				double summ = 0;
				int xMatrPos = 0;
				int yMatrPos = 0;
				for ( int currWdt = minWdt; currWdt < maxWdt; currWdt++ )
				{
					for ( int currHgt = minHgt; currHgt < maxHgt; currHgt++ )
					{
						bool pixelExist = t_img.valid(currWdt, currHgt);
						if ( true == pixelExist )
						{
							const QRgb pixel = t_img.pixel(currWdt, currHgt);
							const int pixelLum = qRed(pixel);
							summ += (double)pixelLum * matrix[xMatrPos][yMatrPos];
						}

						yMatrPos++;
					}

					// Go to the next row of matrix
					yMatrPos = 0;
					xMatrPos++;
				}

				kernelsResults.append(summ);
			}

			// Then calc final pixel color (luminance)...
			int resultPixValue = PixelResultValue(kernelsResults, t_type);
			if ( ERROR == resultPixValue )
			{
				qDebug() << "FormGradientImgCopy: Warning - failed to calc value for pixel" << wdt << hgt;
				resultPixValue = 0;
			}

			// ... and set pixel with calculated luminance to new image
			QRgb gradientPixel = qRgb(resultPixValue, resultPixValue, resultPixValue);
			gradientImg.setPixel(wdt, hgt, gradientPixel);
		}
	}

	return gradientImg;
}

// Get pixel result value
// @input:
// - QList<double> - unempty list
// - Kernel::Type - exist kernel type
// @output:
// - ERROR - failed to calc result
// - int - grey pixel RGB value [0, 255]
int ImgFilter::PixelResultValue(const QList<double> t_results, const Kernel::Type &t_type)
{
	if ( (true == t_results.isEmpty()) || (Kernel::DEFAULT_LAST == t_type) )
	{
		qDebug() << "PixelResultValue(): Error - invalid arguments";
		return ERROR;
	}

	int resultValue = ERROR;
	switch(t_type)
	{
		case Kernel::SOBEL:
		{
			// Result is mean of summ of all absoluted results
			double sobelResult = 0;
			const int resultsNum = t_results.size();
			for ( int val = 0; val < resultsNum; val++ )
			{
				sobelResult += qAbs( t_results.at(val) );
			}

			sobelResult /= (double)resultsNum;
			resultValue = (int)floor( sobelResult + 0.5 );

			break;
		}

		case Kernel::DEFAULT_LAST:
		default:
		{
			qDebug() << "PixelResultValue(): Error - invalid arguments! How do you get there??";
			return ERROR;
		}
	}

	if ( resultValue < 0 )
	{
		resultValue = 0;
	}
	else if ( 255 < resultValue )
	{
		resultValue = 255;
	}

	return resultValue;
}

// Test image gradient processing
void ImgFilter::TestGradientProc()
{
	QWidget wdt;
	QString imgName = QFileDialog::getOpenFileName(&wdt,
												 "Open target image...",
												 QDir::currentPath(),
												 "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	Image testImg;
	testImg.LoadImg(imgName);

	ImgTransform transformer;
	Image greyscaled = transformer.ToGrey(testImg);
	QString pathToSaveGrey = QFileDialog::getSaveFileName(&wdt,
														  "Save grey image as...",
														  QDir::currentPath(),
														  "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	greyscaled.SetImgPath(pathToSaveGrey);
	greyscaled.SaveImg();

	Image gradientImg = GetGradientImage(greyscaled, Kernel::SOBEL);
	if ( true == gradientImg.IsNull() )
	{
		qDebug() << "TestGradientProc(): Fail - gradient image is NULL";
		return;
	}

	QString pathToSave = QFileDialog::getSaveFileName(&wdt,
													  "Save gradient image as...",
													  QDir::currentPath(),
													  "IMG files (*.png *.jpg *.jpeg *.bmp *.tiff)");

	gradientImg.SetImgPath(pathToSave);
	gradientImg.SaveImg();
}
