/********************************************************************************
** Form generated from reading UI file 'zakonczeniewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ZAKONCZENIEWINDOW_H
#define UI_ZAKONCZENIEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ZakonczenieWindow
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *zakonczenieLayout;
    QPushButton *wsteczButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *ZakonczenieWindow)
    {
        if (ZakonczenieWindow->objectName().isEmpty())
            ZakonczenieWindow->setObjectName(QStringLiteral("ZakonczenieWindow"));
        ZakonczenieWindow->resize(390, 318);
        gridLayoutWidget = new QWidget(ZakonczenieWindow);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 351, 211));
        zakonczenieLayout = new QGridLayout(gridLayoutWidget);
        zakonczenieLayout->setSpacing(6);
        zakonczenieLayout->setContentsMargins(11, 11, 11, 11);
        zakonczenieLayout->setObjectName(QStringLiteral("zakonczenieLayout"));
        zakonczenieLayout->setContentsMargins(0, 0, 0, 0);
        wsteczButton = new QPushButton(ZakonczenieWindow);
        wsteczButton->setObjectName(QStringLiteral("wsteczButton"));
        wsteczButton->setGeometry(QRect(70, 270, 75, 23));
        pushButton_2 = new QPushButton(ZakonczenieWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 270, 75, 23));

        retranslateUi(ZakonczenieWindow);

        QMetaObject::connectSlotsByName(ZakonczenieWindow);
    } // setupUi

    void retranslateUi(QWidget *ZakonczenieWindow)
    {
        ZakonczenieWindow->setWindowTitle(QApplication::translate("ZakonczenieWindow", "ZakonczenieWindow", 0));
        wsteczButton->setText(QApplication::translate("ZakonczenieWindow", "Wstecz", 0));
        pushButton_2->setText(QApplication::translate("ZakonczenieWindow", "Zakoncz", 0));
    } // retranslateUi

};

namespace Ui {
    class ZakonczenieWindow: public Ui_ZakonczenieWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ZAKONCZENIEWINDOW_H
