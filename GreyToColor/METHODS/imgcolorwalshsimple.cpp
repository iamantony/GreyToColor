#include "imgcolorwalshsimple.h"

ImgColorWalshSimple::ImgColorWalshSimple(QObject *parent) : QObject(parent)
{
}

QImage ImgColorWalshSimple::startImgProcessing(QImage t_targ, QImage t_orig)
{
	qDebug() << "In ImgColorWalsh::startImgProcessing: ";

	m_imgTarget = new ImgEntity;
	m_imgTarget->SetImg(t_targ);
	m_imgTarget->TransformImgRGB2LAB();

	m_imgOriginal = new ImgEntity;
	m_imgOriginal->SetImg(t_orig);
	m_imgOriginal->TransformImgRGB2LAB();

	ScaleLuminance();

	m_imgTarget->CalcSKO();
	m_imgOriginal->CalcSKO();

	colorTarget();

	ScaleLuminanceBack();

	m_imgTarget->TransformImgLAB2RGB();

	QImage colouredImg = m_imgTarget->GetImg();

	delete m_imgOriginal;
	delete m_imgTarget;

	return colouredImg;
}

void ImgColorWalshSimple::ScaleLuminance()
{
	double targetMaxLum = m_imgTarget->MaxLum();
	double originalMaxLum = m_imgOriginal->MaxLum();
	double lumScaleFactor = targetMaxLum/originalMaxLum;
	if ( lumScaleFactor > 1 )
	{
		m_imgTarget->ScaleLum(1);
		m_imgOriginal->ScaleLum(lumScaleFactor);
	}
	else if ( lumScaleFactor < 1 )
	{
		m_imgTarget->ScaleLum(lumScaleFactor);
		m_imgOriginal->ScaleLum(1);
	}
	else if ( 1 == lumScaleFactor )
	{
		m_imgTarget->ScaleLum(1);
		m_imgOriginal->ScaleLum(1);
	}
}

void ImgColorWalshSimple::ScaleLuminanceBack()
{
	m_imgTarget->ScaleLumBack();
}

void ImgColorWalshSimple::colorTarget()
{
	qDebug() << "In ImgColorWalsh::colorTarget: ";

	int targWidth = m_imgTarget->GetImgWidth();
	int targHeight = m_imgTarget->GetImgHeight();

	int origWidth = m_imgOriginal->GetImgWidth();
	int origHeight = m_imgOriginal->GetImgHeight();

	double bestLum, bestSKO, targPixLum, targPixSKO, origLum, origSKO, diffLum, diffSKO, origA, origB;
	int x, y, wRand, hRand;

	for (int i = 0; i < targWidth; i++)
	{
		qDebug() << "row =" << i;
		for (int j = 0; j < targHeight; j++)
		{
			srand(time(NULL));

			bestLum = 1000;
			bestSKO = 1000;
			x = 0;
			y = 0;
			targPixLum = m_imgTarget->PixelLum(i, j);
			targPixSKO = m_imgTarget->PixelSKO(i, j);

			for (int k = 0; k < 400; k++)
			{
				wRand = rand()%origWidth;
				hRand = rand()%origHeight;

				origLum = m_imgOriginal->PixelLum(wRand, hRand);
				origSKO = m_imgOriginal->PixelSKO(wRand, hRand);

				diffLum = fabs(targPixLum - origLum);
				diffSKO = fabs(targPixSKO - origSKO);

				if ( ( (diffLum < bestLum) && (diffSKO < (bestSKO + SKO_TRESHOLD)) ) ||
						(diffLum < (bestLum + LUMINANCE_TRESHOLD) && diffSKO < bestSKO) )
				{
					bestLum = diffLum;
					bestSKO = diffSKO;
					x = wRand;
					y = hRand;
				}
			}

			origA = m_imgOriginal->PixelChA(x, y);
			origB = m_imgOriginal->PixelChB(x, y);

			m_imgTarget->SetPixelChA(i, j, origA);
			m_imgTarget->SetPixelChB(i, j, origB);
		}
	}
}
