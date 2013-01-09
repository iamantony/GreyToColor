#include "imgcolorwalshneighbor.h"

ImgColorWalshNeighbor::ImgColorWalshNeighbor(QObject *parent) : QObject(parent)
{
}

QImage ImgColorWalshNeighbor::startImgProcessing(QImage t_targ, QImage t_orig)
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

void ImgColorWalshNeighbor::ScaleLuminance()
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

void ImgColorWalshNeighbor::ScaleLuminanceBack()
{
	m_imgTarget->ScaleLumBack();
}

void ImgColorWalshNeighbor::colorTarget()
{
	qDebug() << "In ImgColorWalsh::colorTarget: ";

	int targWidth = m_imgTarget->GetImgWidth();
	int targHeight = m_imgTarget->GetImgHeight();

	int origWidth = m_imgOriginal->GetImgWidth();
	int origHeight = m_imgOriginal->GetImgHeight();

	double bestLum, bestSKO;
	double nextTargPixLum, nextTargPixSKO, targPixLum, targPixSKO, origLum, origSKO, diffLum, diffSKO;
	double origA, origB;
	int x, y, wRand, hRand, nextX, nextY;

	for (int i = 0; i < targWidth; i++)
	{
		qDebug() << "row =" << i;
		for (int j = 0; j < targHeight; j++)
		{
			if ( true == m_imgTarget->PixelHasColor(i, j) )
			{
				continue;
			}

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

				if ((diffLum < bestLum && diffSKO < (bestSKO + SKO_TRESHOLD)) ||
						(diffLum < (bestLum + LUMINANCE_TRESHOLD) && diffSKO < bestSKO))
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
			m_imgTarget->SetPixelHasColor(i, j);

			nextX = i;
			nextY = j;

			while ( (true == m_imgTarget->PixelHasColor(nextX, j)) && (nextX + 1 < targWidth) )
			{
				targPixLum = m_imgTarget->PixelLum(nextX, j);
				targPixSKO = m_imgTarget->PixelSKO(nextX, j);
				nextTargPixLum = m_imgTarget->PixelLum(nextX + 1, j);
				nextTargPixSKO = m_imgTarget->PixelSKO(nextX + 1, j);

				double neighborXDiffLum = fabs( nextTargPixLum - targPixLum );
				double neighborXDiffSKO = fabs( nextTargPixSKO - targPixSKO );
				if ((neighborXDiffLum < LUMINANCE_TRESHOLD) && (neighborXDiffSKO < SKO_TRESHOLD))
				{
					origA = m_imgOriginal->PixelChA(nextX, j);
					origB = m_imgOriginal->PixelChB(nextX, j);
					m_imgTarget->SetPixelChA(nextX + 1, j, origA);
					m_imgTarget->SetPixelChB(nextX + 1, j, origB);
					m_imgTarget->SetPixelHasColor(nextX + 1, j);

					while ( (true == m_imgTarget->PixelHasColor(nextX + 1, nextY)) && (nextY + 1 < targHeight) )
					{
						targPixLum = m_imgTarget->PixelLum(nextX + 1, nextY);
						targPixSKO = m_imgTarget->PixelSKO(nextX + 1, nextY);
						nextTargPixLum = m_imgTarget->PixelLum(nextX + 1, nextY + 1);
						nextTargPixSKO = m_imgTarget->PixelSKO(nextX + 1, nextY + 1);

						double neighborYDiffLum = fabs( nextTargPixLum - targPixLum );
						double neighborYDiffSKO = fabs(nextTargPixSKO - targPixSKO );
						if ((neighborYDiffLum < LUMINANCE_TRESHOLD) && (neighborYDiffSKO < SKO_TRESHOLD))
						{
							origA = m_imgOriginal->PixelChA(nextX + 1, nextY);
							origB = m_imgOriginal->PixelChB(nextX + 1, nextY);
							m_imgTarget->SetPixelChA(nextX + 1, nextY + 1, origA);
							m_imgTarget->SetPixelChB(nextX + 1, nextY + 1, origB);
							m_imgTarget->SetPixelHasColor(nextX + 1, nextY + 1);
						}
						nextY++;
					}
					nextY = j;
				}
				nextX++;
			}
		}
	}
}
