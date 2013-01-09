#include "comparestuff.h"

CompareStuff::CompareStuff(QObject *parent) :
	QObject(parent)
{
}

double CompareStuff::calcImagesSKO(QImage t_orig, QImage t_coloured)
{
	int origW = t_orig.width();
	int origH = t_orig.height();
	int colorW = t_coloured.width();
	int colorH = t_coloured.height();

	// do our images have the same size?
	if ( (origW != colorW) || (origH != colorH) )
		return -1;

	QColor pixelOrig;
	QColor pixelColor;
	double SKO = 0.0;
	for (int x = 0; x < origW; x++)
	{
		for (int y = 0; y < origH; y++)
		{
			pixelOrig = t_orig.pixel(x, y);
			pixelColor = t_coloured.pixel(x, y);

			int rOrig = pixelOrig.red();
			int rColor = pixelColor.red();
			int diffRed = pow( (rOrig - rColor), 2 );

			int gOrig = pixelOrig.green();
			int gColor = pixelColor.green();
			int diffGreen = pow( (gOrig - gColor), 2);

			int bOrig = pixelOrig.blue();
			int bColor = pixelColor.blue();
			int diffBlue = pow( (bOrig - bColor), 2);

			SKO += diffRed + diffGreen + diffBlue;
		}
	}

//	SKO = pow(SKO, 0.5);
	SKO = SKO/(origW*origH);
	if (SKO < MIN_SKO)
		SKO = 0;

	return SKO;
}

double CompareStuff::CalcPassportsSKO(QList<double> &t_target, QList<double> &t_source)
{
	double resultSKO = 1000000;

	if ( (true == t_target.isEmpty()) || (true == t_source.isEmpty()) )
	{
		qDebug() << "CalcPassportsSKO(): error - invalid arguments";
		return resultSKO;
	}

	if ( t_target.size() != t_source.size() )
	{
		qDebug() << "CalcPassportsSKO(): error - size of passports isn't the same";
		return resultSKO;
	}

	double targetItem;
	double sourceItem;
	double diff;

	for (int i = 0; i < t_target.size(); i++)
	{
		targetItem = t_target.at(i);
		sourceItem = t_source.at(i);
		diff = pow( (targetItem - sourceItem), 2);
		resultSKO += diff;
	}

	resultSKO = resultSKO/t_target.size();

	return resultSKO;
}
