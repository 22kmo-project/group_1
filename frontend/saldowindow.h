#ifndef SALDOWINDOW_H
#define SALDOWINDOW_H
#include "url.h"
#include <QWidget>
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>

namespace Ui {
class saldoWindow;
}

class saldoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit saldoWindow(QByteArray webToken,QString cardNumber,QWidget *parent = nullptr);
    ~saldoWindow();
    void setWebToken(const QByteArray &newWebToken);
private slots:
    void saldoSlot (QNetworkReply *reply);
    void asiakasSlot (QNetworkReply *reply);
    void tapahtumaSlot (QNetworkReply *reply);

    void on_suljeButton_clicked();

private:
    Ui::saldoWindow *ui;
    QByteArray webToken;
    QString card_number;
    QByteArray response_data;
    QNetworkAccessManager *saldoManager;
    QNetworkAccessManager *asiakasManager;
    QNetworkAccessManager *tapahtumaManager;
    QNetworkReply *reply;
};

#endif // SALDOWINDOW_H
