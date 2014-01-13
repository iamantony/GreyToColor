/********************************************************************************
** Form generated from reading UI file 'histogramwindow.ui'
**
** Created: Thu Jun 6 10:37:59 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMWINDOW_H
#define UI_HISTOGRAMWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QSpacerItem>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistogramWindow
{
public:
    QAction *actionTargOriginal;
    QAction *actionTargColorized;
    QAction *actionSource;
    QAction *actionHistRGB;
    QAction *actionHistLAB;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *gbImageType;
    QVBoxLayout *verticalLayout;
    QRadioButton *rbTargOrig;
    QRadioButton *rbTargColor;
    QRadioButton *rbSource;
    QGroupBox *gbColorSpaceType;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbRGBGrey;
    QRadioButton *rbRGB;
    QRadioButton *rbLAB;
    QGroupBox *gbTargLum;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *rbNoScale;
    QRadioButton *rbScaleMax;
    QRadioButton *rbScaleAver;
    QRadioButton *rbNormBorder;
    QRadioButton *rbNormCenter;
    QHBoxLayout *rbLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbFormHist;
    QSpacerItem *horizontalSpacer_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HistogramWindow)
    {
        if (HistogramWindow->objectName().isEmpty())
            HistogramWindow->setObjectName(QString::fromUtf8("HistogramWindow"));
        HistogramWindow->setWindowModality(Qt::ApplicationModal);
        HistogramWindow->resize(411, 457);
        HistogramWindow->setSizeIncrement(QSize(1, 1));
        HistogramWindow->setBaseSize(QSize(400, 300));
        actionTargOriginal = new QAction(HistogramWindow);
        actionTargOriginal->setObjectName(QString::fromUtf8("actionTargOriginal"));
        actionTargOriginal->setCheckable(true);
        actionTargColorized = new QAction(HistogramWindow);
        actionTargColorized->setObjectName(QString::fromUtf8("actionTargColorized"));
        actionTargColorized->setCheckable(true);
        actionSource = new QAction(HistogramWindow);
        actionSource->setObjectName(QString::fromUtf8("actionSource"));
        actionSource->setCheckable(true);
        actionHistRGB = new QAction(HistogramWindow);
        actionHistRGB->setObjectName(QString::fromUtf8("actionHistRGB"));
        actionHistRGB->setCheckable(true);
        actionHistLAB = new QAction(HistogramWindow);
        actionHistLAB->setObjectName(QString::fromUtf8("actionHistLAB"));
        actionHistLAB->setCheckable(true);
        actionHistLAB->setEnabled(false);
        centralwidget = new QWidget(HistogramWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gbImageType = new QGroupBox(centralwidget);
        gbImageType->setObjectName(QString::fromUtf8("gbImageType"));
        verticalLayout = new QVBoxLayout(gbImageType);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rbTargOrig = new QRadioButton(gbImageType);
        rbTargOrig->setObjectName(QString::fromUtf8("rbTargOrig"));
        rbTargOrig->setChecked(true);

        verticalLayout->addWidget(rbTargOrig);

        rbTargColor = new QRadioButton(gbImageType);
        rbTargColor->setObjectName(QString::fromUtf8("rbTargColor"));

        verticalLayout->addWidget(rbTargColor);

        rbSource = new QRadioButton(gbImageType);
        rbSource->setObjectName(QString::fromUtf8("rbSource"));

        verticalLayout->addWidget(rbSource);


        verticalLayout_3->addWidget(gbImageType);

        gbColorSpaceType = new QGroupBox(centralwidget);
        gbColorSpaceType->setObjectName(QString::fromUtf8("gbColorSpaceType"));
        gbColorSpaceType->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(gbColorSpaceType);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rbRGBGrey = new QRadioButton(gbColorSpaceType);
        rbRGBGrey->setObjectName(QString::fromUtf8("rbRGBGrey"));
        rbRGBGrey->setChecked(true);

        verticalLayout_2->addWidget(rbRGBGrey);

        rbRGB = new QRadioButton(gbColorSpaceType);
        rbRGB->setObjectName(QString::fromUtf8("rbRGB"));
        rbRGB->setChecked(false);

        verticalLayout_2->addWidget(rbRGB);

        rbLAB = new QRadioButton(gbColorSpaceType);
        rbLAB->setObjectName(QString::fromUtf8("rbLAB"));

        verticalLayout_2->addWidget(rbLAB);

        gbTargLum = new QGroupBox(gbColorSpaceType);
        gbTargLum->setObjectName(QString::fromUtf8("gbTargLum"));
        gbTargLum->setEnabled(false);
        verticalLayout_4 = new QVBoxLayout(gbTargLum);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        rbNoScale = new QRadioButton(gbTargLum);
        rbNoScale->setObjectName(QString::fromUtf8("rbNoScale"));
        rbNoScale->setChecked(true);

        verticalLayout_4->addWidget(rbNoScale);

        rbScaleMax = new QRadioButton(gbTargLum);
        rbScaleMax->setObjectName(QString::fromUtf8("rbScaleMax"));
        rbScaleMax->setChecked(false);

        verticalLayout_4->addWidget(rbScaleMax);

        rbScaleAver = new QRadioButton(gbTargLum);
        rbScaleAver->setObjectName(QString::fromUtf8("rbScaleAver"));

        verticalLayout_4->addWidget(rbScaleAver);

        rbNormBorder = new QRadioButton(gbTargLum);
        rbNormBorder->setObjectName(QString::fromUtf8("rbNormBorder"));

        verticalLayout_4->addWidget(rbNormBorder);

        rbNormCenter = new QRadioButton(gbTargLum);
        rbNormCenter->setObjectName(QString::fromUtf8("rbNormCenter"));

        verticalLayout_4->addWidget(rbNormCenter);


        verticalLayout_2->addWidget(gbTargLum);


        verticalLayout_3->addWidget(gbColorSpaceType);

        rbLayout = new QHBoxLayout();
        rbLayout->setObjectName(QString::fromUtf8("rbLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        rbLayout->addItem(horizontalSpacer);

        pbFormHist = new QPushButton(centralwidget);
        pbFormHist->setObjectName(QString::fromUtf8("pbFormHist"));

        rbLayout->addWidget(pbFormHist);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        rbLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(rbLayout);

        HistogramWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(HistogramWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HistogramWindow->setStatusBar(statusbar);

        retranslateUi(HistogramWindow);

        QMetaObject::connectSlotsByName(HistogramWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HistogramWindow)
    {
		HistogramWindow->setWindowTitle("Histogram");
		actionTargOriginal->setText("Target Original");
		actionTargColorized->setText("Target Colorized");
		actionSource->setText("Source");
		actionHistRGB->setText("RGB");
		actionHistLAB->setText("LAB");
		gbImageType->setTitle("Image type");
		rbTargOrig->setText("Target Oiginal");
		rbTargColor->setText("Target Colorized");
		rbSource->setText("Source");
		gbColorSpaceType->setTitle("Color space");
		rbRGBGrey->setText("RGB Grey");
		rbRGB->setText("RGB");
		rbLAB->setText("LAB Luminance");
		gbTargLum->setTitle("Target LAB Luminance");
		rbNoScale->setText("No scale");
		rbScaleMax->setText("Scale by Source Image Max Luminance");
		rbScaleAver->setText("Scale by Source Image Average Luminance");
		rbNormBorder->setText("Normalise by Source Image Luminance borders");
		rbNormCenter->setText("Normalise by Source Image Central Luminance");
		pbFormHist->setText("Form histogram");
    } // retranslateUi

};

namespace Ui {
    class HistogramWindow: public Ui_HistogramWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMWINDOW_H
