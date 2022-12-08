#include "bankwindow.h"
#include "mainwindow.h"
#include "ui_bankwindow.h"
#include "url.h"
#include "nostosummawindow.h"

bankwindow::bankwindow(QByteArray webToken,QString cardNumber,bool credit,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bankwindow)
{
    ui->setupUi(this);
    ui->labelLocked->hide();

    ui->timer->setPalette(Qt::red);

    ui->timer->setAutoFillBackground(true);
    QPalette Pal = ui->timer->palette();
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::black);
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::red);
    ui->timer->setPalette(Pal);

    qDebug()<<"kortti on"<<credit;
    if(credit==true)
    {
        cardType=true;
        ui->talletusButton->hide();
    }
    else
    {
        cardType=false;
    }
    qDebug()<<"cardtype"<<cardType;
    myCard=cardNumber;
    token = webToken;
    qDebug()<<"constru webtoken"<<token;
    qDebug()<<"constru crdnumber"<<myCard;
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
    token = newWebToken;
}

void bankwindow::on_saldoButton_clicked()
{
    qDebug () << "saldo";
    objectsaldoWindow = new saldoWindow(token,myCard);
    objectsaldoWindow->show();
    this->close();
}

void bankwindow::on_tapahtumaButton_clicked()
{
    qDebug () << "tapahtuma";
    objecttapahtumaWindow = new tapahtumaWindow(token,myCard);
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
    QString cardType = json_obj["debit_credit"].toString();

    ui->labelOmistaja->setText(omistaja);
    qDebug()<<"omistaja: " <<omistaja;
    qDebug()<<"kortti: " <<cardType;
    if (omistaja == "LOCKED") {
        ui->labelOmistaja->hide();
        ui->labelAccount->hide();
        ui->labelCredit->hide();
        ui->kirjauduUlosButton->hide();
        ui->nostoButton->hide();
        ui->saldoButton->hide();
        ui->tapahtumaButton->hide();
        ui->labelLocked->show();
        for (int i = 3; i >= 0;i--) {
            QString info = "KORTTI LUKITTU\nOhjelma suljetaan "+ QString::number(i) +" kuluttua...";
            ui->labelLocked->document()->setPlainText(info);
            delay();
        }
        this->close();
    }
    reply->deleteLater();
    dataManager->deleteLater();
    for (int i = 30; i >= 0; i--) {
        delay30s();
        ui->timer->display(i);
    }
    MainWindow *main = new MainWindow;
    main->show();
    close();

}

void bankwindow::openNostoSummaWindow() //nosto nappii
{

    //iNostoSummaWindow = new nostoSummaWindow();
    //iNostoSummaWindow->show();
}

void bankwindow::on_nostoButton_clicked() // nosto nappii
{
    qDebug () << "nosto";
    objectnostoSummaWindow =new nostoSummaWindow(token, myCard,cardType);
    objectnostoSummaWindow->show();
    this->close();
}

void bankwindow::on_kirjauduUlosButton_clicked()
{
    MainWindow *main = new MainWindow;
    main->show();
    close();
}
void bankwindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void bankwindow::delay30s()
{
    int afkTimer=1;
    QTime dieTime= QTime::currentTime().addSecs(afkTimer);
     while (QTime::currentTime() < dieTime) {
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
     }
}

void bankwindow::on_talletusButton_clicked()
{
    qDebug () << "talleta";
    objecttalletusWindow =new talletusWindow(token, myCard);
    objecttalletusWindow->show();
    this->close();
}


