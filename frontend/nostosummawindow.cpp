#include "nostosummawindow.h"
#include "ui_nostosummawindow.h"
#include "url.h"



nostoSummaWindow::nostoSummaWindow(QByteArray webToken, QString myCard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nostoSummaWindow)
{


    ui->setupUi(this);

    qDebug()<<webToken;
    QString site_url=url::getBaseUrl()+"cards/"+myCard;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    nostoManager = new QNetworkAccessManager(this);

    connect(nostoManager, SIGNAL(finished(QNetworkReply)), this, SLOT(nostoSlot(QNetworkReply)));

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

        QString omistaja = json_obj["card_owner"].toString();
        ui->nimi_label->setText(omistaja);
        qDebug()<<omistaja;


        reply->deleteLater();
        nostoManager->deleteLater();
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


