#include "idbhandler.h"

IDBHandler::IDBHandler(QObject *parent) :
	QObject(parent)
{
	m_imgDB = new ImgDataBase();
}

IDBHandler::~IDBHandler()
{
	delete m_imgDB;
}

// Add all images, that choosed user, to database
void IDBHandler::AddImgsToDatabase(QStringList t_imgs)
{
	// Firstly we should copy images to a project path. Or do nothing if they already in it.
	FileOperations imgFile;
	imgFile.MoveImagesToProject(t_imgs);

	// Then for each copied image we creating passports
	ImgPassport imgPass;
	// This map will contain image path and its' passports
	QMap<QString, QList<QByteArray> > imgsPassports;
	for (int img = 0; img < t_imgs.size(); img++)
	{
		qDebug() << t_imgs.at(img);
		QImage *image = new QImage(t_imgs.at(img));

		// Gets all kind of passports for this image
		QList<QByteArray> passports = imgPass.GetImgPassports(image);

		// Before saving images we need to cut path part in their name
		QString imgName = imgFile.CutImagePathToImageName(t_imgs.at(img));

		imgsPassports.insert(imgName, passports);

		delete image;
	}

	qDebug() << "Adding images to database...";
	m_imgDB->AddEntriesToIDB(imgsPassports);
}

QString IDBHandler::FindSameImg(QImage &t_img)
{
	QString pathToColorImg;

	if ( true == t_img.isNull() )
	{
		qDebug() << "FindSameImg(): Error - invalid arguments";
		return pathToColorImg;
	}

	ImgPassport imgPass;
	QList<QByteArray> passports = imgPass.GetImgPassports(&t_img);

	QMap<QString, QByteArray> imgsPassport;
	imgsPassport = m_imgDB->GetImagesPassport(0);

	pathToColorImg = GetMostSimilarImgName(passports.at(0), imgsPassport);

	pathToColorImg.prepend(PROJECT_IMG_PATH);
	pathToColorImg.prepend(".");
	return pathToColorImg;
}

QString IDBHandler::GetMostSimilarImgName(QByteArray t_targetPass, QMap<QString, QByteArray> t_imgsPass)
{
	QString similarImgName;
	double minSKO = 1000000;

	QByteArray sourcePass;
	double calculatedSKO;

	ImgPassport getInfoFromPassport;
	CompareStuff compareSKO;

	QList<double> targetPassport;
	QList<double> sourcePassport;
	targetPassport = getInfoFromPassport.ConvertFromByteArrayToDoubleList(t_targetPass);

	QMap<QString, QByteArray>::iterator iter = t_imgsPass.begin();
	while( iter != t_imgsPass.end() )
	{
		sourcePass = iter.value();
		sourcePassport.clear();
		sourcePassport = getInfoFromPassport.ConvertFromByteArrayToDoubleList(sourcePass);

		calculatedSKO = 1000000;
		calculatedSKO = compareSKO.CalcPassportsSKO(targetPassport, sourcePassport);
		if ( calculatedSKO < minSKO )
		{
			minSKO = calculatedSKO;
			similarImgName = iter.key();
		}

		++iter;
	}

	return similarImgName;
}

void IDBHandler::UpdateIDB()
{

}
