#ifndef KUITTIWINDOW_H
#define KUITTIWINDOW_H
#include <QtNetwork>
#include <QWidget>
#include <QTableWidget>
#include <QDialog>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonDocument>
#include "url.h"

namespace Ui{
class kuittiwindow;
}

class kuittiwindow : public QDialog
{
    Q_OBJECT

public:
    explicit kuittiwindow(QByteArray token,QString cardnum,QWidget *parent = nullptr);
    ~kuittiwindow();
    void setWebToken(const QByteArray &newWebToken);

private slots:
    void kuittiSlot(QNetworkReply *reply);
    void asiakasSlot(QNetworkReply *reply);

private:
    QTableWidget* m_pTableWidget;
    QStringList m_TableHeader;
    Ui::kuittiwindow *ui;
    QString card_number;
    QByteArray webToken;
    QNetworkAccessManager *kuittiManager;
    QNetworkAccessManager *asiakasManager;
    QByteArray response_data;
    QNetworkReply *reply;
    QString lista;
};

#endif // KUITTIWINDOW_H
