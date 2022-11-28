/********************************************************************************
** Form generated from reading UI file 'bankwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANKWINDOW_H
#define UI_BANKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bankwindow
{
public:
    QLabel *labelAccount;

    void setupUi(QWidget *bankwindow)
    {
        if (bankwindow->objectName().isEmpty())
            bankwindow->setObjectName(QString::fromUtf8("bankwindow"));
        bankwindow->resize(400, 300);
        labelAccount = new QLabel(bankwindow);
        labelAccount->setObjectName(QString::fromUtf8("labelAccount"));
        labelAccount->setGeometry(QRect(110, 130, 63, 20));

        retranslateUi(bankwindow);

        QMetaObject::connectSlotsByName(bankwindow);
    } // setupUi

    void retranslateUi(QWidget *bankwindow)
    {
        bankwindow->setWindowTitle(QCoreApplication::translate("bankwindow", "Form", nullptr));
        labelAccount->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class bankwindow: public Ui_bankwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANKWINDOW_H
