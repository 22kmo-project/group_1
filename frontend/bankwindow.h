#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>

namespace Ui {
class bankwindow;
}

class bankwindow : public QDialog
{
public:
    explicit bankwindow(QString cardnum,QWidget *parent = nullptr);
    ~bankwindow();

    const QString &getWebToken() const;

    void setWebToken(const QByteArray &newWebToken);

private slots:

    void bankSlot (QNetworkReply *reply);
    void dataSlot (QNetworkReply *reply);


    void on_saldoButton_clicked();

    void on_tapahtumaButton_clicked();

    void on_nostoButton_clicked();

    void on_kirjauduUlosButton_clicked();


private:
    Ui::bankwindow *ui;
    QByteArray webToken;
    QString idAccount;
    QString myCard;

    QNetworkAccessManager *dataManager;
    void checkAccount(QString cardnum);
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // BANKWINDOW_H
