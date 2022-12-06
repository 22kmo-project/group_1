#include "nostosummawindow.h"
#include "ui_nostosummawindow.h"
#include "url.h"




nostoSummaWindow::nostoSummaWindow(QByteArray token, QString myCard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nostoSummaWindow)
{


    ui->setupUi(this);
    webToken=token;
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
    QString id_account=QString::number(json_obj["id_account"].toInt());


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

void nostoSummaWindow::balanceSlot(QNetworkReply *reply)
{

    QByteArray response_data=reply->readAll();
    qDebug()<<response_data; //toimii tuo tietokannasta tiedot
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString balance=QString::number(json_obj["debit_balance"].toDouble());
    qDebug()<<"balance on:" << balance;
    ui->kyhny_info->setText("Massia jäljellä: "+balance);

    reply->deleteLater();
        balanceManager->deleteLater();


}



void nostoSummaWindow::on_pushButton20e_clicked()
{

    qDebug()<<"20e";
    countMoney(SaldoValue,20);


}


void nostoSummaWindow::on_pushButton40e_clicked()
{
    qDebug()<<"40e";
    countMoney(SaldoValue,40);
}


void nostoSummaWindow::on_pushButton60e_clicked()
{
    qDebug()<<"60e";
    countMoney(SaldoValue,60);
}


void nostoSummaWindow::on_pushButton100e_clicked()
{
    qDebug()<<"100e";
    countMoney(SaldoValue,100);
}


void nostoSummaWindow::on_pushButton200e_clicked()
{
    qDebug()<<"200e";
    countMoney(SaldoValue,200);
}


void nostoSummaWindow::on_pushButton500e_clicked()
{
    qDebug()<<"500e";
    countMoney(SaldoValue,500);

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
        ui->kuittiButton->show();
    }
}



void nostoSummaWindow::on_kuittiButton_clicked()
{
    objectkuittiwindow = new kuittiwindow();
    objectkuittiwindow->show();
}

