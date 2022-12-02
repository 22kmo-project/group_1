#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "url.h"
#include "nostosummawindow.h"


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
    delete objectnostoSummaWindow;
    objectnostoSummaWindow=nullptr;
}

void bankwindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void bankwindow::checkAccount(QString cardnum)
{
    QString site_url=url::getBaseUrl()+"cards"+cardnum;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    dataManager = new QNetworkAccessManager(this);

    connect(dataManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(dataSlot(QNetworkReply*)));

    reply = dataManager->get(request);
}

void bankwindow::on_saldoButton_clicked()
{
    qDebug () << "saldo";
    objectsaldoWindow = new saldoWindow(webToken,myCard);
    objectsaldoWindow->show();
    this->close();
}


void bankwindow::on_tapahtumaButton_clicked()
{
    qDebug () << "tapahtuma";
}

void bankwindow::dataSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    reply->deleteLater();
    dataManager->deleteLater();
}

void bankwindow::openNostoSummaWindow() //nosto nappii
{

    //iNostoSummaWindow = new nostoSummaWindow();
    //iNostoSummaWindow->show();
}

void bankwindow::on_nostoButton_clicked() // nosto nappii
{
    qDebug () << "nosto";
    objectnostoSummaWindow =new nostoSummaWindow(webToken, myCard);
    objectnostoSummaWindow->show();
    this->close();
}


void bankwindow::on_kirjauduUlosButton_clicked()
{
    qDebug () << "kirjaudu ulos";
    this->close();
}
