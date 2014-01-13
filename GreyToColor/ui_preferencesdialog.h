/********************************************************************************
** Form generated from reading UI file 'preferencesdialog.ui'
**
** Created: Thu Jun 6 10:37:59 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QHeaderView>
#include <QRadioButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *prefCategories;
    QWidget *tabColorization;
    QGroupBox *gbColorMethod;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbWSimple;
    QRadioButton *rbWSLookUp;
    QRadioButton *rbWSEntropy;
    QRadioButton *rbWNeighbor;
    QRadioButton *rbWNNoRand;
    QRadioButton *rbWNOneRand;
    QGroupBox *gbImgLumEqual;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *rbNoScale;
    QRadioButton *rbScaleMaxLum;
    QRadioButton *rbScaleAverLum;
    QRadioButton *rbNormLumBorder;
    QRadioButton *rbNormLumCentral;
    QWidget *tabDatabase;
    QGroupBox *gbPassType;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbLumHist;
    QRadioButton *rbSubLum;
    QRadioButton *rbLumGradHist;
    QRadioButton *rbSubLumGrad;
    QDialogButtonBox *exitBBox;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QString::fromUtf8("PreferencesDialog"));
        PreferencesDialog->setWindowModality(Qt::ApplicationModal);
        PreferencesDialog->resize(650, 280);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesDialog->sizePolicy().hasHeightForWidth());
        PreferencesDialog->setSizePolicy(sizePolicy);
        PreferencesDialog->setMinimumSize(QSize(650, 280));
        PreferencesDialog->setMaximumSize(QSize(650, 280));
        verticalLayout_3 = new QVBoxLayout(PreferencesDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        prefCategories = new QTabWidget(PreferencesDialog);
        prefCategories->setObjectName(QString::fromUtf8("prefCategories"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(prefCategories->sizePolicy().hasHeightForWidth());
        prefCategories->setSizePolicy(sizePolicy1);
        tabColorization = new QWidget();
        tabColorization->setObjectName(QString::fromUtf8("tabColorization"));
        gbColorMethod = new QGroupBox(tabColorization);
        gbColorMethod->setObjectName(QString::fromUtf8("gbColorMethod"));
        gbColorMethod->setGeometry(QRect(10, 10, 271, 181));
        verticalLayout_2 = new QVBoxLayout(gbColorMethod);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rbWSimple = new QRadioButton(gbColorMethod);
        rbWSimple->setObjectName(QString::fromUtf8("rbWSimple"));
        rbWSimple->setChecked(true);

        verticalLayout_2->addWidget(rbWSimple);

        rbWSLookUp = new QRadioButton(gbColorMethod);
        rbWSLookUp->setObjectName(QString::fromUtf8("rbWSLookUp"));

        verticalLayout_2->addWidget(rbWSLookUp);

        rbWSEntropy = new QRadioButton(gbColorMethod);
        rbWSEntropy->setObjectName(QString::fromUtf8("rbWSEntropy"));

        verticalLayout_2->addWidget(rbWSEntropy);

        rbWNeighbor = new QRadioButton(gbColorMethod);
        rbWNeighbor->setObjectName(QString::fromUtf8("rbWNeighbor"));

        verticalLayout_2->addWidget(rbWNeighbor);

        rbWNNoRand = new QRadioButton(gbColorMethod);
        rbWNNoRand->setObjectName(QString::fromUtf8("rbWNNoRand"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(rbWNNoRand->sizePolicy().hasHeightForWidth());
        rbWNNoRand->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(rbWNNoRand);

        rbWNOneRand = new QRadioButton(gbColorMethod);
        rbWNOneRand->setObjectName(QString::fromUtf8("rbWNOneRand"));
        sizePolicy2.setHeightForWidth(rbWNOneRand->sizePolicy().hasHeightForWidth());
        rbWNOneRand->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(rbWNOneRand);

        gbImgLumEqual = new QGroupBox(tabColorization);
        gbImgLumEqual->setObjectName(QString::fromUtf8("gbImgLumEqual"));
        gbImgLumEqual->setGeometry(QRect(290, 10, 301, 181));
        verticalLayout_4 = new QVBoxLayout(gbImgLumEqual);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        rbNoScale = new QRadioButton(gbImgLumEqual);
        rbNoScale->setObjectName(QString::fromUtf8("rbNoScale"));
        rbNoScale->setChecked(true);

        verticalLayout_4->addWidget(rbNoScale);

        rbScaleMaxLum = new QRadioButton(gbImgLumEqual);
        rbScaleMaxLum->setObjectName(QString::fromUtf8("rbScaleMaxLum"));
        rbScaleMaxLum->setChecked(false);

        verticalLayout_4->addWidget(rbScaleMaxLum);

        rbScaleAverLum = new QRadioButton(gbImgLumEqual);
        rbScaleAverLum->setObjectName(QString::fromUtf8("rbScaleAverLum"));

        verticalLayout_4->addWidget(rbScaleAverLum);

        rbNormLumBorder = new QRadioButton(gbImgLumEqual);
        rbNormLumBorder->setObjectName(QString::fromUtf8("rbNormLumBorder"));

        verticalLayout_4->addWidget(rbNormLumBorder);

        rbNormLumCentral = new QRadioButton(gbImgLumEqual);
        rbNormLumCentral->setObjectName(QString::fromUtf8("rbNormLumCentral"));

        verticalLayout_4->addWidget(rbNormLumCentral);

        prefCategories->addTab(tabColorization, QString());
        tabDatabase = new QWidget();
        tabDatabase->setObjectName(QString::fromUtf8("tabDatabase"));
        gbPassType = new QGroupBox(tabDatabase);
        gbPassType->setObjectName(QString::fromUtf8("gbPassType"));
        gbPassType->setGeometry(QRect(10, 10, 302, 151));
        gbPassType->setCheckable(false);
        verticalLayout = new QVBoxLayout(gbPassType);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbLumHist = new QRadioButton(gbPassType);
        rbLumHist->setObjectName(QString::fromUtf8("rbLumHist"));
        rbLumHist->setChecked(true);

        verticalLayout->addWidget(rbLumHist);

        rbSubLum = new QRadioButton(gbPassType);
        rbSubLum->setObjectName(QString::fromUtf8("rbSubLum"));

        verticalLayout->addWidget(rbSubLum);

        rbLumGradHist = new QRadioButton(gbPassType);
        rbLumGradHist->setObjectName(QString::fromUtf8("rbLumGradHist"));

        verticalLayout->addWidget(rbLumGradHist);

        rbSubLumGrad = new QRadioButton(gbPassType);
        rbSubLumGrad->setObjectName(QString::fromUtf8("rbSubLumGrad"));

        verticalLayout->addWidget(rbSubLumGrad);

        prefCategories->addTab(tabDatabase, QString());

        verticalLayout_3->addWidget(prefCategories);

        exitBBox = new QDialogButtonBox(PreferencesDialog);
        exitBBox->setObjectName(QString::fromUtf8("exitBBox"));
        exitBBox->setOrientation(Qt::Horizontal);
        exitBBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(exitBBox);


        retranslateUi(PreferencesDialog);
        QObject::connect(exitBBox, SIGNAL(accepted()), PreferencesDialog, SLOT(accept()));
        QObject::connect(exitBBox, SIGNAL(rejected()), PreferencesDialog, SLOT(reject()));

        prefCategories->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
		PreferencesDialog->setWindowTitle("Preferences");
#ifndef QT_NO_TOOLTIP
        tabColorization->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tabColorization->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_ACCESSIBILITY
        tabColorization->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
		gbColorMethod->setTitle("Colorization Methods");
		rbWSimple->setText("Walsh Simple");
		rbWSLookUp->setText("Walsh Simple (look up table)");
		rbWSEntropy->setText("Walsh Simple (all parameters)");
		rbWNeighbor->setText("Walsh Neighbor");
		rbWNNoRand->setText("Walsh Neighbor (fixed net)");
		rbWNOneRand->setText("Walsh Neighbor (same pixels set)");
		gbImgLumEqual->setTitle("Images Luminance Equalization");
		rbNoScale->setText("No Scale");
		rbScaleMaxLum->setText("Scale by Max Luminance");
		rbScaleAverLum->setText("Scale by Average Luminance");
		rbNormLumBorder->setText("Normalize Luminance (by borders)");
		rbNormLumCentral->setText("Normalize Luminance (by center)");
		prefCategories->setTabText(prefCategories->indexOf(tabColorization), "Colorization");
		gbPassType->setTitle("Passport Type for Image Searching");
		rbLumHist->setText("Luminance Histogram");
		rbSubLum->setText("Subsampled Luminance");
		rbLumGradHist->setText("Luminance and Gradient Histigram");
		rbSubLumGrad->setText("Subsampled Luminance and Gradient");
		prefCategories->setTabText(prefCategories->indexOf(tabDatabase), "Databse");
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H
