/********************************************************************************
** Form generated from reading UI file 'simulationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONWINDOW_H
#define UI_SIMULATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationWindow
{
public:
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout;
    QGridLayout *symulacja;
    QGridLayout *polfinal;
    QGridLayout *przedcwiercfinal;
    QGridLayout *finau;
    QGridLayout *cwiercfinal;

    void setupUi(QDialog *SimulationWindow)
    {
        if (SimulationWindow->objectName().isEmpty())
            SimulationWindow->setObjectName(QStringLiteral("SimulationWindow"));
        SimulationWindow->resize(943, 700);
        SimulationWindow->setMinimumSize(QSize(0, 0));
        SimulationWindow->setMaximumSize(QSize(123123, 123123));
        gridLayout_3 = new QGridLayout(SimulationWindow);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        scrollArea = new QScrollArea(SimulationWindow);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 923, 680));
        gridLayout = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        symulacja = new QGridLayout();
        symulacja->setObjectName(QStringLiteral("symulacja"));

        gridLayout->addLayout(symulacja, 0, 0, 1, 1);

        polfinal = new QGridLayout();
        polfinal->setObjectName(QStringLiteral("polfinal"));
        polfinal->setContentsMargins(0, 25, -1, -1);

        gridLayout->addLayout(polfinal, 3, 0, 1, 1);

        przedcwiercfinal = new QGridLayout();
        przedcwiercfinal->setObjectName(QStringLiteral("przedcwiercfinal"));
        przedcwiercfinal->setContentsMargins(-1, 25, -1, -1);

        gridLayout->addLayout(przedcwiercfinal, 1, 0, 1, 1);

        finau = new QGridLayout();
        finau->setObjectName(QStringLiteral("finau"));
        finau->setContentsMargins(-1, 25, -1, -1);

        gridLayout->addLayout(finau, 5, 0, 1, 1);

        cwiercfinal = new QGridLayout();
        cwiercfinal->setObjectName(QStringLiteral("cwiercfinal"));
        cwiercfinal->setContentsMargins(-1, 25, -1, -1);

        gridLayout->addLayout(cwiercfinal, 2, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        gridLayout_3->addWidget(scrollArea, 1, 0, 1, 1);


        retranslateUi(SimulationWindow);

        QMetaObject::connectSlotsByName(SimulationWindow);
    } // setupUi

    void retranslateUi(QDialog *SimulationWindow)
    {
        SimulationWindow->setWindowTitle(QApplication::translate("SimulationWindow", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class SimulationWindow: public Ui_SimulationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONWINDOW_H
