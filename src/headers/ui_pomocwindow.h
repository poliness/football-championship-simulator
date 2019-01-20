/********************************************************************************
** Form generated from reading UI file 'pomocwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POMOCWINDOW_H
#define UI_POMOCWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pomocWindow
{
public:
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *pomocWindow)
    {
        if (pomocWindow->objectName().isEmpty())
            pomocWindow->setObjectName(QStringLiteral("pomocWindow"));
        pomocWindow->resize(635, 191);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush4(QColor(255, 255, 220, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        pomocWindow->setPalette(palette);
        plainTextEdit = new QPlainTextEdit(pomocWindow);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(20, 10, 581, 171));
        plainTextEdit->setUndoRedoEnabled(false);
        plainTextEdit->setReadOnly(true);

        retranslateUi(pomocWindow);

        QMetaObject::connectSlotsByName(pomocWindow);
    } // setupUi

    void retranslateUi(QWidget *pomocWindow)
    {
        pomocWindow->setWindowTitle(QApplication::translate("pomocWindow", "pomocWindow", 0));
        plainTextEdit->setPlainText(QApplication::translate("pomocWindow", "Symulator rozgrywek mistrzostw \305\233wiata w pi\305\202ce no\305\274nej to prosta symulacja turnieju Mundial. Uzytkownik wybiera spo\305\233r\303\263d narodowych federacji pi\305\202ki no\305\274nej 32 reprezentacje, ustala ich pozycje w rankingu kontynentu i uruchamia symulacj\304\231. W ten spos\303\263b otrzymuje tabele wraz ze statystykami. \n"
"\n"
"Aby rozpocz\304\205\304\207, kliknij \"Dodaj\" obok nazwy reprezentacji oraz okre\305\233l miejsce w rankingu dru\305\274yny. Miejsce w rankigu dla dru\305\274yn z tego samego kontynentu musi by\304\207 unikatowe. \n"
"Licznik wskazuje ile dru\305\274yn z danego kontynentu wybra\305\202 u\305\274ytkownik oraz ich ca\305\202kowit\304\205 liczb\304\231. \n"
"\n"
"Po wybraniu 32 u\305\274ytkownik klika \"Uruchom symulacj\304\231\" i uruchamia symulator. \n"
"W kolejnych oknach wy\305\233wietlane s\304\205 tabele ze statystykami rozegranych mecz\303\263w.\n"
"\n"
"U\305\274ytkownik mo\305\274e tak\305\274e wylosowa\304\207 dru\305\274yny.", 0));
    } // retranslateUi

};

namespace Ui {
    class pomocWindow: public Ui_pomocWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POMOCWINDOW_H
