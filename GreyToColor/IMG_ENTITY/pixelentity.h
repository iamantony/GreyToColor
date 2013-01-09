#ifndef PIXELENTITY_H
#define PIXELENTITY_H

#include <QList>
#include <QDebug>
#include "../defines.h"
#include "../COLOR_SPACE/rgblab.h"

class PixelEntity
{
// Data
private:
	int m_Red;
	int m_Green;
	int m_Blue;
	double m_L;
	double m_A;
	double m_B;
	double m_SKO;
	double m_lumScaleFactor;
	bool m_haveColor;

	// Methods
public:
	explicit PixelEntity();

	void SetRed(const int &t_Red);
	int GetRed();

	void SetGreen(const int &t_Green);
	int GetGreen();

	void SetBlue(const int &t_Blue);
	int GetBlue();

	void SetRGB(const int &t_Red, const int &t_Green, const int &t_Blue);

	void SetL(const double &t_L);
	double GetL();

	void SetA(const double &t_A);
	double GetA();

	void SetB(const double &t_B);
	double GetB();

	bool TransToLAB();
	bool TransToRGB();

	void SetSKO(const double &t_SKO);
	double GetSKO();

	void ScaleLum(const double &t_scaleFactor);
	double GetLumScaleFactor();
	void ScaleLumBack();

	void SetPixHasColor();
	void SetPixHasNoColor();
	bool IsPixHasColor();

signals:

public slots:

};

#endif // PIXELENTITY_H
