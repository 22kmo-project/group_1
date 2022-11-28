#ifndef BANKWINDOW_H
#define BANKWINDOW_H

#include <QObject>
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

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

private:
    Ui::bankwindow *ui;
    QByteArray webToken;
    QString myCard;

    QNetworkAccessManager *cardManager;
    QNetworkAccessManager *pinManager;
    QNetworkReply *reply;
    QByteArray response_data;



};

#endif // BANKWINDOW_H
