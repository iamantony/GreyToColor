#ifndef IMGDATABASE_H
#define IMGDATABASE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QByteArray>
#include <QVariant>
#include <QImage>
#include <QDir>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include "../SERVICE/fileoperations.h"
#include "../defines.h"

class ImgDataBase : public QObject
{
	Q_OBJECT

private:
	QSqlDatabase IDB;

public:
	explicit ImgDataBase(QObject *parent = 0);
	~ImgDataBase();
	bool LoadIDB();
	void UpdateIDB();
	bool AddEntriesToIDB(QMap<QString, QList<QByteArray> > &t_entries);
	QMap<QString, QByteArray> GetImagesPassport(int t_passportType);

private:
	bool CreateIDB();
	QString FormIDBFullName();
	bool CheckIDBExist();
	void ReadAllEntries();

signals:

public slots:


};

#endif // IMGDATABASE_H
