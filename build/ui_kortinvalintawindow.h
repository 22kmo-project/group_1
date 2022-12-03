/********************************************************************************
** Form generated from reading UI file 'kortinvalintawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KORTINVALINTAWINDOW_H
#define UI_KORTINVALINTAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_kortinValintaWindow
{
public:
    QPushButton *creditButton;
    QPushButton *debitButton;
    QLabel *label;

    void setupUi(QWidget *kortinValintaWindow)
    {
        if (kortinValintaWindow->objectName().isEmpty())
            kortinValintaWindow->setObjectName(QString::fromUtf8("kortinValintaWindow"));
        kortinValintaWindow->resize(400, 300);
        creditButton = new QPushButton(kortinValintaWindow);
        creditButton->setObjectName(QString::fromUtf8("creditButton"));
        creditButton->setGeometry(QRect(80, 110, 83, 29));
        debitButton = new QPushButton(kortinValintaWindow);
        debitButton->setObjectName(QString::fromUtf8("debitButton"));
        debitButton->setGeometry(QRect(220, 110, 83, 29));
        label = new QLabel(kortinValintaWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 50, 111, 20));

        retranslateUi(kortinValintaWindow);

        QMetaObject::connectSlotsByName(kortinValintaWindow);
    } // setupUi

    void retranslateUi(QWidget *kortinValintaWindow)
    {
        kortinValintaWindow->setWindowTitle(QCoreApplication::translate("kortinValintaWindow", "Form", nullptr));
        creditButton->setText(QCoreApplication::translate("kortinValintaWindow", "Credit", nullptr));
        debitButton->setText(QCoreApplication::translate("kortinValintaWindow", "Debit", nullptr));
        label->setText(QCoreApplication::translate("kortinValintaWindow", "Valitse kortin tyyppi", nullptr));
    } // retranslateUi

};

namespace Ui {
    class kortinValintaWindow: public Ui_kortinValintaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KORTINVALINTAWINDOW_H
