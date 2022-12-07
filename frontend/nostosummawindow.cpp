#include "nostosummawindow.h"
#include "ui_nostosummawindow.h"
#include "url.h"




nostoSummaWindow::nostoSummaWindow(QByteArray token, QString myCard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nostoSummaWindow)
{


    ui->setupUi(this);
    webToken=token;
    cardnum=myCard;
    QString site_url=url::getBaseUrl()+"cards/"+myCard;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    nostoManager = new QNetworkAccessManager(this);

    connect(nostoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nostoSlot(QNetworkReply*)));

    reply = nostoManager->get(request);
    qDebug()<<"Tilinumero on:" << myCard;
    ui->tiliLabel->setText(myCard);
    ui->kuittiButton->hide();
// Tämä toimii oikein hienosti
}


nostoSummaWindow::~nostoSummaWindow()
{
    delete ui;

}

void nostoSummaWindow::nostoSlot(QNetworkReply *reply)

{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data; //toimii tuo tietokannasta tiedot
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString omistaja=json_obj["card_owner"].toString();
    QString Saldo=QString::number(json_obj["debit_balance"].toDouble());
    id_account=QString::number(json_obj["id_account"].toInt());


    qDebug()<<Saldo;

    ui->nimi_label->setText(omistaja);
    qDebug()<<"Omistajan nimi on:" << omistaja;  //omistaja toimii
    QString site_url=url::getBaseUrl()+"accounts/"+id_account;
    QNetworkRequest request((site_url));
       qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU

    balanceManager = new QNetworkAccessManager(this);
    connect(balanceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(balanceSlot(QNetworkReply*)));
    reply = balanceManager->get(request);

  }

void nostoSummaWindow::balanceSlot(QNetworkReply *reply) // Tämä toimii, kertoo paljo on massia
{

    QByteArray response_data=reply->readAll();
    qDebug()<<response_data; //toimii tuo tietokannasta tiedot
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    balance=QString::number(json_obj["debit_balance"].toDouble());
    qDebug()<<"balance on:" << balance;
    ui->kyhny_info->setText("Massia jäljellä: "+balance);

    //reply->deleteLater();
       // balanceManager->deleteLater();

}

void nostoSummaWindow::updateSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    reply->deleteLater();
    updateManager->deleteLater();
}



void nostoSummaWindow::on_pushButton20e_clicked()
{

    qDebug()<<"20e";
    nosto=balance.toDouble();
    countMoney(nosto,20);
    qDebug()<<nosto;


}


void nostoSummaWindow::on_pushButton40e_clicked()
{
    qDebug()<<"40e";
    nosto=balance.toDouble();
    countMoney(nosto,40);
    qDebug()<<nosto;;
}


void nostoSummaWindow::on_pushButton60e_clicked()
{
    qDebug()<<"60e";
    nosto=balance.toDouble();
    countMoney(nosto,60);
    qDebug()<<nosto;
}


void nostoSummaWindow::on_pushButton100e_clicked()
{
    qDebug()<<"100e";
    nosto=balance.toDouble();
    countMoney(nosto,100);
    qDebug()<<nosto;
}


void nostoSummaWindow::on_pushButton200e_clicked()
{
    qDebug()<<"200e";
    nosto=balance.toDouble();
    countMoney(nosto,200);
    qDebug()<<nosto;
}


void nostoSummaWindow::on_pushButton500e_clicked()
{
    qDebug()<<"500e";
    nosto=balance.toDouble();
    countMoney(nosto,500);
    qDebug()<<nosto;

}

void nostoSummaWindow::on_suljeButton_clicked()
{
    qDebug () << "sulje";
    this->close();

}

void nostoSummaWindow::countMoney(double x, double amount)    //tämä funktio tarkistaa onko tilillä katetta
{

    if(x<amount) // x muuttuja on oma saldo ja amount on nostettava summa
    {
        ui->nosto_info->setText("Tilillä ei riittävästi katetta.");
    }
    else
    {
        x=x-amount;
        ui->nosto_info->setText("Nosto onnistui");
        //tästä alkaa juttelu tietokantaan
        QJsonObject jsonObj;
        jsonObj.insert("debit_balance",x);

        QString site_url=url::getBaseUrl()+"/accounts/"+id_account;
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(webToken));
        //WEBTOKEN LOPPU

        updateManager = new QNetworkAccessManager(this);
        connect(updateManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateSlot(QNetworkReply*)));

        reply = updateManager->put(request, QJsonDocument(jsonObj).toJson());
        //tähän loppuu juttelu tietokantaan, viimeistelee juttelun updateSlotissa.


        balance = QString::number(x);
        ui->kyhny_info->setText("Massia jäljellä: " +balance);

        ui->kuittiButton->show();
    }

}



void nostoSummaWindow::on_kuittiButton_clicked()
{
    objectkuittiwindow = new kuittiwindow(webToken, cardnum);
    objectkuittiwindow->show();
}

