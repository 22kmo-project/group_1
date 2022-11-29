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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bankwindow
{
public:
    QLabel *labelAccount;
    QPushButton *saldoButton;
    QPushButton *tapahtumaButton;
    QPushButton *nostoButton;
    QPushButton *kirjauduUlosButton;

    void setupUi(QWidget *bankwindow)
    {
        if (bankwindow->objectName().isEmpty())
            bankwindow->setObjectName(QString::fromUtf8("bankwindow"));
        bankwindow->resize(400, 300);
        labelAccount = new QLabel(bankwindow);
        labelAccount->setObjectName(QString::fromUtf8("labelAccount"));
        labelAccount->setGeometry(QRect(110, 130, 63, 20));
        saldoButton = new QPushButton(bankwindow);
        saldoButton->setObjectName(QString::fromUtf8("saldoButton"));
        saldoButton->setGeometry(QRect(60, 60, 83, 29));
        tapahtumaButton = new QPushButton(bankwindow);
        tapahtumaButton->setObjectName(QString::fromUtf8("tapahtumaButton"));
        tapahtumaButton->setGeometry(QRect(192, 60, 121, 29));
        nostoButton = new QPushButton(bankwindow);
        nostoButton->setObjectName(QString::fromUtf8("nostoButton"));
        nostoButton->setGeometry(QRect(60, 200, 83, 29));
        kirjauduUlosButton = new QPushButton(bankwindow);
        kirjauduUlosButton->setObjectName(QString::fromUtf8("kirjauduUlosButton"));
        kirjauduUlosButton->setGeometry(QRect(210, 200, 83, 29));

        retranslateUi(bankwindow);

        QMetaObject::connectSlotsByName(bankwindow);
    } // setupUi

    void retranslateUi(QWidget *bankwindow)
    {
        bankwindow->setWindowTitle(QCoreApplication::translate("bankwindow", "Form", nullptr));
        labelAccount->setText(QString());
        saldoButton->setText(QCoreApplication::translate("bankwindow", "N\303\244yt\303\244 saldo", nullptr));
        tapahtumaButton->setText(QCoreApplication::translate("bankwindow", "Selaa tilitapahtumia", nullptr));
        nostoButton->setText(QCoreApplication::translate("bankwindow", "Nosta rahaa", nullptr));
        kirjauduUlosButton->setText(QCoreApplication::translate("bankwindow", "Kirjaudu ulos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bankwindow: public Ui_bankwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANKWINDOW_H
