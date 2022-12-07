#include "kortinvalintawindow.h"
#include "ui_kortinvalintawindow.h"

kortinValintaWindow::kortinValintaWindow(QByteArray token,QString cardNum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::kortinValintaWindow)
{
    ui->setupUi(this);
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

void kortinValintaWindow::delay()
{
    int afkTimer=30; //afkTimer=30 tarkoittaa 30 sekuntia. Muokkaa lyhyemmäksi kun testailet.
    QTime dieTime= QTime::currentTime().addSecs(afkTimer);
     while (QTime::currentTime() < dieTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
     qDebug()<<"afkTimer 30sec";
     this->close(); //Tähän pitää keksiä järkevä funktio että menee aloitusnäkymään
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
        objectBankWindow=new bankwindow(webToken,cardNumber);
        objectBankWindow->setWebToken("Bearer "+response_data);
        objectBankWindow->show();
        this->close();
        }
    reply->deleteLater();
    dataManager->deleteLater();
    delay();
}

void kortinValintaWindow::on_creditButton_clicked()
{
    qDebug()<<"valittu credit";
    objectBankWindow=new bankwindow(webToken,cardNumber);
    objectBankWindow->setWebToken("Bearer "+response_data);
    objectBankWindow->show();
    this->close();
}

void kortinValintaWindow::on_debitButton_clicked()
{
    qDebug()<<"valittu debit";
    objectBankWindow=new bankwindow(webToken,cardNumber);
    objectBankWindow->setWebToken("Bearer "+response_data);
    objectBankWindow->show();
    this->close();
}
