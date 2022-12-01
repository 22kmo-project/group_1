#include "nostosummawindow.h"
#include "ui_nostosummawindow.h"
#include "url.h"

nostoSummaWindow::nostoSummaWindow(QByteArray wt, QString cardnum, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nostoSummaWindow)
{
    wt=webToken;
    cardnum=myCard;
    ui->setupUi(this);

    qDebug()<<webToken;
    QString site_url=url::getBaseUrl()+"cards"+cardnum;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    nostoManager = new QNetworkAccessManager(this);

    connect(nostoManager, SIGNAL(finished(QNetworkReply)), this, SLOT(bankSlot(QNetworkReply)));

    reply = nostoManager->get(request);
}

nostoSummaWindow::~nostoSummaWindow()
{
    delete ui;
}

void nostoSummaWindow::nostoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
        qDebug()<<response_data;
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();

        myCard=QString::number(json_obj["id_client"].toInt());
        myAccountId=QString::number(json_obj["id_account"].toInt());

        clientName=json_obj["client_name"].toString();
        balance=QString::number(json_obj["balance"].toDouble());
        balanceValue=QString(balance).toDouble();


        reply->deleteLater();
        nostoManager->deleteLater();
}

void nostoSummaWindow::balanceSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
        qDebug()<<response_data;
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();

        reply->deleteLater();
        balanceManager->deleteLater();

        QString site_url=url::getBaseUrl()+"/account/"+myCard;
        QNetworkRequest request((site_url));
        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(webToken));
        //WEBTOKEN LOPPU
        balanceManager = new QNetworkAccessManager(this);
        connect(balanceManager, SIGNAL(finished(QNetworkReply)), this, SLOT(clientSlot(QNetworkReply)));
        reply = balanceManager->get(request);
}

void nostoSummaWindow::on_pushButton20e_clicked()
{
    qDebug()<<"20e";
}


void nostoSummaWindow::on_pushButton40e_clicked()
{
    qDebug()<<"40e";
}


void nostoSummaWindow::on_pushButton60e_clicked()
{
    qDebug()<<"60e";
}


void nostoSummaWindow::on_pushButton100e_clicked()
{
    qDebug()<<"100e";
}


void nostoSummaWindow::on_pushButton200e_clicked()
{
    qDebug()<<"200e";
}


void nostoSummaWindow::on_pushButton500e_clicked()
{
    qDebug()<<"500e";
}

