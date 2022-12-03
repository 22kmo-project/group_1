/********************************************************************************
** Form generated from reading UI file 'tapahtumawindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAPAHTUMAWINDOW_H
#define UI_TAPAHTUMAWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tapahtumaWindow
{
public:
    QLabel *label;

    void setupUi(QWidget *tapahtumaWindow)
    {
        if (tapahtumaWindow->objectName().isEmpty())
            tapahtumaWindow->setObjectName(QString::fromUtf8("tapahtumaWindow"));
        tapahtumaWindow->resize(400, 300);
        label = new QLabel(tapahtumaWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 70, 171, 20));

        retranslateUi(tapahtumaWindow);

        QMetaObject::connectSlotsByName(tapahtumaWindow);
    } // setupUi

    void retranslateUi(QWidget *tapahtumaWindow)
    {
        tapahtumaWindow->setWindowTitle(QCoreApplication::translate("tapahtumaWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("tapahtumaWindow", "TILITAPAHTUMAT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class tapahtumaWindow: public Ui_tapahtumaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAPAHTUMAWINDOW_H
