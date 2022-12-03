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

    ui->tiliLabel->setText(myCard);     //tämä on tilinumero
    ui->nimi_label->setText(clientName); //tämä on tilin omistajan nimi


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
        myAccountId=QString::number(json_obj["id_customer"].toInt());

        clientName=json_obj["client_name"].toString();
        balance=QString::number(json_obj["balance"].toDouble());
        balanceValue=QString(balance).toDouble();
        //ui->tiliLabel->setText(myAccountId);


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
    countMoney(balanceValue,20);

}


void nostoSummaWindow::on_pushButton40e_clicked()
{
    qDebug()<<"40e";
    countMoney(balanceValue,40);
}


void nostoSummaWindow::on_pushButton60e_clicked()
{
    qDebug()<<"60e";
    countMoney(balanceValue,60);
}


void nostoSummaWindow::on_pushButton100e_clicked()
{
    qDebug()<<"100e";
    countMoney(balanceValue,100);
}


void nostoSummaWindow::on_pushButton200e_clicked()
{
    qDebug()<<"200e";
    countMoney(balanceValue,200);
}


void nostoSummaWindow::on_pushButton500e_clicked()
{
    qDebug()<<"500e";
    countMoney(balanceValue,500);

}

void nostoSummaWindow::on_suljeButton_clicked()
{
    qDebug () << "sulje";
    this->close();

}

void nostoSummaWindow::countMoney(double balance, double amount)    //tämä funktio tarkistaa onko tilillä katetta
{
    if(balance<amount)
    {
        ui->nosto_info->setText("Tilillä ei riittävästi katetta.");
    }
    else
    {
        balance=balance-amount;
        ui->nosto_info->setText("Nosto onnistui");
        QString balanceAsString = QString::number(balance);
        ui->kyhny_info->setText("Massia jäljellä: " +balanceAsString);
    }
}


