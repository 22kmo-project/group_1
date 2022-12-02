#ifndef BANKWINDOW_H
#define BANKWINDOW_H
#include "nostosummawindow.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>
#include <QWidget>
#include "saldowindow.h"


namespace Ui {
class bankwindow;
}

class bankwindow : public QDialog
{
    Q_OBJECT

public:
    explicit bankwindow(QString cardnum,QWidget *parent = nullptr);
    ~bankwindow();

    const QString &getWebToken() const;

    void setWebToken(const QByteArray &newWebToken);

public slots:
    void openNostoSummaWindow();


private slots:

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
    nostoSummaWindow *objectnostoSummaWindow;
    saldoWindow *objectsaldoWindow;
    QNetworkAccessManager *dataManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // BANKWINDOW_H
