#ifndef NOSTOSUMMAWINDOW_H
#define NOSTOSUMMAWINDOW_H

#include <QWidget>
#include <QObject>
#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>


namespace Ui {
class nostoSummaWindow;
}

class nostoSummaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit nostoSummaWindow(QByteArray webToken, QString myCard, QString idAccount,  QWidget *parent = nullptr);
    const QString &getWebToken() const;
    ~nostoSummaWindow();


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
    QString myCard="66456535303353"; //kovakoodattu että voi testata, saa poistaa
    QString idAccount;
    QString clientName; //kovakoodattu että voi testata, saa poistaa
    QString balance;
    double balanceValue=400; //kovakoodattu että voi testata, saa poistaa
    QNetworkAccessManager *nostoManager;
    QNetworkAccessManager *balanceManager;
    QNetworkReply *reply;
    QByteArray response_data;

};

#endif // NOSTOSUMMAWINDOW_H
