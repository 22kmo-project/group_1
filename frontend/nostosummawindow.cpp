#include "nostosummawindow.h"
#include "ui_nostosummawindow.h"
#include "url.h"

nostoSummaWindow::nostoSummaWindow(QByteArray token, QString myCard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nostoSummaWindow)
{
    ui->setupUi(this);
    webToken=token;
    cardnum=myCard;
    QString site_url=url::getBaseUrl()+"cards/"+myCard;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    nostoManager = new QNetworkAccessManager(this);
    connect(nostoManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nostoSlot(QNetworkReply*)));
    reply = nostoManager->get(request);
    qDebug()<<"Tilinumero on:" << myCard;
    ui->tiliLabel->setText(myCard);
    ui->kuittiButton->hide();
    ui->lineEdit->hide();
    ui->muu_info->hide();
    ui->confirmButton->hide();
    ui->jakolabel->hide();
}

nostoSummaWindow::~nostoSummaWindow()
{
    delete ui;
}

void nostoSummaWindow::nostoSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString omistaja=json_obj["card_owner"].toString();
    QString Saldo=QString::number(json_obj["debit_balance"].toDouble());

    id_account=QString::number(json_obj["id_account"].toInt());
    qDebug()<<Saldo;
    ui->nimi_label->setText(omistaja);
    qDebug()<<"Omistajan nimi on:" << omistaja;
    QString site_url=url::getBaseUrl()+"accounts/"+id_account;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    balanceManager = new QNetworkAccessManager(this);
    connect(balanceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(balanceSlot(QNetworkReply*)));
    reply = balanceManager->get(request);
    delay();
  }

void nostoSummaWindow::balanceSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    balance=QString::number(json_obj["debit_balance"].toDouble());
    qDebug()<<"balance on:" << balance;
    ui->kyhny_info->setText("Tilillä katetta: "+balance);
}

void nostoSummaWindow::updateSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    reply->deleteLater();
    updateManager->deleteLater();
}

void nostoSummaWindow::on_pushButton20e_clicked()
{
    qDebug()<<"20e";
    nosto=balance.toDouble();
    countMoney(nosto,20);
    delay();
    qDebug()<<nosto;
}

void nostoSummaWindow::on_pushButton40e_clicked()
{
    qDebug()<<"40e";
    nosto=balance.toDouble();
    countMoney(nosto,40);
    delay();
    qDebug()<<nosto;;
}

void nostoSummaWindow::on_pushButton60e_clicked()
{
    qDebug()<<"60e";
    nosto=balance.toDouble();
    countMoney(nosto,60);
    delay();
    qDebug()<<nosto;
}

void nostoSummaWindow::on_pushButton100e_clicked()
{
    qDebug()<<"100e";
    nosto=balance.toDouble();
    countMoney(nosto,100);
    delay();
    qDebug()<<nosto;
}

void nostoSummaWindow::on_pushButton200e_clicked()
{
    qDebug()<<"200e";
    nosto=balance.toDouble();
    countMoney(nosto,200);
    delay();
    qDebug()<<nosto;
}

void nostoSummaWindow::on_pushButton500e_clicked()
{
    qDebug()<<"500e";
    nosto=balance.toDouble();
    countMoney(nosto,500);
    delay();
    qDebug()<<nosto;
}

void nostoSummaWindow::on_suljeButton_clicked()
{
    qDebug () << "sulje";
    this->close();
}

void nostoSummaWindow::delay()
{
    int afkTimer=30; //afkTimer=30 tarkoittaa 30 sekuntia. Muokkaa lyhyemmäksi kun testailet.
    QTime dieTime= QTime::currentTime().addSecs(afkTimer);
     while (QTime::currentTime() < dieTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
     qDebug()<<"afkTimer 30sec";
     this->close();
}

void nostoSummaWindow::countMoney(double omaSaldo, double nostoSumma)
{
    if(omaSaldo<nostoSumma)
    {

        ui->nosto_info->setText("Tilillä ei riittävästi katetta.");
    }
    else
    {



        omaSaldo=omaSaldo-nostoSumma;

        ui->nosto_info->setText("Nosto onnistui");
        QJsonObject jsonObj;
        jsonObj.insert("debit_balance",omaSaldo);
        QString site_url=url::getBaseUrl()+"/accounts/"+id_account;
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(webToken));
        //WEBTOKEN LOPPU
        updateManager = new QNetworkAccessManager(this);
        connect(updateManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(updateSlot(QNetworkReply*)));
        reply = updateManager->put(request, QJsonDocument(jsonObj).toJson());
        balance = QString::number(omaSaldo);
        ui->kyhny_info->setText("Massia jäljellä: " +balance);
        ui->kuittiButton->show();
    }
}

void nostoSummaWindow::on_kuittiButton_clicked()
{

    objectkuittiwindow = new kuittiwindow(webToken, cardnum);
    objectkuittiwindow->show();
    this->close();
}





void nostoSummaWindow::on_muuButton_clicked()
{
    ui->lineEdit->show();
    ui->muu_info->show();
    ui->confirmButton->show();
    delay();


}





void nostoSummaWindow::on_confirmButton_clicked() //Hei nosta joku järkevä summa on muu_info labelissa
{
    ui->nosto_info->setText("");
    ui->jakolabel->hide();
    qDebug()<<"Muu summa ok clicked";
    QString nostoluku;
    nostoluku=ui->lineEdit->text();
    ui->lineEdit->clear();
    ui->muu_info->clear();
    int y = nostoluku.toDouble();
    nosto=balance.toDouble();
    if (y%10==0)    // Antaa nostaa muu summa vain 10 välein, 10..20..30..40...
    {
        countMoney(nosto,y);
    }
    else
    {
        ui->jakolabel->show();
        qDebug()<<"Nosto luku on virheellinen";
    }

    delay();



}

