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
    explicit nostoSummaWindow(QByteArray wt, QString cardnum, QWidget *parent = nullptr);
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

private:
    Ui::nostoSummaWindow *ui;
    QByteArray webToken;
    QString myCard;
    QString myAccountId;
    QString clientName;
    QString balance;
    double balanceValue;
    QNetworkAccessManager *nostoManager;
    QNetworkAccessManager *balanceManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // NOSTOSUMMAWINDOW_H
