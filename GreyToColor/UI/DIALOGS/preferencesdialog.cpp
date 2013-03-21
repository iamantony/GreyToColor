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

#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PreferencesDialog)
{
	ui->setupUi(this);

	m_imgPassport = Passport::LUM_HISTOGRAM;
	m_colorizationMethod = Methods::WALSH_SIMPLE;
	m_lumEqualType = LumEqualization::SCALE_BY_MAX;
}

PreferencesDialog::~PreferencesDialog()
{
	delete ui;
}

// Init preferences
// @input:
// - Passport::Type - exist passport type
// - Methods::Type - exist colorization method type
// - LumEqualization::Type - exist luminance equalization type
// @output:
void PreferencesDialog::InitPrefs(const Passport::Type &t_passType,
								  const Methods::Type &t_methodsType,
								  const LumEqualization::Type &t_lumType)
{
	if ( (Passport::DEFAULT_LAST == t_passType) ||
		 (Methods::DEFAULT_LAST == t_methodsType) ||
		 (LumEqualization::DEFAULT_LAST == t_lumType) )
	{
		qDebug() << "InitPrefs(): Error - invalid arguments";
		return;
	}

	m_imgPassport = t_passType;
	m_colorizationMethod = t_methodsType;
	m_lumEqualType = t_lumType;

	SetUpPassportType();
	SetUpColorMethodType();
	SetUpLumEqualType();
}

// Set up RadioButton for Passport Type
// @input:
// @output:
void PreferencesDialog::SetUpPassportType()
{
	switch(m_imgPassport)
	{
		case Passport::LUM_HISTOGRAM:
			ui->rbLumHist->setChecked(true);
			break;

		case Passport::LUM_SUBSAMPLE:
			ui->rbSubLum->setChecked(true);
			break;

		case Passport::LUM_AND_GRAD_HIST:
			ui->rbLumGradHist->setChecked(true);
			break;

		case Passport::LUM_AND_GRAD_SUB:
			ui->rbSubLumGrad->setChecked(true);
			break;

		case Passport::DEFAULT_LAST:
		default:
		{
			qDebug() << "SetUpPassportType(): Error - invalid image passport type";
			return;
		}
	}
}

// Set up RadioButton for Colorization Method Type
// @input:
// @output:
void PreferencesDialog::SetUpColorMethodType()
{
	switch(m_colorizationMethod)
	{
		case Methods::WALSH_SIMPLE:
			ui->rbWSimple->setChecked(true);
			break;

		case Methods::WALSH_NEIGHBOR:
			ui->rbWNeighbor->setChecked(true);
			break;

		case Methods::WALSH_NEIGHBOR_NORAND:
			ui->rbWNNoRand->setChecked(true);
			break;

		case Methods::WALSH_NEIGHBOR_ONERAND:
			ui->rbWNOneRand->setChecked(true);
			break;

		case Methods::DEFAULT_LAST:
		default:
		{
			qDebug() << "SetUpColorMethodType(): Error - invalid colorization method type";
			return;
		}
	}
}

// Set up RadioButton for Luminance Equalization Type
// @input:
// @output:
void PreferencesDialog::SetUpLumEqualType()
{
	switch(m_lumEqualType)
	{
		case LumEqualization::SCALE_BY_MAX:
			ui->rbScaleMaxLum->setChecked(true);
			break;

		case LumEqualization::SCALE_BY_AVERAGE:
			ui->rbScaleAverLum->setChecked(true);
			break;

		case LumEqualization::NORMALIZE_LUM_BORDER:
			ui->rbNormLumBorder->setChecked(true);
			break;

		case LumEqualization::NORMALIZE_LUM_CENTER:
			ui->rbNormLumCentral->setChecked(true);
			break;

		case LumEqualization::DEFAULT_LAST:
		default:
		{
			qDebug() << "SetUpLumEqualType(): Error - invalid luminance equalization type";
			return;
		}
	}
}

// Define checked Image Passport Type
// @input:
// @output:
void PreferencesDialog::DefinePassportType()
{
	if ( true == ui->rbLumHist->isChecked() )
	{
		m_imgPassport = Passport::LUM_HISTOGRAM;
	}
	else if ( true == ui->rbSubLum->isChecked() )
	{
		m_imgPassport = Passport::LUM_SUBSAMPLE;
	}
	else if ( true == ui->rbLumGradHist->isChecked() )
	{
		m_imgPassport = Passport::LUM_AND_GRAD_HIST;
	}
	else if ( true == ui->rbSubLumGrad->isChecked() )
	{
		m_imgPassport = Passport::LUM_AND_GRAD_SUB;
	}
}

// Define checked Colorization Method Type
// @input:
// @output:
void PreferencesDialog::DefineColorMethodType()
{
	if ( true == ui->rbWSimple->isChecked() )
	{
		m_colorizationMethod = Methods::WALSH_SIMPLE;
	}
	else if ( true == ui->rbWNeighbor->isChecked() )
	{
		m_colorizationMethod = Methods::WALSH_NEIGHBOR;
	}
	else if ( true == ui->rbWNNoRand->isChecked() )
	{
		m_colorizationMethod = Methods::WALSH_NEIGHBOR_NORAND;
	}
	else if ( true == ui->rbWNOneRand->isChecked() )
	{
		m_colorizationMethod = Methods::WALSH_NEIGHBOR_ONERAND;
	}
}

// Define checked Luminance Equalization Type
// @input:
// @output:
void PreferencesDialog::DefineLumEqualType()
{
	if ( true == ui->rbScaleMaxLum->isChecked() )
	{
		m_lumEqualType = LumEqualization::SCALE_BY_MAX;
	}
	else if ( true == ui->rbScaleAverLum->isChecked() )
	{
		m_lumEqualType = LumEqualization::SCALE_BY_AVERAGE;
	}
	else if ( true == ui->rbNormLumBorder->isChecked() )
	{
		m_lumEqualType = LumEqualization::NORMALIZE_LUM_BORDER;
	}
	else if ( true == ui->rbNormLumCentral->isChecked() )
	{
		m_lumEqualType = LumEqualization::NORMALIZE_LUM_CENTER;
	}
}

// On OK button press
// @input:
// @output:
void PreferencesDialog::accept()
{
	DefinePassportType();
	DefineColorMethodType();
	DefineLumEqualType();

	emit SignalPassportType(m_imgPassport);
	emit SignalColorMethodType(m_colorizationMethod);
	emit SignalLumEqualType(m_lumEqualType);

	this->done(QDialog::Accepted);
}

// On Cancel button press
// @input:
// @output:
void PreferencesDialog::reject()
{
	this->done(QDialog::Rejected);
}
