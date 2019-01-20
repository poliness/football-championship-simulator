/********************************************************************************
** Form generated from reading UI file 'pucharowaWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUCHAROWAWINDOW_H
#define UI_PUCHAROWAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pucharowaWindow
{
public:
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_5;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout;
    QGridLayout *trzecieMiejsce;
    QGridLayout *cwiercfinal;
    QGridLayout *finau;
    QGridLayout *przedcwiercfinal;
    QGridLayout *polfinal;
    QGridLayout *gridLayout_6;
    QPushButton *dalejButton;
    QPushButton *wsteczButton;

    void setupUi(QDialog *pucharowaWindow)
    {
        if (pucharowaWindow->objectName().isEmpty())
            pucharowaWindow->setObjectName(QStringLiteral("pucharowaWindow"));
        pucharowaWindow->resize(638, 572);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pucharowaWindow->sizePolicy().hasHeightForWidth());
        pucharowaWindow->setSizePolicy(sizePolicy);
        pucharowaWindow->setMinimumSize(QSize(0, 0));
        pucharowaWindow->setMaximumSize(QSize(123123, 123123));
        gridLayout_3 = new QGridLayout(pucharowaWindow);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        scrollArea = new QScrollArea(pucharowaWindow);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(0, 500));
        scrollArea->setMaximumSize(QSize(16777215, 16777215));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 616, 498));
        gridLayout = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        trzecieMiejsce = new QGridLayout();
        trzecieMiejsce->setObjectName(QStringLiteral("trzecieMiejsce"));
        trzecieMiejsce->setContentsMargins(-1, 25, -1, -1);

        gridLayout->addLayout(trzecieMiejsce, 3, 0, 1, 1);

        cwiercfinal = new QGridLayout();
        cwiercfinal->setObjectName(QStringLiteral("cwiercfinal"));
        cwiercfinal->setContentsMargins(-1, 25, -1, -1);

        gridLayout->addLayout(cwiercfinal, 1, 0, 1, 1);

        finau = new QGridLayout();
        finau->setObjectName(QStringLiteral("finau"));
        finau->setContentsMargins(-1, 25, -1, -1);

        gridLayout->addLayout(finau, 4, 0, 1, 1);

        przedcwiercfinal = new QGridLayout();
        przedcwiercfinal->setObjectName(QStringLiteral("przedcwiercfinal"));
        przedcwiercfinal->setContentsMargins(-1, 25, -1, -1);

        gridLayout->addLayout(przedcwiercfinal, 0, 0, 1, 1);

        polfinal = new QGridLayout();
        polfinal->setObjectName(QStringLiteral("polfinal"));
        polfinal->setContentsMargins(0, 25, -1, -1);

        gridLayout->addLayout(polfinal, 2, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_5->addWidget(scrollArea, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_5, 0, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        dalejButton = new QPushButton(pucharowaWindow);
        dalejButton->setObjectName(QStringLiteral("dalejButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dalejButton->sizePolicy().hasHeightForWidth());
        dalejButton->setSizePolicy(sizePolicy2);
        dalejButton->setMaximumSize(QSize(200, 16777215));

        gridLayout_6->addWidget(dalejButton, 0, 1, 1, 1);

        wsteczButton = new QPushButton(pucharowaWindow);
        wsteczButton->setObjectName(QStringLiteral("wsteczButton"));
        wsteczButton->setMaximumSize(QSize(200, 16777215));

        gridLayout_6->addWidget(wsteczButton, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_6, 1, 0, 2, 1);


        retranslateUi(pucharowaWindow);

        QMetaObject::connectSlotsByName(pucharowaWindow);
    } // setupUi

    void retranslateUi(QDialog *pucharowaWindow)
    {
        pucharowaWindow->setWindowTitle(QApplication::translate("pucharowaWindow", "Dialog", 0));
        dalejButton->setText(QApplication::translate("pucharowaWindow", "Zakonczenie", 0));
        wsteczButton->setText(QApplication::translate("pucharowaWindow", "Wstecz", 0));
    } // retranslateUi

};

namespace Ui {
    class pucharowaWindow: public Ui_pucharowaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUCHAROWAWINDOW_H
