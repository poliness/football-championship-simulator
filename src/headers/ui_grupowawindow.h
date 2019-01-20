/********************************************************************************
** Form generated from reading UI file 'grupowawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRUPOWAWINDOW_H
#define UI_GRUPOWAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_grupowaWindow
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *grupowaLayout;
    QPushButton *dalejButton;
    QPushButton *wsteczButton;

    void setupUi(QDialog *grupowaWindow)
    {
        if (grupowaWindow->objectName().isEmpty())
            grupowaWindow->setObjectName(QStringLiteral("grupowaWindow"));
        grupowaWindow->resize(1082, 710);
        gridLayoutWidget = new QWidget(grupowaWindow);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 1061, 641));
        grupowaLayout = new QGridLayout(gridLayoutWidget);
        grupowaLayout->setObjectName(QStringLiteral("grupowaLayout"));
        grupowaLayout->setContentsMargins(0, 0, 0, 0);
        dalejButton = new QPushButton(grupowaWindow);
        dalejButton->setObjectName(QStringLiteral("dalejButton"));
        dalejButton->setGeometry(QRect(690, 670, 75, 23));
        wsteczButton = new QPushButton(grupowaWindow);
        wsteczButton->setObjectName(QStringLiteral("wsteczButton"));
        wsteczButton->setGeometry(QRect(320, 670, 75, 23));

        retranslateUi(grupowaWindow);

        QMetaObject::connectSlotsByName(grupowaWindow);
    } // setupUi

    void retranslateUi(QDialog *grupowaWindow)
    {
        grupowaWindow->setWindowTitle(QApplication::translate("grupowaWindow", "Dialog", 0));
        dalejButton->setText(QApplication::translate("grupowaWindow", "Dalej", 0));
        wsteczButton->setText(QApplication::translate("grupowaWindow", "Wstecz", 0));
    } // retranslateUi

};

namespace Ui {
    class grupowaWindow: public Ui_grupowaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRUPOWAWINDOW_H
