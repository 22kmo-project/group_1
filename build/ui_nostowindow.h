/********************************************************************************
** Form generated from reading UI file 'nostowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOSTOWINDOW_H
#define UI_NOSTOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nostoWindow
{
public:

    void setupUi(QWidget *nostoWindow)
    {
        if (nostoWindow->objectName().isEmpty())
            nostoWindow->setObjectName(QString::fromUtf8("nostoWindow"));
        nostoWindow->resize(400, 300);

        retranslateUi(nostoWindow);

        QMetaObject::connectSlotsByName(nostoWindow);
    } // setupUi

    void retranslateUi(QWidget *nostoWindow)
    {
        nostoWindow->setWindowTitle(QCoreApplication::translate("nostoWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nostoWindow: public Ui_nostoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOSTOWINDOW_H
