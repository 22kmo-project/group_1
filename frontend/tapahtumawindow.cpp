#include "tapahtumawindow.h"
#include "ui_tapahtumawindow.h"

tapahtumaWindow::tapahtumaWindow(QByteArray wt,QString myCard,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tapahtumaWindow)
{
    ui->setupUi(this);
    wt=webToken;
    card_number = myCard;
    qDebug()<<"OLEMME TÄÄLLÄ " << card_number;
    QString site_url=url::getBaseUrl()+"cards/" + card_number;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    tapahtumaManager = new QNetworkAccessManager(this);

    connect(tapahtumaManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tapahtumaSlot(QNetworkReply*)));
    reply = tapahtumaManager->get(request);

}

tapahtumaWindow::~tapahtumaWindow()
{
    delete ui;
}


void tapahtumaWindow::tapahtumaSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data; //toimii tuo tietokannasta tiedot
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonObject json_obj = json_doc.object();


    QString account = QString::number(json_obj["id_account"].toInt());
    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString debit_credit = json_obj["debit_credit"].toString();
    QString card_owner = json_obj["card_owner"].toString();
    QString lista;
        lista += "Account: " + account + "\nCard number: "+card_number + "\nDebit/Credit: "+debit_credit + "\nCard owner: "+card_owner;


    qDebug()<<"cards data in saldowindow: "<<account<<card_number<<debit_credit<<card_owner;

    ui->labelAsiakas->setText(lista);

    reply->deleteLater();
    tapahtumaManager->deleteLater();
    QString site_url=url::getBaseUrl()+"transactions/1";
    qDebug()<<site_url;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    asiakasManager = new QNetworkAccessManager(this);
    connect(asiakasManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(asiakasSlot(QNetworkReply*)));
    reply = asiakasManager->get(request);
}

void tapahtumaWindow::asiakasSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonObject json_obj = json_doc.object();
    QString id_transactions = QString::number(json_obj["id_transactions"].toInt());
    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString sum = QString::number(json_obj["sum"].toInt());
    QString date = json_obj["date"].toString();
    QString lista;
        lista += "Transaction: " + id_transactions + "\nCard number: "+card_number + "\nSum: "+sum + "\nDAte: "+date;

    qDebug()<<"pöö" <<id_transactions<<card_number<<sum<<date;

    ui->labelTapahtuma->setText(lista);

    reply->deleteLater();
    asiakasManager->deleteLater();
}



void tapahtumaWindow::on_forwardButton_clicked()
{

}


void tapahtumaWindow::on_backwardButton_clicked()
{

}


void tapahtumaWindow::on_closeButton_clicked()
{
    qDebug () << "sulje";
    this->close();
}

