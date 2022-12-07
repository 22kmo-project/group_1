#ifndef TALLETUSWINDOW_H
#define TALLETUSWINDOW_H
#include "ui_bankwindow.h"
#include "url.h"
#include <QWidget>
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>

namespace Ui {
class talletusWindow;
}

class talletusWindow : public QWidget
{
    Q_OBJECT

public:
    explicit talletusWindow(QByteArray token,QString cardNumber,QWidget *parent = nullptr);
    ~talletusWindow();

private slots:
    void on_talletaButton_clicked();
    void on_peruutaButton_clicked();

    void talletusSlot (QNetworkReply *reply);
    void asiakasSlot (QNetworkReply *reply);
    void saldoSlot (QNetworkReply *reply);
private:
    Ui::talletusWindow *ui;
    QByteArray webToken;
    QString card_number;
    QString account;
    QNetworkAccessManager *asiakasManager;
    QNetworkAccessManager *saldoManager;
    QNetworkAccessManager *talletusManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString sum;
    QString saldo;
    QString uusiSaldo;
    double talletus;
    double x;
};

#endif // TALLETUSWINDOW_H
