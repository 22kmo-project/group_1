/********************************************************************************
** Form generated from reading UI file 'saldowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALDOWINDOW_H
#define UI_SALDOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_saldoWindow
{
public:
    QLabel *labelSaldo;
    QPushButton *suljeButton;
    QLabel *labelAsiakas;
    QLabel *labelTapahtuma;

    void setupUi(QWidget *saldoWindow)
    {
        if (saldoWindow->objectName().isEmpty())
            saldoWindow->setObjectName(QString::fromUtf8("saldoWindow"));
        saldoWindow->resize(400, 300);
        labelSaldo = new QLabel(saldoWindow);
        labelSaldo->setObjectName(QString::fromUtf8("labelSaldo"));
        labelSaldo->setGeometry(QRect(30, 130, 331, 61));
        suljeButton = new QPushButton(saldoWindow);
        suljeButton->setObjectName(QString::fromUtf8("suljeButton"));
        suljeButton->setGeometry(QRect(150, 240, 83, 29));
        labelAsiakas = new QLabel(saldoWindow);
        labelAsiakas->setObjectName(QString::fromUtf8("labelAsiakas"));
        labelAsiakas->setGeometry(QRect(40, 40, 321, 81));
        labelTapahtuma = new QLabel(saldoWindow);
        labelTapahtuma->setObjectName(QString::fromUtf8("labelTapahtuma"));
        labelTapahtuma->setGeometry(QRect(260, 70, 131, 191));

        retranslateUi(saldoWindow);

        QMetaObject::connectSlotsByName(saldoWindow);
    } // setupUi

    void retranslateUi(QWidget *saldoWindow)
    {
        saldoWindow->setWindowTitle(QCoreApplication::translate("saldoWindow", "Form", nullptr));
        labelSaldo->setText(QString());
        suljeButton->setText(QCoreApplication::translate("saldoWindow", "SULJE", nullptr));
        labelAsiakas->setText(QString());
        labelTapahtuma->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class saldoWindow: public Ui_saldoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALDOWINDOW_H
