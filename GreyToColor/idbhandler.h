#ifndef IDBHANDLER_H
#define IDBHANDLER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include "DATABASE/imgdatabase.h"
#include "METHODS/imgpassport.h"
#include "SERVICE/imgtransform.h"
#include "SERVICE/fileoperations.h"
#include "SERVICE/comparestuff.h"

class IDBHandler : public QObject
{
	Q_OBJECT

private:
	ImgDataBase *m_imgDB;

public:
	explicit IDBHandler(QObject *parent = 0);
	~IDBHandler();
	void AddImgsToDatabase(QStringList t_imgs);
	QString FindSameImg(QImage &t_img);
	void UpdateIDB();

private:
	QMap<QString, QList<QByteArray> > GetPassportsOfImgs(QStringList t_imgs);
	QString GetMostSimilarImgName(QByteArray t_targetPass, QMap<QString, QByteArray> t_imgsPass);

signals:

public slots:

};

#endif // IDBHANDLER_H
