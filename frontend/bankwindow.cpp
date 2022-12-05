#include "bankwindow.h"
#include "ui_bankwindow.h"
#include "url.h"
#include "nostosummawindow.h"


bankwindow::bankwindow(QString cardNumber,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bankwindow)
{

    ui->setupUi(this);
    ui->labelLocked->hide();
    //ui->labelAccount->setText(cardNumber);
    myCard=cardNumber;

    QString site_url=url::getBaseUrl()+"cards/"+myCard;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    dataManager = new QNetworkAccessManager(this);

    connect(dataManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(dataSlot(QNetworkReply*)));
    reply = dataManager->get(request);
}

bankwindow::~bankwindow()
{
    delete ui;
    delete objectnostoSummaWindow;
    objectnostoSummaWindow=nullptr;
    delete objectsaldoWindow;
    objectsaldoWindow=nullptr;
    delete objecttapahtumaWindow;
    objecttapahtumaWindow=nullptr;
}

void bankwindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
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
    objecttapahtumaWindow = new tapahtumaWindow(webToken,myCard);
    objecttapahtumaWindow->show();
    this->close();
}

void bankwindow::dataSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<"response data in dataslot, bankwindow.cpp: " << response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString omistaja = json_obj["card_owner"].toString();
    ui->labelOmistaja->setText(omistaja);
    qDebug()<<"omistaja: " <<omistaja;

    if (omistaja == "LOCKED") {
        ui->labelLocked->show();
        ui->labelLocked->document()->setPlainText("KORTTI LUKITTU\n👁👅👁");
        delay();
        this->close();
    }

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
void bankwindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
