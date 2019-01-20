/********************************************************************************
** Form generated from reading UI file 'oknozmeczamigrupowymi.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OKNOZMECZAMIGRUPOWYMI_H
#define UI_OKNOZMECZAMIGRUPOWYMI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OknoZMeczamiGrupowymi
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *gridLayoutWidget;
    QGridLayout *layoutZMeczamiGrupowymi;
    QPushButton *wsteczButton;
    QPushButton *dalejButton;

    void setupUi(QWidget *OknoZMeczamiGrupowymi)
    {
        if (OknoZMeczamiGrupowymi->objectName().isEmpty())
            OknoZMeczamiGrupowymi->setObjectName(QStringLiteral("OknoZMeczamiGrupowymi"));
        OknoZMeczamiGrupowymi->resize(675, 633);
        scrollArea = new QScrollArea(OknoZMeczamiGrupowymi);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 671, 621));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 649, 900));
        gridLayoutWidget = new QWidget(scrollAreaWidgetContents);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 631, 811));
        layoutZMeczamiGrupowymi = new QGridLayout(gridLayoutWidget);
        layoutZMeczamiGrupowymi->setSpacing(6);
        layoutZMeczamiGrupowymi->setContentsMargins(11, 11, 11, 11);
        layoutZMeczamiGrupowymi->setObjectName(QStringLiteral("layoutZMeczamiGrupowymi"));
        layoutZMeczamiGrupowymi->setContentsMargins(0, 0, 0, 0);
        wsteczButton = new QPushButton(scrollAreaWidgetContents);
        wsteczButton->setObjectName(QStringLiteral("wsteczButton"));
        wsteczButton->setGeometry(QRect(130, 850, 75, 23));
        dalejButton = new QPushButton(scrollAreaWidgetContents);
        dalejButton->setObjectName(QStringLiteral("dalejButton"));
        dalejButton->setGeometry(QRect(460, 850, 75, 23));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(OknoZMeczamiGrupowymi);

        QMetaObject::connectSlotsByName(OknoZMeczamiGrupowymi);
    } // setupUi

    void retranslateUi(QWidget *OknoZMeczamiGrupowymi)
    {
        OknoZMeczamiGrupowymi->setWindowTitle(QApplication::translate("OknoZMeczamiGrupowymi", "OknoZMeczamiGrupowymi", 0));
        wsteczButton->setText(QApplication::translate("OknoZMeczamiGrupowymi", "Wstecz", 0));
        dalejButton->setText(QApplication::translate("OknoZMeczamiGrupowymi", "Dalej", 0));
    } // retranslateUi

};

namespace Ui {
    class OknoZMeczamiGrupowymi: public Ui_OknoZMeczamiGrupowymi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OKNOZMECZAMIGRUPOWYMI_H
