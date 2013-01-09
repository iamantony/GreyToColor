#ifndef COMPARESTUFF_H
#define COMPARESTUFF_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <math.h>
#include <QDebug>

#define MIN_SKO 0.00001

class CompareStuff : public QObject
{
	Q_OBJECT
public:
	explicit CompareStuff(QObject *parent = 0);

	double calcImagesSKO(QImage t_orig, QImage t_coloured);
	double CalcPassportsSKO(QList<double> &t_target, QList<double> &t_source);

signals:

public slots:

};

#endif // COMPARESTUFF_H
