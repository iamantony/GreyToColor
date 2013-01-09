#ifndef RGBLAB_H
#define RGBLAB_H

#include <QDebug>
#include <math.h>
#include "../defines.h"

class RGBLAB : public QObject
{
// METHODS
public:
	explicit RGBLAB();

	QList<double> RGB2LAB(const int &t_Red, const int &t_Green, const int &t_Blue);
	QList<int> LAB2RGB(const double &t_LL, const double &t_AA, const double &t_BB);
};

#endif // RGBLAB_H
