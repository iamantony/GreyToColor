/********************************************************************************
** Form generated from reading UI file 'histogramwindow.ui'
**
** Created: Sun 24. Mar 12:49:10 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMWINDOW_H
#define UI_HISTOGRAMWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <UI/scalelabel.h>

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
    QVBoxLayout *verticalLayout;
    QVBoxLayout *histLayout;
    ScaleLabel *labelHist;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbShowHist;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menuImage_type;
    QMenu *menuHistogram;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HistogramWindow)
    {
        if (HistogramWindow->objectName().isEmpty())
            HistogramWindow->setObjectName(QString::fromUtf8("HistogramWindow"));
        HistogramWindow->resize(400, 300);
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
        centralwidget = new QWidget(HistogramWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        histLayout = new QVBoxLayout();
        histLayout->setObjectName(QString::fromUtf8("histLayout"));
        histLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        labelHist = new ScaleLabel(centralwidget);
        labelHist->setObjectName(QString::fromUtf8("labelHist"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelHist->sizePolicy().hasHeightForWidth());
        labelHist->setSizePolicy(sizePolicy);
        labelHist->setMinimumSize(QSize(150, 100));
        labelHist->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        histLayout->addWidget(labelHist);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pbShowHist = new QPushButton(centralwidget);
        pbShowHist->setObjectName(QString::fromUtf8("pbShowHist"));

        horizontalLayout->addWidget(pbShowHist);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        histLayout->addLayout(horizontalLayout);

        histLayout->setStretch(0, 1);

        verticalLayout->addLayout(histLayout);

        HistogramWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HistogramWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 400, 21));
        menuImage_type = new QMenu(menubar);
        menuImage_type->setObjectName(QString::fromUtf8("menuImage_type"));
        menuHistogram = new QMenu(menubar);
        menuHistogram->setObjectName(QString::fromUtf8("menuHistogram"));
        HistogramWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(HistogramWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HistogramWindow->setStatusBar(statusbar);

        menubar->addAction(menuImage_type->menuAction());
        menubar->addAction(menuHistogram->menuAction());
        menuImage_type->addAction(actionTargOriginal);
        menuImage_type->addAction(actionTargColorized);
        menuImage_type->addAction(actionSource);
        menuHistogram->addAction(actionHistRGB);
        menuHistogram->addAction(actionHistLAB);

        retranslateUi(HistogramWindow);

        QMetaObject::connectSlotsByName(HistogramWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HistogramWindow)
    {
        HistogramWindow->setWindowTitle(QApplication::translate("HistogramWindow", "Histogram", 0, QApplication::UnicodeUTF8));
        actionTargOriginal->setText(QApplication::translate("HistogramWindow", "Target Original", 0, QApplication::UnicodeUTF8));
        actionTargColorized->setText(QApplication::translate("HistogramWindow", "Target Colorized", 0, QApplication::UnicodeUTF8));
        actionSource->setText(QApplication::translate("HistogramWindow", "Source", 0, QApplication::UnicodeUTF8));
        actionHistRGB->setText(QApplication::translate("HistogramWindow", "RGB", 0, QApplication::UnicodeUTF8));
        actionHistLAB->setText(QApplication::translate("HistogramWindow", "LAB", 0, QApplication::UnicodeUTF8));
        labelHist->setText(QString());
        pbShowHist->setText(QApplication::translate("HistogramWindow", "Show histogram", 0, QApplication::UnicodeUTF8));
        menuImage_type->setTitle(QApplication::translate("HistogramWindow", "Image type", 0, QApplication::UnicodeUTF8));
        menuHistogram->setTitle(QApplication::translate("HistogramWindow", "Histogram", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HistogramWindow: public Ui_HistogramWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMWINDOW_H
