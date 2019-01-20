/********************************************************************************
** Form generated from reading UI file 'oknopowitalne.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OKNOPOWITALNE_H
#define UI_OKNOPOWITALNE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OknoPowitalne
{
public:
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;

    void setupUi(QWidget *OknoPowitalne)
    {
        if (OknoPowitalne->objectName().isEmpty())
            OknoPowitalne->setObjectName(QStringLiteral("OknoPowitalne"));
        OknoPowitalne->resize(850, 631);
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
        OknoPowitalne->setPalette(palette);
        label = new QLabel(OknoPowitalne);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(270, 150, 291, 281));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Resources/uksw.png")));
        label->setScaledContents(true);
        label_3 = new QLabel(OknoPowitalne);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 0, 511, 161));
        QFont font;
        font.setFamily(QStringLiteral("Cambria"));
        font.setPointSize(28);
        label_3->setFont(font);
        label_2 = new QLabel(OknoPowitalne);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 440, 551, 191));
        QFont font1;
        font1.setFamily(QStringLiteral("Cambria"));
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        retranslateUi(OknoPowitalne);

        QMetaObject::connectSlotsByName(OknoPowitalne);
    } // setupUi

    void retranslateUi(QWidget *OknoPowitalne)
    {
        OknoPowitalne->setWindowTitle(QApplication::translate("OknoPowitalne", "OknoPowitalne", 0));
        label->setText(QString());
        label_3->setText(QApplication::translate("OknoPowitalne", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Uniwersytet Kardyna\305\202a Stefana Wyszy\305\204skiego w Warszawie</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">Wydzia\305\202 Matematyczno - Przyrodniczy<br/>Szko\305\202a Nauk \305\232cis\305\202ych</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("OknoPowitalne", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt;\">Symulator rozgrywek mistrzostw \305\233wiata w pi\305\202ce no\305\274nej</span><span style=\" font-size:16pt;\"><br/></span></p><p align=\"center\"><span style=\" font-size:16pt;\"><br/></span><span style=\" font-size:12pt;\">Paulina Zapletal</span></p><p align=\"center\"><span style=\" font-size:12pt;\"><br/>Warszawa 2017</span></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class OknoPowitalne: public Ui_OknoPowitalne {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OKNOPOWITALNE_H
