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
