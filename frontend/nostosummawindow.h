#ifndef NOSTOSUMMAWINDOW_H
#define NOSTOSUMMAWINDOW_H
#include "url.h"
#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>


namespace Ui {
class nostoSummaWindow;
}

class nostoSummaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit nostoSummaWindow(QByteArray token, QString myCard, QWidget *parent = nullptr);
    ~nostoSummaWindow();
    void setWebToken(const QByteArray &newWebToken);


private slots:
    void on_pushButton20e_clicked();

    void on_pushButton40e_clicked();

    void on_pushButton60e_clicked();

    void on_pushButton100e_clicked();

    void on_pushButton200e_clicked();

    void on_pushButton500e_clicked();

    void nostoSlot (QNetworkReply *reply);

    void balanceSlot (QNetworkReply *reply);

    void on_suljeButton_clicked();

    void countMoney(double balance, double amount);

private:
    Ui::nostoSummaWindow *ui;
    QByteArray webToken;
    double nosto;
    QString balance;
    QNetworkAccessManager *nostoManager;
    QNetworkAccessManager *balanceManager;

    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // NOSTOSUMMAWINDOW_H
