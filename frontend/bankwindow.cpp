#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "url.h"

bankwindow::bankwindow(QString cardNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bankwindow)
{
    ui->setupUi(this);
    ui->labelAccount->setText(cardNumber);
    myCard=cardNumber;
}

bankwindow::~bankwindow()
{
    delete ui;
}

void bankwindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void bankwindow::checkAccount(QString cardnum)
{
    qDebug()<<webToken;
    QString site_url=url::getBaseUrl()+"/cards/"+cardnum;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    dataManager = new QNetworkAccessManager(this);

    connect(dataManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(dataSlot(QNetworkReply*)));

    reply = dataManager->get(request);
}


void bankwindow::dataSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"dataslot response data"<<response_data;
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
    }

    reply->deleteLater();
    dataManager->deleteLater();
}

