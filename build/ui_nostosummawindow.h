/********************************************************************************
** Form generated from reading UI file 'nostosummawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOSTOSUMMAWINDOW_H
#define UI_NOSTOSUMMAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nostoSummaWindow
{
public:
    QPushButton *pushButton20e;
    QPushButton *pushButton40e;
    QPushButton *pushButton60e;
    QPushButton *pushButton100e;
    QPushButton *pushButton200e;
    QPushButton *pushButton500e;
    QLabel *label;
    QPushButton *suljeButton;
    QLabel *label_2;
    QLabel *tiliLabel;
    QLabel *nosto_info;
    QLabel *kyhny_info;
    QLabel *label_3;
    QLabel *nimi_label;

    void setupUi(QWidget *nostoSummaWindow)
    {
        if (nostoSummaWindow->objectName().isEmpty())
            nostoSummaWindow->setObjectName(QString::fromUtf8("nostoSummaWindow"));
        nostoSummaWindow->resize(472, 379);
        pushButton20e = new QPushButton(nostoSummaWindow);
        pushButton20e->setObjectName(QString::fromUtf8("pushButton20e"));
        pushButton20e->setGeometry(QRect(90, 170, 83, 29));
        pushButton40e = new QPushButton(nostoSummaWindow);
        pushButton40e->setObjectName(QString::fromUtf8("pushButton40e"));
        pushButton40e->setGeometry(QRect(240, 170, 83, 29));
        pushButton60e = new QPushButton(nostoSummaWindow);
        pushButton60e->setObjectName(QString::fromUtf8("pushButton60e"));
        pushButton60e->setGeometry(QRect(90, 220, 83, 29));
        pushButton100e = new QPushButton(nostoSummaWindow);
        pushButton100e->setObjectName(QString::fromUtf8("pushButton100e"));
        pushButton100e->setGeometry(QRect(240, 230, 83, 29));
        pushButton200e = new QPushButton(nostoSummaWindow);
        pushButton200e->setObjectName(QString::fromUtf8("pushButton200e"));
        pushButton200e->setGeometry(QRect(90, 280, 83, 29));
        pushButton500e = new QPushButton(nostoSummaWindow);
        pushButton500e->setObjectName(QString::fromUtf8("pushButton500e"));
        pushButton500e->setGeometry(QRect(240, 280, 83, 29));
        label = new QLabel(nostoSummaWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 120, 191, 20));
        suljeButton = new QPushButton(nostoSummaWindow);
        suljeButton->setObjectName(QString::fromUtf8("suljeButton"));
        suljeButton->setGeometry(QRect(350, 330, 80, 24));
        label_2 = new QLabel(nostoSummaWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 60, 61, 16));
        tiliLabel = new QLabel(nostoSummaWindow);
        tiliLabel->setObjectName(QString::fromUtf8("tiliLabel"));
        tiliLabel->setGeometry(QRect(170, 60, 111, 16));
        nosto_info = new QLabel(nostoSummaWindow);
        nosto_info->setObjectName(QString::fromUtf8("nosto_info"));
        nosto_info->setGeometry(QRect(90, 140, 281, 20));
        kyhny_info = new QLabel(nostoSummaWindow);
        kyhny_info->setObjectName(QString::fromUtf8("kyhny_info"));
        kyhny_info->setGeometry(QRect(300, 30, 141, 20));
        label_3 = new QLabel(nostoSummaWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(100, 40, 61, 16));
        nimi_label = new QLabel(nostoSummaWindow);
        nimi_label->setObjectName(QString::fromUtf8("nimi_label"));
        nimi_label->setGeometry(QRect(170, 40, 91, 21));

        retranslateUi(nostoSummaWindow);

        QMetaObject::connectSlotsByName(nostoSummaWindow);
    } // setupUi

    void retranslateUi(QWidget *nostoSummaWindow)
    {
        nostoSummaWindow->setWindowTitle(QCoreApplication::translate("nostoSummaWindow", "Form", nullptr));
        pushButton20e->setText(QCoreApplication::translate("nostoSummaWindow", "20", nullptr));
        pushButton40e->setText(QCoreApplication::translate("nostoSummaWindow", "40", nullptr));
        pushButton60e->setText(QCoreApplication::translate("nostoSummaWindow", "60", nullptr));
        pushButton100e->setText(QCoreApplication::translate("nostoSummaWindow", "100", nullptr));
        pushButton200e->setText(QCoreApplication::translate("nostoSummaWindow", "200", nullptr));
        pushButton500e->setText(QCoreApplication::translate("nostoSummaWindow", "500", nullptr));
        label->setText(QCoreApplication::translate("nostoSummaWindow", "Valitse nostettava summa", nullptr));
        suljeButton->setText(QCoreApplication::translate("nostoSummaWindow", "Peruuta", nullptr));
        label_2->setText(QCoreApplication::translate("nostoSummaWindow", "Tilinumero", nullptr));
        tiliLabel->setText(QCoreApplication::translate("nostoSummaWindow", "tilinumero t\303\244h\303\244", nullptr));
        nosto_info->setText(QString());
        kyhny_info->setText(QString());
        label_3->setText(QCoreApplication::translate("nostoSummaWindow", "Asiakas", nullptr));
        nimi_label->setText(QCoreApplication::translate("nostoSummaWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nostoSummaWindow: public Ui_nostoSummaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOSTOSUMMAWINDOW_H
