/********************************************************************************
** Form generated from reading UI file 'rankingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANKINGWINDOW_H
#define UI_RANKINGWINDOW_H

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

class Ui_rankingwindow
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *rankingLayout;
    QPushButton *dalejButton;
    QPushButton *wsteczButton;

    void setupUi(QDialog *rankingwindow)
    {
        if (rankingwindow->objectName().isEmpty())
            rankingwindow->setObjectName(QStringLiteral("rankingwindow"));
        rankingwindow->resize(749, 450);
        gridLayoutWidget = new QWidget(rankingwindow);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 731, 361));
        rankingLayout = new QGridLayout(gridLayoutWidget);
        rankingLayout->setObjectName(QStringLiteral("rankingLayout"));
        rankingLayout->setContentsMargins(0, 0, 0, 0);
        dalejButton = new QPushButton(rankingwindow);
        dalejButton->setObjectName(QStringLiteral("dalejButton"));
        dalejButton->setGeometry(QRect(450, 400, 75, 23));
        wsteczButton = new QPushButton(rankingwindow);
        wsteczButton->setObjectName(QStringLiteral("wsteczButton"));
        wsteczButton->setGeometry(QRect(220, 400, 75, 23));

        retranslateUi(rankingwindow);

        QMetaObject::connectSlotsByName(rankingwindow);
    } // setupUi

    void retranslateUi(QDialog *rankingwindow)
    {
        rankingwindow->setWindowTitle(QApplication::translate("rankingwindow", "Dialog", 0));
        dalejButton->setText(QApplication::translate("rankingwindow", "Dalej", 0));
        wsteczButton->setText(QApplication::translate("rankingwindow", "Wstecz", 0));
    } // retranslateUi

};

namespace Ui {
    class rankingwindow: public Ui_rankingwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANKINGWINDOW_H
