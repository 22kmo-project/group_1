#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "konstruktori";
    ui->labelKirjaudu->setText("Anna kortin numero ja paina kirjaudu sisään");
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
    switch(kirjautuminen) {
    case 1:
        cardNumber=ui->lineEditKirjaudu->text();
        ui->lineEditKirjaudu->clear();
        ui->labelKirjaudu->setText("Anna pin-koodi ja paina kirjaudu sisään");
        break;
    case 2:
        cardPin=ui->lineEditKirjaudu->text();
        ui->labelKirjaudu->setText("");

        QJsonObject jsonObj;
        jsonObj.insert("card_number",cardNumber);
        jsonObj.insert("pin_code",cardPin);

        QString site_url=url::getBaseUrl()+"login";
        QNetworkRequest request((site_url));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        loginManager = new QNetworkAccessManager(this);
        connect(loginManager, SIGNAL (finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));

        reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
        break;
    }
    kirjautuminen++;
}

void MainWindow::loginSlot(QNetworkReply *reply)
{

    //TODO: lisää card locked notif kirjautuessa.
    // sleep,close implementointi, poista bäkistä process exit ja db endit jatkuvalle toiminolle frontissa.


    response_data=reply->readAll();
    qDebug()<<"response data"<<response_data;
    int test=QString::compare(response_data, "false");
    qDebug()<<"test"<<test;
    if(response_data.length()==0){
        loginTries = loginTries - 1;
        ui->lineEditKirjaudu->clear();
        ui->labelInfo->setText("Väärä pin. Syötä pin uudelleen. Yrityksiä: "  + QString::number(loginTries));
        kirjautuminen--;
        if (loginTries == 0) {
            ui->labelInfo->clear();
            ui->labelInfo->setText("Kortti lukittu. Ohjelma suljetaan...");
        }
    }
    else {
        if(QString::compare(response_data,"-4078")==0){
            ui->lineEditKirjaudu->clear();
<<<<<<< HEAD
<<<<<<< HEAD
            ui->labelInfo->setText("Virhe tietokanta yhteydessä");
            kirjautuminen--;
=======
            ui->labelInfo->setText("Virhe tietokantayhteydessä!");
>>>>>>> 100c93329f7d488ec83f50f77a2982d818757cf1
=======
            ui->labelInfo->setText("Virhe tietokanta yhteydessä");
            kirjautuminen--;
            ui->labelInfo->setText("Virhe tietokantayhteydessä!");
>>>>>>> cd9f46c91b14521c301347131edf97a450f98ad5
        }
        else {
            if(test==0){
                ui->lineEditKirjaudu->clear();
<<<<<<< HEAD
<<<<<<< HEAD
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää");
                kirjautuminen--;
=======
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää!");
>>>>>>> 100c93329f7d488ec83f50f77a2982d818757cf1
=======
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää");
                kirjautuminen--;
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää!");
>>>>>>> cd9f46c91b14521c301347131edf97a450f98ad5
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
void MainWindow::on_peruutaButton_clicked()
{
    this -> close();
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "1");
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "2");
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "3");
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "4");
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "5");
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "6");
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "7");
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "8");
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "9");
}


void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "0");
}

