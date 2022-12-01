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
    //ui->nostoSummaLabel->setText("Valitse nostettava summa");

    qDebug()<<webToken;
        QString site_url=url::getBaseUrl()+"/cards/"+cardnum;
        QNetworkRequest request((site_url));
        qDebug()<<site_url;
        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(webToken));
        //WEBTOKEN LOPPU
        nostoManager = new QNetworkAccessManager(this);

        connect(nostoManager, SIGNAL(finished(QNetworkReply)), this, SLOT(dataSlot(QNetworkReply)));

        reply = nostoManager->get(request);
}

nostoSummaWindow::~nostoSummaWindow()
{
    delete ui;
}





void nostoSummaWindow::on_pushButton20e_clicked()
{
    //Saldo muuttuja -20e tyylii. jne..
}


void nostoSummaWindow::on_pushButton40e_clicked()
{

}


void nostoSummaWindow::on_pushButton60e_clicked()
{

}


void nostoSummaWindow::on_pushButton100e_clicked()
{

}


void nostoSummaWindow::on_pushButton200e_clicked()
{

}


void nostoSummaWindow::on_pushButton500e_clicked()
{

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
        QString transaction;
        foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           transaction+="Tapahtuman laji:"+json_obj["tapahtuman laji"].toString()+", päivämäärä:"+json_obj["päivämäärä"].toString()+", summa:"+QString::number(json_obj["summa"].toInt())+"\n";
        }



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

