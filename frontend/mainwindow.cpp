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
    delete objectKortinValinta;
    objectKortinValinta=nullptr;
}

void MainWindow::delay()
{
    int afkTimer=30; //afkTimer=30 tarkoittaa 30 sekuntia. Muokkaa lyhyemmäksi kun testailet.
        QTime dieTime= QTime::currentTime().addSecs(afkTimer);
         while (QTime::currentTime() < dieTime)
             QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
         qDebug()<<"afkTimer 30sec";
         this->close(); //Tähän pitää keksiä järkevä funktio että menee aloitusnäkymään
}

void MainWindow::on_loginButton_clicked()
{
    switch(kirjautuminen) {
    case 1:
        cardNum=ui->lineEditKirjaudu->text();
        ui->lineEditKirjaudu->clear();
        ui->lineEditKirjaudu->setEchoMode(QLineEdit::Password);
        ui->labelKirjaudu->setText("Anna pin-koodi ja paina kirjaudu sisään");
        break;
    case 2:
        cardPin=ui->lineEditKirjaudu->text();
        ui->labelKirjaudu->setText("");
        QJsonObject jsonObj;
        jsonObj.insert("card_number",cardNum);
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
    delay();
}

void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"response data"<<response_data;
    token = response_data;
    int test=QString::compare(response_data, "false");
    qDebug()<<"test"<<test;
    if(response_data.length()==0){
        loginTries = loginTries - 1;
        qDebug() << "login tries" << loginTries;
        ui->lineEditKirjaudu->clear();
        ui->labelKirjaudu->setText("Väärä pin. Syötä pin uudelleen. Yrityksiä: "  + QString::number(loginTries));
        kirjautuminen--;
        if (loginTries == 0) {
            ui->labelKirjaudu->clear();
            ui->labelKirjaudu->setText("Kortti lukittu.");
        }
    }
    else {
        if(QString::compare(response_data,"-4078")==0){
            ui->lineEditKirjaudu->clear();
            ui->labelInfo->setText("Virhe tietokanta yhteydessä");
            kirjautuminen--;
        }
        else {
            if(test==0){
                ui->lineEditKirjaudu->clear();
                ui->labelInfo->setText("Tunnus ja salasana eivät täsmää");
                kirjautuminen--;
            }
             else {
                objectKortinValinta=new kortinValintaWindow(token,cardNum);
                objectKortinValinta->setWebToken("Bearer "+response_data);
                objectKortinValinta->show();
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
void MainWindow::showWindow() {
    show();
}

void MainWindow::on_pushButton_1_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "1");
    delay();
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "2");
    delay();
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "3");
    delay();
}
void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "4");
    delay();
}
void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "5");
    delay();
}
void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "6");
    delay();
}
void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "7");
    delay();
}
void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "8");
    delay();
}
void MainWindow::on_pushButton_9_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "9");
    delay();
}
void MainWindow::on_pushButton_0_clicked()
{
    ui->lineEditKirjaudu->setText(ui->lineEditKirjaudu->text()+ "0");
    delay();
}

void MainWindow::on_pyyhiButton_clicked()
{
    ui->lineEditKirjaudu->backspace();
    delay();
}
