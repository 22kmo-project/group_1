#include "nostosummawindow.h"
#include "ui_nostosummawindow.h"
#include "url.h"
#include "bankwindow.h"

nostoSummaWindow::nostoSummaWindow(QByteArray token, QString myCard, bool cardType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nostoSummaWindow)
{
    ui->setupUi(this);
    nostoSummaWindow::setWindowState(Qt::WindowMaximized);
    webToken=token;
    cardnum=myCard;
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
    qDebug()<<"kortti nostossa on"<<credit;
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

    ui->kumiButton->hide();
    ui->nollaButton->hide();
    ui->yksiButton->hide();
    ui->kaksiButton->hide();
    ui->kolmeButton->hide();
    ui->neljaButton->hide();
    ui->viisiButton->hide();
    ui->kuusiButton->hide();
    ui->seitsemanButton->hide();
    ui->kahdeksanButton->hide();
    ui->yhdeksanButton->hide();

}
nostoSummaWindow::~nostoSummaWindow()
{
    delete ui;
}
void nostoSummaWindow::nostoSlot(QNetworkReply *reply)
{
    if(credit==false){
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
    for (aika = 10; aika >= 0; aika--) {
        delay();
        ui->timer->display(aika);

    }
    bankwindow *main = new bankwindow(webToken,cardnum,credit);
    main->show();
    close();

    }else{
        QByteArray response_data=reply->readAll();
        qDebug()<<response_data;
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();
        QString omistaja=json_obj["card_owner"].toString();
        QString Saldo=QString::number(json_obj["credit_limit"].toDouble());

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
        for (aika = 10; aika >= 0; aika--) {
            delay();
            ui->timer->display(aika);
        }
        bankwindow *main = new bankwindow(webToken,cardnum,credit);
        main->show();
        close();
    }
  }
void nostoSummaWindow::balanceSlot(QNetworkReply *reply)
{
    if(credit==false){
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    balance=QString::number(json_obj["debit_balance"].toDouble());
    creditLimit = QString::number(json_obj["credit_limit"].toDouble());
    QString debitBalance =QString::number(json_obj["debit_balance"].toDouble());
    qDebug()<<"balance on:" << balance;
    ui->kyhny_info->setText("Tilillä katetta: "+balance);
    }
    else{
        QByteArray response_data=reply->readAll();
        qDebug()<<response_data;
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonObject json_obj = json_doc.object();
        balance=QString::number(json_obj["credit_limit"].toDouble());
        debitBalance = QString::number(json_obj["debit_balance"].toDouble());
        qDebug()<<"balance on:" << balance;
        ui->kyhny_info->setText("Käytettävissä: "+balance);
    }
}

void nostoSummaWindow::updateSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    reply->deleteLater();
    updateManager->deleteLater();
}

void nostoSummaWindow::on_pushButton20e_clicked()
{
    aika = 10;
    qDebug()<<"20e";
    nosto=balance.toDouble();
    countMoney(nosto,20);
    delay();
    qDebug()<<nosto;
}
void nostoSummaWindow::on_pushButton40e_clicked()
{
    aika = 10;
    qDebug()<<"40e";
    nosto=balance.toDouble();
    countMoney(nosto,40);
    delay();
    qDebug()<<nosto;;
}
void nostoSummaWindow::on_pushButton60e_clicked()
{
    aika = 10;
    qDebug()<<"60e";
    nosto=balance.toDouble();
    countMoney(nosto,60);
    delay();
    qDebug()<<nosto;
}
void nostoSummaWindow::on_pushButton100e_clicked()
{
    aika = 10;
    qDebug()<<"100e";
    nosto=balance.toDouble();
    countMoney(nosto,100);
    delay();
    qDebug()<<nosto;
}
void nostoSummaWindow::on_pushButton200e_clicked()
{
    aika = 10;
    qDebug()<<"200e";
    nosto=balance.toDouble();
    countMoney(nosto,200);
    delay();
    qDebug()<<nosto;
}
void nostoSummaWindow::on_pushButton500e_clicked()
{
    aika = 10;
    qDebug()<<"500e";
    nosto=balance.toDouble();
    countMoney(nosto,500);
    delay();
    qDebug()<<nosto;
}

void nostoSummaWindow::on_suljeButton_clicked()
{
    bankwindow *bank = new bankwindow(webToken, cardnum,credit);
    bank->show();
    close();
}

void nostoSummaWindow::delay()
{
    int afkTimer=1;
    QTime dieTime= QTime::currentTime().addSecs(afkTimer);
     while (QTime::currentTime() < dieTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void nostoSummaWindow::countMoney(double omaSaldo, double nostoSumma)
{
    if(omaSaldo<nostoSumma)
    {

        ui->nosto_info->setText("Tilillä ei riittävästi katetta.");
    }

     if(credit==false)
    {
        omaSaldo=omaSaldo-nostoSumma;
        ui->nosto_info->setText("Nosto onnistui");
        QJsonObject jsonObj;
        jsonObj.insert("debit_balance",omaSaldo);
        jsonObj.insert("credit_limit",creditLimit);
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
  else if (credit==true)
    {
        omaSaldo=omaSaldo-nostoSumma;
        ui->nosto_info->setText("Nosto onnistui");
        QJsonObject jsonObj;
        jsonObj.insert("credit_limit",omaSaldo);
        jsonObj.insert("debit_balance",debitBalance);
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
        ui->kyhny_info->setText("Luottoa jäljellä" +balance);
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
{   aika = 10;
    ui->lineEdit->show();
    ui->muu_info->show();
    ui->confirmButton->show();
    ui->kumiButton->show();
    ui->nollaButton->show();
    ui->yksiButton->show();
    ui->kaksiButton->show();
    ui->kolmeButton->show();
    ui->neljaButton->show();
    ui->viisiButton->show();
    ui->kuusiButton->show();
    ui->seitsemanButton->show();
    ui->kahdeksanButton->show();
    ui->yhdeksanButton->show();
    delay();
}
void nostoSummaWindow::on_confirmButton_clicked()
{
    aika = 10;
    ui->nosto_info->setText("");
    ui->jakolabel->hide();
    qDebug()<<"Muu summa ok clicked";
    QString nostoluku;
    nostoluku=ui->lineEdit->text();
    ui->lineEdit->clear();
    ui->muu_info->clear();
    int y = nostoluku.toDouble();
    nosto=balance.toDouble();
    if (y%10==0)
    {
        countMoney(nosto,y);
    }
    else
    {
        ui->jakolabel->show();
        qDebug()<<"Nosto luku on virheellinen";
    }
}
void nostoSummaWindow::close_window() {
    close();
}
void nostoSummaWindow::on_nollaButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "0");
    delay();
}
void nostoSummaWindow::on_yksiButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "1");
    delay();
}
void nostoSummaWindow::on_kaksiButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "2");
    delay();
}
void nostoSummaWindow::on_kolmeButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "3");
    delay();
}
void nostoSummaWindow::on_neljaButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "4");
    delay();
}
void nostoSummaWindow::on_viisiButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "5");
    delay();
}
void nostoSummaWindow::on_kuusiButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "6");
    delay();
}
void nostoSummaWindow::on_seitsemanButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "7");
    delay();
}
void nostoSummaWindow::on_kahdeksanButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "8");
    delay();
}
void nostoSummaWindow::on_yhdeksanButton_clicked()
{
    aika = 10;
    ui->lineEdit->setText(ui->lineEdit->text()+ "9");
    delay();
}
void nostoSummaWindow::on_kumiButton_clicked()
{
    ui->lineEdit->backspace();
}
