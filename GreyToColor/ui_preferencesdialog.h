/********************************************************************************
** Form generated from reading UI file 'preferencesdialog.ui'
**
** Created: Mon Mar 18 21:47:07 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QDialogButtonBox *exitBBox;
    QTabWidget *prefCategories;
    QWidget *tabDatabase;
    QGroupBox *gbPassType;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbLumHist;
    QRadioButton *rbSubLum;
    QRadioButton *rbLumGradHist;
    QRadioButton *rbSubLumGrad;
    QWidget *tabColorization;
    QGroupBox *gbColorMethod;
    QRadioButton *rbWSimple;
    QRadioButton *rbWNNoRand;
    QRadioButton *rbWNOneRand;
    QRadioButton *rbWNeighbor;
    QGroupBox *gbImgLumEqual;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *rbScaleMaxLum;
    QRadioButton *rbScaleAverLum;
    QRadioButton *rbNormLum;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QString::fromUtf8("PreferencesDialog"));
        PreferencesDialog->setWindowModality(Qt::ApplicationModal);
        PreferencesDialog->resize(600, 240);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PreferencesDialog->sizePolicy().hasHeightForWidth());
        PreferencesDialog->setSizePolicy(sizePolicy);
        PreferencesDialog->setMinimumSize(QSize(600, 240));
        PreferencesDialog->setMaximumSize(QSize(600, 240));
        exitBBox = new QDialogButtonBox(PreferencesDialog);
        exitBBox->setObjectName(QString::fromUtf8("exitBBox"));
        exitBBox->setGeometry(QRect(430, 210, 156, 23));
        exitBBox->setOrientation(Qt::Horizontal);
        exitBBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        prefCategories = new QTabWidget(PreferencesDialog);
        prefCategories->setObjectName(QString::fromUtf8("prefCategories"));
        prefCategories->setGeometry(QRect(10, 10, 581, 181));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(prefCategories->sizePolicy().hasHeightForWidth());
        prefCategories->setSizePolicy(sizePolicy1);
        tabDatabase = new QWidget();
        tabDatabase->setObjectName(QString::fromUtf8("tabDatabase"));
        gbPassType = new QGroupBox(tabDatabase);
        gbPassType->setObjectName(QString::fromUtf8("gbPassType"));
        gbPassType->setGeometry(QRect(10, 10, 302, 142));
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
        tabColorization = new QWidget();
        tabColorization->setObjectName(QString::fromUtf8("tabColorization"));
        gbColorMethod = new QGroupBox(tabColorization);
        gbColorMethod->setObjectName(QString::fromUtf8("gbColorMethod"));
        gbColorMethod->setGeometry(QRect(10, 10, 276, 142));
        rbWSimple = new QRadioButton(gbColorMethod);
        rbWSimple->setObjectName(QString::fromUtf8("rbWSimple"));
        rbWSimple->setGeometry(QRect(17, 25, 120, 22));
        rbWSimple->setChecked(true);
        rbWNNoRand = new QRadioButton(gbColorMethod);
        rbWNNoRand->setObjectName(QString::fromUtf8("rbWNNoRand"));
        rbWNNoRand->setGeometry(QRect(17, 81, 209, 22));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(rbWNNoRand->sizePolicy().hasHeightForWidth());
        rbWNNoRand->setSizePolicy(sizePolicy2);
        rbWNOneRand = new QRadioButton(gbColorMethod);
        rbWNOneRand->setObjectName(QString::fromUtf8("rbWNOneRand"));
        rbWNOneRand->setGeometry(QRect(17, 109, 250, 22));
        sizePolicy2.setHeightForWidth(rbWNOneRand->sizePolicy().hasHeightForWidth());
        rbWNOneRand->setSizePolicy(sizePolicy2);
        rbWNeighbor = new QRadioButton(gbColorMethod);
        rbWNeighbor->setObjectName(QString::fromUtf8("rbWNeighbor"));
        rbWNeighbor->setGeometry(QRect(17, 53, 137, 22));
        gbImgLumEqual = new QGroupBox(tabColorization);
        gbImgLumEqual->setObjectName(QString::fromUtf8("gbImgLumEqual"));
        gbImgLumEqual->setGeometry(QRect(300, 10, 251, 120));
        verticalLayout_4 = new QVBoxLayout(gbImgLumEqual);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        rbScaleMaxLum = new QRadioButton(gbImgLumEqual);
        rbScaleMaxLum->setObjectName(QString::fromUtf8("rbScaleMaxLum"));
        rbScaleMaxLum->setChecked(true);

        verticalLayout_4->addWidget(rbScaleMaxLum);

        rbScaleAverLum = new QRadioButton(gbImgLumEqual);
        rbScaleAverLum->setObjectName(QString::fromUtf8("rbScaleAverLum"));

        verticalLayout_4->addWidget(rbScaleAverLum);

        rbNormLum = new QRadioButton(gbImgLumEqual);
        rbNormLum->setObjectName(QString::fromUtf8("rbNormLum"));

        verticalLayout_4->addWidget(rbNormLum);

        prefCategories->addTab(tabColorization, QString());

        retranslateUi(PreferencesDialog);
        QObject::connect(exitBBox, SIGNAL(accepted()), PreferencesDialog, SLOT(accept()));
        QObject::connect(exitBBox, SIGNAL(rejected()), PreferencesDialog, SLOT(reject()));

        prefCategories->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Preferences", 0, QApplication::UnicodeUTF8));
        gbPassType->setTitle(QApplication::translate("PreferencesDialog", "Passport Type for Image Searching", 0, QApplication::UnicodeUTF8));
        rbLumHist->setText(QApplication::translate("PreferencesDialog", "Luminance Histogram", 0, QApplication::UnicodeUTF8));
        rbSubLum->setText(QApplication::translate("PreferencesDialog", "Subsampled Luminance", 0, QApplication::UnicodeUTF8));
        rbLumGradHist->setText(QApplication::translate("PreferencesDialog", "Luminance and Gradient Histigram", 0, QApplication::UnicodeUTF8));
        rbSubLumGrad->setText(QApplication::translate("PreferencesDialog", "Subsampled Luminance and Gradient", 0, QApplication::UnicodeUTF8));
        prefCategories->setTabText(prefCategories->indexOf(tabDatabase), QApplication::translate("PreferencesDialog", "Databse", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tabColorization->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tabColorization->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_ACCESSIBILITY
        tabColorization->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        gbColorMethod->setTitle(QApplication::translate("PreferencesDialog", "Colorization Methods", 0, QApplication::UnicodeUTF8));
        rbWSimple->setText(QApplication::translate("PreferencesDialog", "Walsh Simple", 0, QApplication::UnicodeUTF8));
        rbWNNoRand->setText(QApplication::translate("PreferencesDialog", "Walsh Neighbor (fixed net)", 0, QApplication::UnicodeUTF8));
        rbWNOneRand->setText(QApplication::translate("PreferencesDialog", "Walsh Neighbor (same pixels set)", 0, QApplication::UnicodeUTF8));
        rbWNeighbor->setText(QApplication::translate("PreferencesDialog", "Walsh Neighbor", 0, QApplication::UnicodeUTF8));
        gbImgLumEqual->setTitle(QApplication::translate("PreferencesDialog", "Images Luminance Equalization", 0, QApplication::UnicodeUTF8));
        rbScaleMaxLum->setText(QApplication::translate("PreferencesDialog", "Scale by Max Luminance", 0, QApplication::UnicodeUTF8));
        rbScaleAverLum->setText(QApplication::translate("PreferencesDialog", "Scale by Average Luminance", 0, QApplication::UnicodeUTF8));
        rbNormLum->setText(QApplication::translate("PreferencesDialog", "Normalize Luminance", 0, QApplication::UnicodeUTF8));
        prefCategories->setTabText(prefCategories->indexOf(tabColorization), QApplication::translate("PreferencesDialog", "Colorization", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H