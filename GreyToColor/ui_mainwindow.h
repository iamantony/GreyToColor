/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun 27. Jan 16:39:04 2013
**      by: Qt User Interface Compiler version 4.8.1
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

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenImage;
    QAction *actionClose;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *imgsLayout;
    QVBoxLayout *targetImgLayout;
    QLabel *targetImgLbl;
    QHBoxLayout *targetButtonsLayout;
    QSpacerItem *leftHS_3;
    QPushButton *openTargetImgPB;
    QSpacerItem *rightHS_3;
    QSpacerItem *targetResultImgsHS;
    QVBoxLayout *resultImgLayout;
    QLabel *resultImgLbl;
    QHBoxLayout *resultButtonsLayout;
    QSpacerItem *leftHS_2;
    QPushButton *saveResultPB;
    QSpacerItem *rightHS_2;
    QSpacerItem *resultSourceImgsHS;
    QVBoxLayout *sourceImgLayout;
    QLabel *sourceImgLbl;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setSizeIncrement(QSize(1, 1));
        MainWindow->setBaseSize(QSize(800, 600));
        actionOpenImage = new QAction(MainWindow);
        actionOpenImage->setObjectName(QString::fromUtf8("actionOpenImage"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        imgsLayout = new QHBoxLayout();
        imgsLayout->setObjectName(QString::fromUtf8("imgsLayout"));
        imgsLayout->setSizeConstraint(QLayout::SetMaximumSize);
        targetImgLayout = new QVBoxLayout();
        targetImgLayout->setObjectName(QString::fromUtf8("targetImgLayout"));
        targetImgLbl = new QLabel(centralwidget);
        targetImgLbl->setObjectName(QString::fromUtf8("targetImgLbl"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(targetImgLbl->sizePolicy().hasHeightForWidth());
        targetImgLbl->setSizePolicy(sizePolicy);
        targetImgLbl->setMinimumSize(QSize(200, 200));
        targetImgLbl->setMaximumSize(QSize(660, 660));
        targetImgLbl->setFrameShape(QFrame::NoFrame);
        targetImgLbl->setPixmap(QPixmap(QString::fromUtf8(":/defaultImgs/UI/target_image.png")));
        targetImgLbl->setScaledContents(true);
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

        targetResultImgsHS = new QSpacerItem(13, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        imgsLayout->addItem(targetResultImgsHS);

        resultImgLayout = new QVBoxLayout();
        resultImgLayout->setObjectName(QString::fromUtf8("resultImgLayout"));
        resultImgLayout->setContentsMargins(0, -1, -1, -1);
        resultImgLbl = new QLabel(centralwidget);
        resultImgLbl->setObjectName(QString::fromUtf8("resultImgLbl"));
        sizePolicy.setHeightForWidth(resultImgLbl->sizePolicy().hasHeightForWidth());
        resultImgLbl->setSizePolicy(sizePolicy);
        resultImgLbl->setMinimumSize(QSize(200, 200));
        resultImgLbl->setMaximumSize(QSize(660, 660));
        resultImgLbl->setFrameShape(QFrame::NoFrame);
        resultImgLbl->setPixmap(QPixmap(QString::fromUtf8(":/defaultImgs/UI/result_image.png")));
        resultImgLbl->setScaledContents(true);
        resultImgLbl->setAlignment(Qt::AlignCenter);
        resultImgLbl->setWordWrap(true);

        resultImgLayout->addWidget(resultImgLbl);

        resultButtonsLayout = new QHBoxLayout();
        resultButtonsLayout->setObjectName(QString::fromUtf8("resultButtonsLayout"));
        leftHS_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        resultButtonsLayout->addItem(leftHS_2);

        saveResultPB = new QPushButton(centralwidget);
        saveResultPB->setObjectName(QString::fromUtf8("saveResultPB"));
        saveResultPB->setMinimumSize(QSize(75, 23));
        saveResultPB->setMaximumSize(QSize(100, 23));

        resultButtonsLayout->addWidget(saveResultPB);

        rightHS_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        resultButtonsLayout->addItem(rightHS_2);


        resultImgLayout->addLayout(resultButtonsLayout);


        imgsLayout->addLayout(resultImgLayout);

        resultSourceImgsHS = new QSpacerItem(18, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        imgsLayout->addItem(resultSourceImgsHS);

        sourceImgLayout = new QVBoxLayout();
        sourceImgLayout->setObjectName(QString::fromUtf8("sourceImgLayout"));
        sourceImgLbl = new QLabel(centralwidget);
        sourceImgLbl->setObjectName(QString::fromUtf8("sourceImgLbl"));
        sizePolicy.setHeightForWidth(sourceImgLbl->sizePolicy().hasHeightForWidth());
        sourceImgLbl->setSizePolicy(sizePolicy);
        sourceImgLbl->setMinimumSize(QSize(200, 200));
        sourceImgLbl->setMaximumSize(QSize(660, 660));
        sourceImgLbl->setFrameShape(QFrame::NoFrame);
        sourceImgLbl->setPixmap(QPixmap(QString::fromUtf8(":/defaultImgs/UI/source_image.png")));
        sourceImgLbl->setScaledContents(true);
        sourceImgLbl->setAlignment(Qt::AlignCenter);
        sourceImgLbl->setWordWrap(true);

        sourceImgLayout->addWidget(sourceImgLbl);

        sourceButtonsLayout = new QHBoxLayout();
        sourceButtonsLayout->setObjectName(QString::fromUtf8("sourceButtonsLayout"));
        leftHS = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        sourceButtonsLayout->addItem(leftHS);

        openSourceImgPB = new QPushButton(centralwidget);
        openSourceImgPB->setObjectName(QString::fromUtf8("openSourceImgPB"));
        openSourceImgPB->setMinimumSize(QSize(100, 23));
        openSourceImgPB->setMaximumSize(QSize(120, 23));

        sourceButtonsLayout->addWidget(openSourceImgPB);

        middleHS = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        sourceButtonsLayout->addItem(middleHS);

        findSourceImgPB = new QPushButton(centralwidget);
        findSourceImgPB->setObjectName(QString::fromUtf8("findSourceImgPB"));
        findSourceImgPB->setMinimumSize(QSize(60, 23));
        findSourceImgPB->setMaximumSize(QSize(80, 23));

        sourceButtonsLayout->addWidget(findSourceImgPB);

        rightHS = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

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
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(skoLbl->sizePolicy().hasHeightForWidth());
        skoLbl->setSizePolicy(sizePolicy1);

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
        menubar->setGeometry(QRect(0, 0, 800, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpenImage);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);
        QObject::connect(actionClose, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GreyToColor", 0, QApplication::UnicodeUTF8));
        actionOpenImage->setText(QApplication::translate("MainWindow", "Open image...", 0, QApplication::UnicodeUTF8));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0, QApplication::UnicodeUTF8));
        targetImgLbl->setText(QString());
        openTargetImgPB->setText(QApplication::translate("MainWindow", "Open target image", 0, QApplication::UnicodeUTF8));
        resultImgLbl->setText(QString());
        saveResultPB->setText(QApplication::translate("MainWindow", "Save result", 0, QApplication::UnicodeUTF8));
        sourceImgLbl->setText(QString());
        openSourceImgPB->setText(QApplication::translate("MainWindow", "Open source image", 0, QApplication::UnicodeUTF8));
        findSourceImgPB->setText(QApplication::translate("MainWindow", "Find in DB", 0, QApplication::UnicodeUTF8));
        skoLbl->setText(QApplication::translate("MainWindow", "SKO:", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
