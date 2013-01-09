#include "imgpassport.h"

ImgPassport::ImgPassport(QObject *parent) :
	QObject(parent)
{
}

QList<QByteArray> ImgPassport::GetImgPassports(QImage *t_img)
{
	QList<QByteArray> listOfImgPassports;

	if ( NULL == t_img )
	{
		qDebug() << "GetImgPassports(): error - invalid arguments";
		return listOfImgPassports;
	}

	qDebug() << "Transformation...";
	ImgTransform imgTrans;
	imgTrans.TransColorImgToGrayImg(t_img);

	QByteArray firstPassport = GetScaledLuminancePassport(t_img);
	if ( true == firstPassport.isEmpty() )
	{
		qDebug() << "GetImgPassports(): error - unable to create first image passport";
		return listOfImgPassports;
	}

	listOfImgPassports.append(firstPassport);

	return listOfImgPassports;
}

QByteArray ImgPassport::GetScaledLuminancePassport(QImage *t_img)
{
	QByteArray passport;

	if ( NULL == t_img )
	{
		qDebug() << "GetScaledLuminancePassport(): error - invalid arguments";
		return passport;
	}

	qDebug() << "Normalisation...";
	ImgTransform imgTrans;
	bool imgNormalised = imgTrans.NormaliseImg(t_img);
	if ( false == imgNormalised )
	{
		qDebug() << "GetImgPassports(): error - can't normalize image";
		return passport;
	}

	qDebug() << "Leveling...";
	bool imgLuminanceLeveled = imgTrans.LevelLuminanceOfImg(t_img, MAX_LUM);
	if ( false == imgLuminanceLeveled )
	{
		qDebug() << "GetImgPassports(): error - can't level images luminance";
		return passport;
	}

	qDebug() << "Counting pixels...";
	QList<double> procPixelsPerLum = CountPercentOfPixelsForEachLuminance(t_img, MAX_LUM);
	if ( 0 == procPixelsPerLum.size() )
	{
		qDebug() << "GetImgPassports(): error - can't count luminance pixels";
		return passport;
	}

	qDebug() << "Forming passport...";
	for (int i = 0; i < procPixelsPerLum.size(); i++)
	{
		double procent = procPixelsPerLum.at(i);
		passport.append(reinterpret_cast<char*>(&procent), sizeof(double));
	}

	return passport;
}

QList<double> ImgPassport::CountPercentOfPixelsForEachLuminance(QImage *t_img, int t_maxLumLevel)
{
	QList<double> percentOfPixPerLum;

	if ( NULL == t_img )
	{
		qDebug() << "CountNumOfPixelsForEachLuminance(): error - invalid arguments";
		return percentOfPixPerLum;
	}

	ImgSearchParams imgSearch;
	QList<int> pixelsPerLum = imgSearch.CountNumOfPixelsForEachLuminance(t_img, t_maxLumLevel);

	if ( t_maxLumLevel != pixelsPerLum.size() )
	{
		qDebug() << "CountPercentOfPixelsForEachLuminance(): error - size of list is less then t_maxLumLevel!" ;
		return percentOfPixPerLum;
	}

	double numOfAllPixels = t_img->width() * t_img->height();
	for (int i = 0; i < t_maxLumLevel; i++)
	{
		double numOfPixels = (double)pixelsPerLum.at(i);
		if ( numOfPixels < 0 )
		{
			numOfPixels = 0;
		}

		double percent = numOfPixels/numOfAllPixels;
		percentOfPixPerLum.append(percent);
	}

//	qDebug() << pixelsPerLum << endl;
//	qDebug() << percentOfPixPerLum;

	return percentOfPixPerLum;
}

QList<double> ImgPassport::ConvertFromByteArrayToDoubleList(QByteArray t_array)
{
	QList<double> convertedArray;

	if ( true == t_array.isEmpty() )
	{
		return convertedArray;
	}

	int modulo = t_array.size()%sizeof(double);
	if ( 0 != modulo )
	{
		qDebug() << "ConvertFromByteArrayToDoubleList(): error - array is damaged";
	}

	int numOfEntries = t_array.size()/sizeof(double);
	double *number = reinterpret_cast<double*>(t_array.data());
	for (int i = 0; i < numOfEntries; i++)
	{
		convertedArray.append(*number);
		number++;
	}

	return convertedArray;
}
