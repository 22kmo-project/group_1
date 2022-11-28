#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "url.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objectBankWindow;
    objectBankWindow=nullptr;

}


void MainWindow::on_loginButton_clicked()
{
    cardnum=ui->textCardNum->text();
    QString pincode=ui->textPinCode->text();

    QJsonObject jsonObj;
    jsonObj.insert("cardnum",cardnum);
    jsonObj.insert("pin",pincode);

    QString site_url=url::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    int test=QString::compare(response_data,"false");
    qDebug()<<test;

    //Esimerkeissä allaoleva, mutta toimii ilmankin

    /*QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString tokenstring;

    tokenstring = json_obj["token"].toString();
    QByteArray token = tokenstring.toUtf8();*/

    if(response_data.length()==0){
        ui->labelInfo->setText("Palvelin ei vastaa");
    }
    else {
        if(QString::compare(response_data,"-4078")==0){
            ui->labelInfo->setText("Virhe tietokanta yhteydessä");
        }
        else {
            if(test==0){
                ui->textCardNum->clear();
                ui->textPinCode->clear();
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää");
            }
            else {
                objectBankWindow=new bankwindow(cardnum);
                objectBankWindow->setWebToken("Bearer "+response_data);
                objectBankWindow->show();
            }
        }
    }
    reply->deleteLater();
    loginManager->deleteLater();

}
