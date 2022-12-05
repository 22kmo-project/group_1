#include "tapahtumawindow.h"
#include "ui_tapahtumawindow.h"

tapahtumaWindow::tapahtumaWindow(QByteArray wt,QString myCard,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tapahtumaWindow)
{
    ui->setupUi(this);
    wt=webToken;
    qDebug()<<"OLEMME TÄÄLLÄ " << myCard;
    QString site_url=url::getBaseUrl()+"cards/" + myCard;
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
    QString tiedot;
    QString account;

    foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           tiedot+="Asiakas: "+json_obj["card_owner"].toString()+" ,\n Kortin numero: "+QString::number(json_obj["card_number"].toInt())+" ,\n Tilin numero: "+
                           QString::number(json_obj["id_account"].toInt())+" ,\n Debit/Credit: "+json_obj["debit_credit"].toString();
            account = QString::number(json_obj["id_account"].toInt());
    }

    qDebug()<<"cards data in tapahtumawindow: " <<tiedot;
    qDebug()<<"id_account in tapahtumawindow: " <<account;
    //ui->labelAsiakas->setText(tiedot);

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
    QString tiedot;

    foreach (const QJsonValue &value, json_array) {
           QJsonObject json_obj = value.toObject();
           tiedot+="id_transactions: "+QString::number(json_obj["id_transactions"].toInt())+",\nKortin numero: "+QString::number(json_obj["card_number"].toInt())+",\nsum: "+
                           QString::number(json_obj["sum"].toInt())+",\ndate: "+json_obj["date"].toString() +",\n";
    }
    qDebug()<<"pöö" <<tiedot;

    ui->labelTapahtuma->setText(tiedot);

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

