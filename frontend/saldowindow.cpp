#include "saldowindow.h"
#include "ui_saldowindow.h"
#include "url.h"

saldoWindow::saldoWindow(QByteArray webToken,QString cardnum,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saldoWindow)
{
    ui->setupUi(this);
    card_number = cardnum;
    qDebug()<<"card_number in saldo.cpp: "<< card_number;
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
    qDebug()<< "response data: " <<response_data; //toimii tuo tietokannasta tiedot
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonObject json_obj = json_doc.object();
    QString account = QString::number(json_obj["id_account"].toInt());
    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString debit_credit = json_obj["debit_credit"].toString();
    QString card_owner = json_obj["card_owner"].toString();

    QString lista;
    lista += "Account: " + account + "\nCard number: "+card_number + "\nDebit/Credit: "+debit_credit + "\nCard owner: "+card_owner;
    qDebug()<<"cards data in saldowindow: "<<card_number<<debit_credit<<card_owner;
    qDebug()<<"id_account in saldowindow: "<<account;
    ui->labelAsiakas->setText(lista);

    reply->deleteLater();
    saldoManager->deleteLater();
    QString site_url=url::getBaseUrl()+"accounts/"+account;
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
    QString account;
    account = QString::number(json_obj["id_account"].toInt());
    qDebug()<<Saldo;
    ui->labelSaldo->setText("Saldo: "+Saldo);

    QString site_url=url::getBaseUrl()+"transactions/"+account;
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
    QJsonObject json_obj = json_doc.object();
    QString tiedot;
    QString account;

    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString debit_credit = json_obj["debit_credit"].toString();
    QString card_owner = json_obj["card_owner"].toString();

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        tiedot+="id_transactions: "+QString::number(json_obj["id_transactions"].toInt())+",\nKortin numero: "+QString::number(json_obj["card_number"].toInt())+",\nsum: "+
        QString::number(json_obj["sum"].toInt())+",\ndate: "+json_obj["date"].toString() +",\n";
    }
    qDebug()<<"pöö" <<tiedot;
    ui->labelTapahtuma->setText(tiedot);
    reply->deleteLater();
    tapahtumaManager->deleteLater();
}

void saldoWindow::on_suljeButton_clicked()
{
    this->close();
}

