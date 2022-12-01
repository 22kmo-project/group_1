#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "konstruktori";
}

MainWindow::~MainWindow()
{
    qDebug() << "destruktori";
    delete ui;
    delete objectBankWindow;
    objectBankWindow=nullptr;

}


void MainWindow::on_loginButton_clicked()
{
    qDebug() << "login clicked";
    cardNumber=ui->textCardNum->text();
    cardPin=ui->textPinCode->text();

    QJsonObject jsonObj;
    jsonObj.insert("card_number",cardNumber);
    jsonObj.insert("pin_code",cardPin);

    QString site_url=url::getBaseUrl()+"login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL (finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"response data"<<response_data;
    int test=QString::compare(response_data, "false");
    qDebug()<<"test"<<test;

    if(response_data.length()==0){
        ui->textCardNum->clear();
        ui->textPinCode->clear();
        ui->labelInfo->setText("Palvelin ei vastaa");
    }
    else {
        if(QString::compare(response_data,"-4078")==0){
            ui->textCardNum->clear();
            ui->textPinCode->clear();
            ui->labelInfo->setText("Virhe tietokanta yhteydessä");
        }
        else {
            if(test==0){
                ui->textCardNum->clear();
                ui->textPinCode->clear();
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää");
                    qDebug()<<"Väärät toimii";
            }
            else {
                objectBankWindow=new bankwindow(cardNumber);
                objectBankWindow->setWebToken("Bearer "+response_data);
                objectBankWindow->show();
                this->hide();
            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();

}
