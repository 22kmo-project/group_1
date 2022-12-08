#include "kortinvalintawindow.h"
#include "ui_kortinvalintawindow.h"

kortinValintaWindow::kortinValintaWindow(QByteArray token,QString cardNum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::kortinValintaWindow)
{
    ui->setupUi(this);
    kortinValintaWindow::setWindowState(Qt::WindowMaximized);
    cardNumber=cardNum;
    webToken=token;
    qDebug()<<"kortinvalintawindow webtoken"<<webToken;
    qDebug()<<"kortinvalintawindow crdnumber"<<cardNumber;
    QString site_url=url::getBaseUrl()+"cards/"+cardNumber;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    dataManager = new QNetworkAccessManager(this);
    connect(dataManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(dataSlot(QNetworkReply*)));
    reply = dataManager->get(request);
}

kortinValintaWindow::~kortinValintaWindow()
{
    delete ui;
    delete objectBankWindow;
    objectBankWindow=nullptr;
}

void kortinValintaWindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void kortinValintaWindow::dataSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<"response data in dataslot, kortinvalintawindow.cpp: " << response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString kortti = json_obj["debit_credit"].toString();
    qDebug()<<"debit/credit: " <<kortti;

    if (kortti == "debit") {
        credit=false;
        objectBankWindow=new bankwindow(webToken,cardNumber,credit);
        objectBankWindow->setWebToken("Bearer "+response_data);
        objectBankWindow->show();
        this->close();
        }
    reply->deleteLater();
    dataManager->deleteLater();
}

void kortinValintaWindow::on_creditButton_clicked()
{

    qDebug()<<"valittu credit";
    credit=true;
    objectBankWindow=new bankwindow(webToken,cardNumber,credit);
    objectBankWindow->setWebToken("Bearer "+response_data);
    objectBankWindow->show();
    this->close();
}

void kortinValintaWindow::on_debitButton_clicked()
{
    qDebug()<<"valittu debit";
    credit=false;
    objectBankWindow=new bankwindow(webToken,cardNumber,credit);
    objectBankWindow->setWebToken("Bearer "+response_data);
    objectBankWindow->show();
    this->close();
}
