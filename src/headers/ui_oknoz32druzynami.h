/********************************************************************************
** Form generated from reading UI file 'oknoz32druzynami.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OKNOZ32DRUZYNAMI_H
#define UI_OKNOZ32DRUZYNAMI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OknoZ32Druzynami
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *kolumnaDruzynLayout;
    QPushButton *dalejButton;

    void setupUi(QWidget *OknoZ32Druzynami)
    {
        if (OknoZ32Druzynami->objectName().isEmpty())
            OknoZ32Druzynami->setObjectName(QStringLiteral("OknoZ32Druzynami"));
        OknoZ32Druzynami->resize(351, 552);
        verticalLayoutWidget = new QWidget(OknoZ32Druzynami);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 331, 481));
        kolumnaDruzynLayout = new QVBoxLayout(verticalLayoutWidget);
        kolumnaDruzynLayout->setSpacing(6);
        kolumnaDruzynLayout->setContentsMargins(11, 11, 11, 11);
        kolumnaDruzynLayout->setObjectName(QStringLiteral("kolumnaDruzynLayout"));
        kolumnaDruzynLayout->setContentsMargins(0, 0, 0, 0);
        dalejButton = new QPushButton(OknoZ32Druzynami);
        dalejButton->setObjectName(QStringLiteral("dalejButton"));
        dalejButton->setGeometry(QRect(140, 510, 75, 23));

        retranslateUi(OknoZ32Druzynami);

        QMetaObject::connectSlotsByName(OknoZ32Druzynami);
    } // setupUi

    void retranslateUi(QWidget *OknoZ32Druzynami)
    {
        OknoZ32Druzynami->setWindowTitle(QApplication::translate("OknoZ32Druzynami", "OknoZ32Druzynami", 0));
        dalejButton->setText(QApplication::translate("OknoZ32Druzynami", "Dalej", 0));
    } // retranslateUi

};

namespace Ui {
    class OknoZ32Druzynami: public Ui_OknoZ32Druzynami {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OKNOZ32DRUZYNAMI_H
