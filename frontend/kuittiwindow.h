#ifndef KUITTIWINDOW_H
#define KUITTIWINDOW_H
#include "url.h"
#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

namespace Ui{
class kuittiwindow;
}

class kuittiwindow : public QDialog
{
    Q_OBJECT

public:
    explicit kuittiwindow();

private:
    Ui::kuittiwindow *ui;
    kuittiwindow *objectkuittiwindow;
};

#endif // KUITTIWINDOW_H
