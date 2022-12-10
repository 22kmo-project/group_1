#include "saldowindow.h"
#include "ui_saldowindow.h"
#include "url.h"
#include "bankwindow.h"

saldoWindow::saldoWindow(QByteArray token,QString cardnum,bool cardType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saldoWindow)
{
    ui->setupUi(this);
    saldoWindow::setWindowState(Qt::WindowMaximized);
    card_number = cardnum;
    webToken=token;
    ui->timer->setPalette(Qt::red);
    ui->timer->setAutoFillBackground(true);
    QPalette Pal = ui->timer->palette();
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    ui->timer->setPalette(Pal);
    if(cardType==true)//debit käytössä = false , credit käytössä = true
    {
        credit=true;
    }
    else
    {
        credit=false;
    }
    QString site_url=url::getBaseUrl()+"cards/"+card_number;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    saldoManager = new QNetworkAccessManager(this);
    connect(saldoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(saldoSlot(QNetworkReply*)));
    reply = saldoManager->get(request);

}

saldoWindow::~saldoWindow()
{
    delete ui;
}

void saldoWindow::delay()
{
    int afkTimer=1;
    QTime dieTime= QTime::currentTime().addSecs(afkTimer);
     while (QTime::currentTime() < dieTime) {
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
     }
}
void saldoWindow::saldoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString account = QString::number(json_obj["id_account"].toInt());
    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString debit_credit = json_obj["debit_credit"].toString();
    QString card_owner = json_obj["card_owner"].toString();
    QString lista;

    lista += "Account: " + account + "\nCard number: "+card_number + "\nDebit/Credit: "+debit_credit + "\nCard owner: "+card_owner;
    ui->labelAsiakas->setText(lista);
    reply->deleteLater();
    saldoManager->deleteLater();

    QString site_url=url::getBaseUrl()+"accounts/"+account;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    asiakasManager = new QNetworkAccessManager(this);
    connect(asiakasManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(asiakasSlot(QNetworkReply*)));
    reply = asiakasManager->get(request);

    for (int i = 10; i >= 0; i--) {
        delay();
        ui->timer->display(i);

        if (i == 0&& this->isHidden()==false) {
            bankwindow *bank = new bankwindow(webToken,card_number,credit);
            bank->show();
            close();
        }
    }
}

void saldoWindow::asiakasSlot(QNetworkReply *reply)
{
    if(credit==false){
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString Saldo=QString::number(json_obj["debit_balance"].toDouble());
    QString account;
    account = QString::number(json_obj["id_account"].toInt());
    ui->labelSaldo->setText("Saldo: "+Saldo);
    QString site_url=url::getBaseUrl()+"transactions/"+account;
    QNetworkRequest request((site_url));
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    tapahtumaManager = new QNetworkAccessManager(this);
    connect(tapahtumaManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tapahtumaSlot(QNetworkReply*)));
    reply = tapahtumaManager->get(request);}
    else{
        QByteArray response_data=reply->readAll();
        qDebug()<<response_data;
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();
        QString creditLimit=QString::number(json_obj["credit_limit"].toDouble());
        QString usedCredit=QString::number(json_obj["used_credit"].toDouble());
        QString account;
        account = QString::number(json_obj["id_account"].toInt());
        ui->labelSaldo->setText("Luottoraja: "+creditLimit+"\n"+"Käytetty luotto: "+usedCredit);
        QString site_url=url::getBaseUrl()+"transactions/"+account;

        QNetworkRequest request((site_url));
        request.setRawHeader(QByteArray("Authorization"),(webToken));
        tapahtumaManager = new QNetworkAccessManager(this);
        connect(tapahtumaManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tapahtumaSlot(QNetworkReply*)));
        reply = tapahtumaManager->get(request);
    }
}

void saldoWindow::tapahtumaSlot(QNetworkReply *reply) {
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString id_transactions = QString::number(json_obj["id_transactions"].toInt());
    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString sum = QString::number(json_obj["sum"].toInt());
    QString date = json_obj["date"].toString();
    QString lista;

    lista += "Transaction: " + id_transactions + "\nCard number: "+card_number + "\nSum: "+sum + "\nDate: "+date;
    ui->labelTapahtuma->setText(lista);
    reply->deleteLater();
    tapahtumaManager->deleteLater();

}

void saldoWindow::on_suljeButton_clicked()
{
    bankwindow *bank = new bankwindow(webToken, card_number,credit);
    bank->show();
    close();
}
