/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2013, Antony Cherepanov <antony.cherepanov@gmail.com>
 *
 *	GreyToColor is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	GreyToColor is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with GreyToColor. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QDebug>
#include "./DEFINES/images.h"
#include "./DEFINES/colorization.h"

namespace Ui {
	class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
	Q_OBJECT

	// == DATA ==
private:
	Ui::PreferencesDialog *ui;

	Passport::Type m_imgPassport;
	Methods::Type m_colorizationMethod;
	LumEqualization::Type m_lumEqualType;

	// == METHODS ==
public:
	explicit PreferencesDialog(QWidget *parent = 0);
	~PreferencesDialog();

	// Init preferences
	void InitPrefs(const Passport::Type &t_passType,
				   const Methods::Type &t_methodsType,
				   const LumEqualization::Type &t_lumType);

private:
	// Set up RadioButton for Passport Type
	void SetUpPassportType();
	// Set up RadioButton for Colorization Method Type
	void SetUpColorMethodType();
	// Set up RadioButton for Luminance Equalization Type
	void SetUpLumEqualType();
	// Define checked Passport Type
	void DefinePassportType();
	// Define checked Colorization Method Type
	void DefineColorMethodType();
	// Define checked Luminance Equalization Type
	void DefineLumEqualType();

signals:
	void SignalPassportType(const Passport::Type &t_passType);
	void SignalColorMethodType(const Methods::Type &t_methodsType);
	void SignalLumEqualType(const LumEqualization::Type &t_lumType);

private slots:
	// On OK button press
	virtual void accept();
	// On Cancel button press
	virtual void reject();
};

#endif // PREFERENCESDIALOG_H
