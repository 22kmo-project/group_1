#include "talletuswindow.h"
#include "ui_talletuswindow.h"

talletusWindow::talletusWindow(QByteArray token,QString cardNumber,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::talletusWindow)
{
    ui->setupUi(this);

    card_number = cardNumber;
    webToken=token;

    QString site_url=url::getBaseUrl()+"cards/"+card_number;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    asiakasManager = new QNetworkAccessManager(this);

    connect(asiakasManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(asiakasSlot(QNetworkReply*)));
    reply = asiakasManager->get(request);
}

talletusWindow::~talletusWindow()
{
    delete ui;
}

void talletusWindow::asiakasSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    account = QString::number(json_obj["id_account"].toInt());
    qDebug()<<"account"<<account;

    QString site_url=url::getBaseUrl()+"accounts/"+account;
        qDebug()<<site_url;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    saldoManager = new QNetworkAccessManager(this);
    connect(saldoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(saldoSlot(QNetworkReply*)));
    reply = saldoManager->get(request);
}

void talletusWindow::saldoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    saldo=QString::number(json_obj["debit_balance"].toDouble());
    qDebug()<<"saldo"<<saldo;
    x = saldo.toDouble();

    ui->talletusLabel->setText("Syötä talletettava määrä");
}

void talletusWindow::on_talletaButton_clicked()
{

    sum=ui->lineEditMaara->text();
    ui->lineEditMaara->clear();
    qDebug()<<"summa"<<sum;
    double y = sum.toDouble();
    talletus=x + y;
    qDebug()<<"talletus"<<talletus;
    QJsonObject jsonObj;
    jsonObj.insert("debit_balance",talletus);
    QString uusiSaldo = QString::number(talletus);
    ui->saldoLabel->setText("Saldo: " + uusiSaldo);
    ui->summaLabel->setText("Talletettu summa: " + sum);
    QString site_url=url::getBaseUrl()+"/accounts/"+account;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU

    talletusManager = new QNetworkAccessManager(this);
    connect(talletusManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(talletusSlot(QNetworkReply*)));

    reply = talletusManager->put(request, QJsonDocument(jsonObj).toJson());

}

void talletusWindow::talletusSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    reply->deleteLater();
    talletusManager->deleteLater();
}

void talletusWindow::on_peruutaButton_clicked()
{
    this->close();
}
