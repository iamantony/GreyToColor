#include "rgblab.h"

RGBLAB::RGBLAB()
{
}

QList<double> RGBLAB::RGB2LAB(const int &t_Red, const int &t_Green, const int &t_Blue)
{
	QList<double> massLAB;

	if ( (ERROR == t_Red) || (ERROR == t_Green) || (ERROR == t_Blue) )
	{
		qDebug() << "TransToRGB(): Error - value of LAB pixel undefined.";
		return massLAB;
	}

	int R = t_Red;
	if(R < 0)
	{
		R = 0;
	}
	else if( 255 < R )
	{
		R = 255;
	}

	int G = t_Green;
	if(G < 0)
	{
		G = 0;
	}
	else if( 255 < G )
	{
		G = 255;
	}

	int B = t_Blue;
	if(B < 0)
	{
		B = 0;
	}
	else if( 255 < B )
	{
		B = 255;
	}

	double L = 0.3811*R + 0.5783*G + 0.0402*B;
	double M = 0.1967*R + 0.7244*G + 0.0782*B;
	double S = 0.0241*R + 0.1288*G + 0.8444*B;

	L = log10(L);
	M = log10(M);
	S = log10(S);

	double LL = 0.5774*L + 0.5774*M + 0.5774*S;
	double AA = 0.4082*L + 0.4082*M - 0.8165*S;
	double BB = 0.7071*L - 0.7071*M;

	massLAB << LL << AA << BB;

	return massLAB;
}

QList<int> RGBLAB::LAB2RGB(const double &t_LL, const double &t_AA, const double &t_BB)
{
	QList<int> massRGB;

	if ( (ERROR == t_LL) || (ERROR == t_AA) || (ERROR == t_BB) )
	{
		qDebug() << "TransToRGB(): Error - value of LAB pixel undefined.";
		return massRGB;
	}

	double L = 0.5774*t_LL + 0.4082*t_AA + 0.7071*t_BB;
	double M = 0.5774*t_LL + 0.4082*t_AA - 0.7071*t_BB;
	double S = 0.5774*t_LL - 0.8165*t_AA;

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

	massRGB << R << G << B;

	return massRGB;
}
