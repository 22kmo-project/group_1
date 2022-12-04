#include "saldowindow.h"
#include "ui_saldowindow.h"
#include "url.h"

saldoWindow::saldoWindow(QByteArray wt,QString cardnum,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saldoWindow)
{
    ui->setupUi(this);

    wt=webToken;
    cardnum=card_number;
    QString site_url=url::getBaseUrl()+"cards/"+card_number;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    saldoManager = new QNetworkAccessManager(this);

    connect(saldoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(saldoSlot(QNetworkReply*)));
    reply = saldoManager->get(request);
}

saldoWindow::~saldoWindow()
{
    delete ui;
}

void saldoWindow::saldoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data; //toimii tuo tietokannasta tiedot
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString tiedot;
    foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           tiedot+="Asiakas: "+json_obj["card_owner"].toString()+" ,\n Kortin numero: "+QString::number(json_obj["card_number"].toInt())+" ,\n Tilin numero: "+
                           QString::number(json_obj["id_account"].toInt())+" ,\n Debit/Credit: "+json_obj["debit_credit"].toString();
    }
    ui->labelAsiakas->setText(tiedot);

    reply->deleteLater();
    saldoManager->deleteLater();
    QString site_url=url::getBaseUrl()+"accounts/1";
        qDebug()<<site_url;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    asiakasManager = new QNetworkAccessManager(this);
    connect(asiakasManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(asiakasSlot(QNetworkReply*)));
    reply = asiakasManager->get(request);
}

void saldoWindow::asiakasSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString Saldo=QString::number(json_obj["debit_balance"].toDouble());
    qDebug()<<Saldo;
    ui->labelSaldo->setText("Saldo: "+Saldo);

    QString site_url=url::getBaseUrl()+"transactions/1";
        qDebug()<<site_url;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    tapahtumaManager = new QNetworkAccessManager(this);
    connect(tapahtumaManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tapahtumaSlot(QNetworkReply*)));
    reply = tapahtumaManager->get(request);


}

void saldoWindow::tapahtumaSlot(QNetworkReply *reply) {
    QByteArray response_data=reply->readAll();
        qDebug()<<response_data;
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();
        QString tapahtuma;
        foreach (const QJsonValue &value, json_array) {
               QJsonObject json_obj = value.toObject();
               tapahtuma+="Asiakas: "+json_obj["card_owner"].toString()+" ,\n Kortin numero: "+QString::number(json_obj["card_number"].toInt())+" ,\n Tilin numero: "+
                               QString::number(json_obj["id_account"].toInt())+" ,\n Debit/Credit: "+json_obj["debit_credit"].toString();
        }
        qDebug()<<tapahtuma;
        ui->labelTapahtuma->setText("tapahtumat: " + tapahtuma);



    reply->deleteLater();
    tapahtumaManager->deleteLater();
}

void saldoWindow::on_suljeButton_clicked()
{
    this->close();
}

