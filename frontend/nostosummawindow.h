#ifndef NOSTOSUMMAWINDOW_H
#define NOSTOSUMMAWINDOW_H
#include "url.h"
#include "kuittiwindow.h"
#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QMovie>
#include <QTimer>


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
public slots:
    void close_window();
private slots:
    void on_pushButton20e_clicked();
    void on_pushButton40e_clicked();
    void on_pushButton60e_clicked();
    void on_pushButton100e_clicked();
    void on_pushButton200e_clicked();
    void on_pushButton500e_clicked();
    void nostoSlot (QNetworkReply *reply);
    void balanceSlot (QNetworkReply *reply);
    void updateSlot (QNetworkReply *reply);
    void on_suljeButton_clicked();
    void delay();
    void countMoney(double balance, double amount);
    void on_kuittiButton_clicked();
    void on_muuButton_clicked();
    void on_confirmButton_clicked();
private:
    Ui::nostoSummaWindow *ui;
    QByteArray webToken;
    double nosto;
    QString balance;
    QString cardnum;
    QNetworkAccessManager *nostoManager;
    QNetworkAccessManager *balanceManager;
    QNetworkAccessManager *updateManager;
    QString id_account;
    QNetworkReply *reply;
    QByteArray response_data;
    kuittiwindow *objectkuittiwindow;
    int aika;
};
#endif // NOSTOSUMMAWINDOW_H
