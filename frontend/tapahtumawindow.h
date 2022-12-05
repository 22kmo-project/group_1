#ifndef TAPAHTUMAWINDOW_H
#define TAPAHTUMAWINDOW_H
#include <QtNetwork>
#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonDocument>
#include "url.h"

namespace Ui {
class tapahtumaWindow;
}

class tapahtumaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit tapahtumaWindow(QByteArray wt,QString myCard,QWidget *parent = nullptr);
    ~tapahtumaWindow();
    void setWebToken(const QByteArray &newWebToken);

private slots:
    void on_forwardButton_clicked();
    void on_backwardButton_clicked();
    void on_closeButton_clicked();
    void tapahtumaSlot(QNetworkReply *reply);
    void asiakasSlot(QNetworkReply *reply);

private:
    Ui::tapahtumaWindow *ui;
    QByteArray webToken;
    QNetworkAccessManager *tapahtumaManager;
    QNetworkAccessManager *asiakasManager;
    QByteArray response_data;
    QNetworkReply *reply;

};

#endif // TAPAHTUMAWINDOW_H
