#include "imghandler_old.h"

ImgHandlerOld::ImgHandlerOld(QObject *parent) :
	QObject(parent)
{
}

void ImgHandlerOld::setImg(QImage t_img, int t_type)
{
	if (t_type < TARGET || t_type > ORIGINAL)
		return;

	m_imgMass[t_type] = t_img;
}

QImage ImgHandlerOld::getImg(int t_type)
{
	return m_imgMass[t_type];
}

void ImgHandlerOld::getLumImg(QImage *t_img)
{
	if (t_img == NULL)
		return;

	ImgTransform transformImg;
	transformImg.TransColorImgToGrayImg(t_img);
}

// Colorize our gray image and compare original coloured TARGET image with a RESULT
QImage ImgHandlerOld::startImgColorizationWSimple()
{
	ImgColorWalshSimple *iCWSimple = new ImgColorWalshSimple();
	m_imgMass[RESULT] = iCWSimple->startImgProcessing(m_imgMass[RESULT], m_imgMass[ORIGINAL]);

	imageComparison(m_imgMass[TARGET], m_imgMass[RESULT]);

	delete iCWSimple;

	return m_imgMass[RESULT];
}

// Colorize our gray image and compare original coloured TARGET image with a RESULT
QImage ImgHandlerOld::startImgColorizationWNeighbor()
{
	ImgColorWalshNeighbor *iCWNeighbor = new ImgColorWalshNeighbor();
	m_imgMass[RESULT] = iCWNeighbor->startImgProcessing(m_imgMass[RESULT], m_imgMass[ORIGINAL]);
	delete iCWNeighbor;
	imageComparison(m_imgMass[TARGET], m_imgMass[RESULT]);
	return m_imgMass[RESULT];
}

void ImgHandlerOld::imageComparison(QImage &t_targ, QImage &t_coloured)
{
	CompareStuff compare;
	double result = compare.calcImagesSKO(t_targ, t_coloured);

	// result will be less than 0 if calculations didn't go well
	if (result < 0)
		return;

	QString imgSKO = QString::number(result);

	emit signalImagesSKO(imgSKO);
}

void ImgHandlerOld::getGrayImg(QString t_imgPath)
{
	QImage *img = new QImage(t_imgPath);

	bool imgIsGrayscale = img->isGrayscale();
	if (imgIsGrayscale)
	{
		setImg(*img, TARGET);
		setImg(*img, RESULT);

		setImg2Label(img, TARGET);
		setImg2Label(img, RESULT);

		emit signalEnableProcButtn(TARGET);
	}
	else
	{
		setImg(*img, TARGET);
		setImg2Label(img, TARGET);

		getLumImg(img);
		setImg(*img, RESULT);
		setImg2Label(img, RESULT);

		emit signalEnableProcButtn (TARGET);
	}
}

//
void ImgHandlerOld::getColorImg(QString t_imgPath)
{
	QImage *img = new QImage(t_imgPath);

	bool imgIsGrayscale = img->isGrayscale();
	if (imgIsGrayscale)
	{
		QMessageBox mbox;
		mbox.setWindowTitle("Error");
		mbox.setText("Please, choose color image!");
		mbox.exec();
		return;
	}

	setImg(*img, ORIGINAL);
	setImg2Label(img, ORIGINAL);

	emit signalEnableProcButtn (ORIGINAL);
}

void ImgHandlerOld::setImg2Label(QImage *t_img, int t_type)
{
	QImage imgScaled = t_img->scaled(W_IMG, H_IMG, Qt::KeepAspectRatio);

	switch(t_type)
	{
		case TARGET:
			emit signalSetTargetImg(imgScaled);
			break;

		case RESULT:
			emit signalSetResultImg(imgScaled);
			break;

		case ORIGINAL:
			emit signalSetOriginalImg(imgScaled);
			break;

		default:
			qDebug() << "In ImgHandlerOld::setImg2Label(): unknown image type.";
	}
}
