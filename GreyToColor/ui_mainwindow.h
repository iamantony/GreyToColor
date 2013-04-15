/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 15. Apr 18:17:58 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <UI/scalelabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenTargetImage;
    QAction *actionClose;
    QAction *actionOpenSourceImage;
    QAction *actionSaveResult;
    QAction *actionCreateDatabase;
    QAction *actionAddImages;
    QAction *actionOpenDatabase;
    QAction *actionPreferences;
    QAction *actionLumHist;
    QAction *actionSubsampLum;
    QAction *actionLumGradHists;
    QAction *actionSubsampLumGrad;
    QAction *actionWalshSimple;
    QAction *actionWalshNeighbor;
    QAction *actionWNNoRand;
    QAction *actionWNOneRand;
    QAction *actionFormHist;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *imgsLayout;
    QVBoxLayout *targetImgLayout;
    ScaleLabel *targetImgLbl;
    QHBoxLayout *targetButtonsLayout;
    QSpacerItem *leftHS_3;
    QPushButton *openTargetImgPB;
    QSpacerItem *rightHS_3;
    QSpacerItem *targetResultImgsHS;
    QVBoxLayout *resultImgLayout;
    ScaleLabel *resultImgLbl;
    QHBoxLayout *resultButtonsLayout;
    QSpacerItem *leftHS_2;
    QPushButton *startColorizationPB;
    QSpacerItem *horizontalSpacer;
    QPushButton *resetPB;
    QSpacerItem *rightHS_2;
    QSpacerItem *resultSourceImgsHS;
    QVBoxLayout *sourceImgLayout;
    ScaleLabel *sourceImgLbl;
    QHBoxLayout *sourceButtonsLayout;
    QSpacerItem *leftHS;
    QPushButton *openSourceImgPB;
    QSpacerItem *middleHS;
    QPushButton *findSourceImgPB;
    QSpacerItem *rightHS;
    QHBoxLayout *skoLayout;
    QSpacerItem *leftSKOHS;
    QLabel *skoLbl;
    QLineEdit *lineSKO;
    QSpacerItem *rightSKOHS;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuDatabase;
    QMenu *menuColorization;
    QMenu *menuHistogram;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 507);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setSizeIncrement(QSize(1, 1));
        MainWindow->setBaseSize(QSize(800, 600));
        actionOpenTargetImage = new QAction(MainWindow);
        actionOpenTargetImage->setObjectName(QString::fromUtf8("actionOpenTargetImage"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionOpenSourceImage = new QAction(MainWindow);
        actionOpenSourceImage->setObjectName(QString::fromUtf8("actionOpenSourceImage"));
        actionSaveResult = new QAction(MainWindow);
        actionSaveResult->setObjectName(QString::fromUtf8("actionSaveResult"));
        actionCreateDatabase = new QAction(MainWindow);
        actionCreateDatabase->setObjectName(QString::fromUtf8("actionCreateDatabase"));
        actionAddImages = new QAction(MainWindow);
        actionAddImages->setObjectName(QString::fromUtf8("actionAddImages"));
        actionOpenDatabase = new QAction(MainWindow);
        actionOpenDatabase->setObjectName(QString::fromUtf8("actionOpenDatabase"));
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        actionPreferences->setEnabled(true);
        actionLumHist = new QAction(MainWindow);
        actionLumHist->setObjectName(QString::fromUtf8("actionLumHist"));
        actionLumHist->setCheckable(true);
        actionLumHist->setChecked(false);
        actionSubsampLum = new QAction(MainWindow);
        actionSubsampLum->setObjectName(QString::fromUtf8("actionSubsampLum"));
        actionSubsampLum->setCheckable(true);
        actionLumGradHists = new QAction(MainWindow);
        actionLumGradHists->setObjectName(QString::fromUtf8("actionLumGradHists"));
        actionLumGradHists->setCheckable(true);
        actionSubsampLumGrad = new QAction(MainWindow);
        actionSubsampLumGrad->setObjectName(QString::fromUtf8("actionSubsampLumGrad"));
        actionSubsampLumGrad->setCheckable(true);
        actionWalshSimple = new QAction(MainWindow);
        actionWalshSimple->setObjectName(QString::fromUtf8("actionWalshSimple"));
        actionWalshSimple->setCheckable(true);
        actionWalshNeighbor = new QAction(MainWindow);
        actionWalshNeighbor->setObjectName(QString::fromUtf8("actionWalshNeighbor"));
        actionWalshNeighbor->setCheckable(true);
        actionWNNoRand = new QAction(MainWindow);
        actionWNNoRand->setObjectName(QString::fromUtf8("actionWNNoRand"));
        actionWNNoRand->setCheckable(true);
        actionWNOneRand = new QAction(MainWindow);
        actionWNOneRand->setObjectName(QString::fromUtf8("actionWNOneRand"));
        actionWNOneRand->setCheckable(true);
        actionFormHist = new QAction(MainWindow);
        actionFormHist->setObjectName(QString::fromUtf8("actionFormHist"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        imgsLayout = new QHBoxLayout();
        imgsLayout->setObjectName(QString::fromUtf8("imgsLayout"));
        imgsLayout->setSizeConstraint(QLayout::SetMaximumSize);
        targetImgLayout = new QVBoxLayout();
        targetImgLayout->setObjectName(QString::fromUtf8("targetImgLayout"));
        targetImgLbl = new ScaleLabel(centralwidget);
        targetImgLbl->setObjectName(QString::fromUtf8("targetImgLbl"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(targetImgLbl->sizePolicy().hasHeightForWidth());
        targetImgLbl->setSizePolicy(sizePolicy1);
        targetImgLbl->setMinimumSize(QSize(200, 200));
        targetImgLbl->setMaximumSize(QSize(660, 660));
        targetImgLbl->setFrameShape(QFrame::NoFrame);
        targetImgLbl->setScaledContents(false);
        targetImgLbl->setAlignment(Qt::AlignCenter);
        targetImgLbl->setWordWrap(true);
        targetImgLbl->setIndent(-1);

        targetImgLayout->addWidget(targetImgLbl);

        targetButtonsLayout = new QHBoxLayout();
        targetButtonsLayout->setSpacing(6);
        targetButtonsLayout->setObjectName(QString::fromUtf8("targetButtonsLayout"));
        leftHS_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        targetButtonsLayout->addItem(leftHS_3);

        openTargetImgPB = new QPushButton(centralwidget);
        openTargetImgPB->setObjectName(QString::fromUtf8("openTargetImgPB"));
        openTargetImgPB->setMinimumSize(QSize(98, 23));
        openTargetImgPB->setMaximumSize(QSize(120, 23));

        targetButtonsLayout->addWidget(openTargetImgPB);

        rightHS_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        targetButtonsLayout->addItem(rightHS_3);


        targetImgLayout->addLayout(targetButtonsLayout);

        targetImgLayout->setStretch(0, 1);

        imgsLayout->addLayout(targetImgLayout);

        targetResultImgsHS = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        imgsLayout->addItem(targetResultImgsHS);

        resultImgLayout = new QVBoxLayout();
        resultImgLayout->setObjectName(QString::fromUtf8("resultImgLayout"));
        resultImgLayout->setContentsMargins(0, -1, -1, -1);
        resultImgLbl = new ScaleLabel(centralwidget);
        resultImgLbl->setObjectName(QString::fromUtf8("resultImgLbl"));
        sizePolicy1.setHeightForWidth(resultImgLbl->sizePolicy().hasHeightForWidth());
        resultImgLbl->setSizePolicy(sizePolicy1);
        resultImgLbl->setMinimumSize(QSize(200, 200));
        resultImgLbl->setMaximumSize(QSize(660, 660));
        resultImgLbl->setFrameShape(QFrame::NoFrame);
        resultImgLbl->setAlignment(Qt::AlignCenter);
        resultImgLbl->setWordWrap(true);

        resultImgLayout->addWidget(resultImgLbl);

        resultButtonsLayout = new QHBoxLayout();
        resultButtonsLayout->setObjectName(QString::fromUtf8("resultButtonsLayout"));
        leftHS_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        resultButtonsLayout->addItem(leftHS_2);

        startColorizationPB = new QPushButton(centralwidget);
        startColorizationPB->setObjectName(QString::fromUtf8("startColorizationPB"));
        startColorizationPB->setMinimumSize(QSize(75, 23));
        startColorizationPB->setMaximumSize(QSize(100, 23));

        resultButtonsLayout->addWidget(startColorizationPB);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        resultButtonsLayout->addItem(horizontalSpacer);

        resetPB = new QPushButton(centralwidget);
        resetPB->setObjectName(QString::fromUtf8("resetPB"));

        resultButtonsLayout->addWidget(resetPB);

        rightHS_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        resultButtonsLayout->addItem(rightHS_2);


        resultImgLayout->addLayout(resultButtonsLayout);


        imgsLayout->addLayout(resultImgLayout);

        resultSourceImgsHS = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        imgsLayout->addItem(resultSourceImgsHS);

        sourceImgLayout = new QVBoxLayout();
        sourceImgLayout->setObjectName(QString::fromUtf8("sourceImgLayout"));
        sourceImgLbl = new ScaleLabel(centralwidget);
        sourceImgLbl->setObjectName(QString::fromUtf8("sourceImgLbl"));
        sizePolicy1.setHeightForWidth(sourceImgLbl->sizePolicy().hasHeightForWidth());
        sourceImgLbl->setSizePolicy(sizePolicy1);
        sourceImgLbl->setMinimumSize(QSize(200, 200));
        sourceImgLbl->setMaximumSize(QSize(660, 660));
        sourceImgLbl->setFrameShape(QFrame::NoFrame);
        sourceImgLbl->setAlignment(Qt::AlignCenter);
        sourceImgLbl->setWordWrap(true);

        sourceImgLayout->addWidget(sourceImgLbl);

        sourceButtonsLayout = new QHBoxLayout();
        sourceButtonsLayout->setObjectName(QString::fromUtf8("sourceButtonsLayout"));
        leftHS = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        sourceButtonsLayout->addItem(leftHS);

        openSourceImgPB = new QPushButton(centralwidget);
        openSourceImgPB->setObjectName(QString::fromUtf8("openSourceImgPB"));
        openSourceImgPB->setMinimumSize(QSize(100, 23));
        openSourceImgPB->setMaximumSize(QSize(120, 23));

        sourceButtonsLayout->addWidget(openSourceImgPB);

        middleHS = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        sourceButtonsLayout->addItem(middleHS);

        findSourceImgPB = new QPushButton(centralwidget);
        findSourceImgPB->setObjectName(QString::fromUtf8("findSourceImgPB"));
        findSourceImgPB->setMinimumSize(QSize(60, 23));
        findSourceImgPB->setMaximumSize(QSize(80, 23));
        findSourceImgPB->setCheckable(false);
        findSourceImgPB->setChecked(false);
        findSourceImgPB->setAutoRepeat(false);
        findSourceImgPB->setAutoExclusive(false);
        findSourceImgPB->setAutoDefault(false);
        findSourceImgPB->setDefault(false);
        findSourceImgPB->setFlat(false);

        sourceButtonsLayout->addWidget(findSourceImgPB);

        rightHS = new QSpacerItem(10, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        sourceButtonsLayout->addItem(rightHS);


        sourceImgLayout->addLayout(sourceButtonsLayout);


        imgsLayout->addLayout(sourceImgLayout);


        verticalLayout->addLayout(imgsLayout);

        skoLayout = new QHBoxLayout();
        skoLayout->setObjectName(QString::fromUtf8("skoLayout"));
        leftSKOHS = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        skoLayout->addItem(leftSKOHS);

        skoLbl = new QLabel(centralwidget);
        skoLbl->setObjectName(QString::fromUtf8("skoLbl"));
        sizePolicy.setHeightForWidth(skoLbl->sizePolicy().hasHeightForWidth());
        skoLbl->setSizePolicy(sizePolicy);

        skoLayout->addWidget(skoLbl);

        lineSKO = new QLineEdit(centralwidget);
        lineSKO->setObjectName(QString::fromUtf8("lineSKO"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineSKO->sizePolicy().hasHeightForWidth());
        lineSKO->setSizePolicy(sizePolicy2);
        lineSKO->setMinimumSize(QSize(20, 20));
        lineSKO->setMaximumSize(QSize(100, 20));
        lineSKO->setFrame(true);
        lineSKO->setReadOnly(true);

        skoLayout->addWidget(lineSKO);

        rightSKOHS = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        skoLayout->addItem(rightSKOHS);


        verticalLayout->addLayout(skoLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuDatabase = new QMenu(menubar);
        menuDatabase->setObjectName(QString::fromUtf8("menuDatabase"));
        menuColorization = new QMenu(menubar);
        menuColorization->setObjectName(QString::fromUtf8("menuColorization"));
        menuColorization->setEnabled(false);
        menuHistogram = new QMenu(menubar);
        menuHistogram->setObjectName(QString::fromUtf8("menuHistogram"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuDatabase->menuAction());
        menubar->addAction(menuColorization->menuAction());
        menubar->addAction(menuHistogram->menuAction());
        menuFile->addAction(actionOpenTargetImage);
        menuFile->addAction(actionOpenSourceImage);
        menuFile->addSeparator();
        menuFile->addAction(actionSaveResult);
        menuFile->addSeparator();
        menuFile->addAction(actionPreferences);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuDatabase->addAction(actionCreateDatabase);
        menuDatabase->addAction(actionOpenDatabase);
        menuDatabase->addAction(actionAddImages);
        menuHistogram->addAction(actionFormHist);

        retranslateUi(MainWindow);
        QObject::connect(actionClose, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GreyToColor", 0, QApplication::UnicodeUTF8));
        actionOpenTargetImage->setText(QApplication::translate("MainWindow", "Open target image...", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        actionOpenSourceImage->setText(QApplication::translate("MainWindow", "Open source image...", 0, QApplication::UnicodeUTF8));
        actionSaveResult->setText(QApplication::translate("MainWindow", "Save result...", 0, QApplication::UnicodeUTF8));
        actionCreateDatabase->setText(QApplication::translate("MainWindow", "Create database...", 0, QApplication::UnicodeUTF8));
        actionAddImages->setText(QApplication::translate("MainWindow", "Add images...", 0, QApplication::UnicodeUTF8));
        actionOpenDatabase->setText(QApplication::translate("MainWindow", "Open database...", 0, QApplication::UnicodeUTF8));
        actionPreferences->setText(QApplication::translate("MainWindow", "Preferences", 0, QApplication::UnicodeUTF8));
        actionLumHist->setText(QApplication::translate("MainWindow", "Luminance Histogram", 0, QApplication::UnicodeUTF8));
        actionSubsampLum->setText(QApplication::translate("MainWindow", "Subsampled Luminance", 0, QApplication::UnicodeUTF8));
        actionLumGradHists->setText(QApplication::translate("MainWindow", "Luminance and Gradient Histograms", 0, QApplication::UnicodeUTF8));
        actionSubsampLumGrad->setText(QApplication::translate("MainWindow", "Subsampled Luminance and Gradient", 0, QApplication::UnicodeUTF8));
        actionWalshSimple->setText(QApplication::translate("MainWindow", "Walsh Simple", 0, QApplication::UnicodeUTF8));
        actionWalshNeighbor->setText(QApplication::translate("MainWindow", "Walsh Neighbor", 0, QApplication::UnicodeUTF8));
        actionWNNoRand->setText(QApplication::translate("MainWindow", "Walsh Neighbor No Rand", 0, QApplication::UnicodeUTF8));
        actionWNOneRand->setText(QApplication::translate("MainWindow", "Walsh Neighbor One Rand", 0, QApplication::UnicodeUTF8));
        actionFormHist->setText(QApplication::translate("MainWindow", "Form histogram", 0, QApplication::UnicodeUTF8));
        targetImgLbl->setText(QString());
        openTargetImgPB->setText(QApplication::translate("MainWindow", "Open target image", 0, QApplication::UnicodeUTF8));
        resultImgLbl->setText(QString());
        startColorizationPB->setText(QApplication::translate("MainWindow", "Colorize", 0, QApplication::UnicodeUTF8));
        resetPB->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        sourceImgLbl->setText(QString());
        openSourceImgPB->setText(QApplication::translate("MainWindow", "Open source image", 0, QApplication::UnicodeUTF8));
        findSourceImgPB->setText(QApplication::translate("MainWindow", "Find in DB", 0, QApplication::UnicodeUTF8));
        skoLbl->setText(QApplication::translate("MainWindow", "SKO:", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuDatabase->setTitle(QApplication::translate("MainWindow", "Database", 0, QApplication::UnicodeUTF8));
        menuColorization->setTitle(QApplication::translate("MainWindow", "Colorization", 0, QApplication::UnicodeUTF8));
        menuHistogram->setTitle(QApplication::translate("MainWindow", "Histogram", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
