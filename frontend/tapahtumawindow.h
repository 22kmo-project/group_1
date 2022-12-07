#ifndef TAPAHTUMAWINDOW_H
#define TAPAHTUMAWINDOW_H
#include <QtNetwork>
#include <QWidget>
#include <QTableWidget>
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
    explicit tapahtumaWindow(QByteArray token,QString myCard,QWidget *parent = nullptr);
    ~tapahtumaWindow();
    void setWebToken(const QByteArray &newWebToken);

private slots:
    void on_closeButton_clicked();
    void tapahtumaSlot(QNetworkReply *reply);
    void asiakasSlot(QNetworkReply *reply);
    void on_backwardButton_clicked(bool checked);
    void on_forwardButton_clicked(bool checked);

private:
    QTableWidget* m_pTableWidget;
    QStringList m_TableHeader;
    Ui::tapahtumaWindow *ui;
    QString card_number;
    QByteArray webToken;
    QNetworkAccessManager *tapahtumaManager;
    QNetworkAccessManager *asiakasManager;
    QByteArray response_data;
    QNetworkReply *reply;
    QString lista;
    int rows = 0;
    int positives = 0;
    int increment = 10;
    int overTen = 0;
};

#endif // TAPAHTUMAWINDOW_H
