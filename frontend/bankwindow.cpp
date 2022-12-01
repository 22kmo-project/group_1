#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "url.h"

bankwindow::bankwindow(QString cardNumber, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bankwindow)
{

    ui->setupUi(this);
    ui->label->setText(cardNumber);
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

void bankwindow::on_saldoButton_clicked()
{
    qDebug () << "saldo";
}


void bankwindow::on_tapahtumaButton_clicked()
{
    qDebug () << "tapahtuma";
}


void bankwindow::on_nostoButton_clicked()
{
    qDebug () << "nosto";
}


void bankwindow::on_kirjauduUlosButton_clicked()
{
    qDebug () << "kirjaudu ulos";
}

