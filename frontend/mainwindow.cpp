#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if (this->isHidden()==true) {
        ui->setupUi(this);
        MainWindow::setWindowState(Qt::WindowMaximized);
        qDebug() << "mainwindow konstruktori";
        ui->labelKirjaudu->setText("Anna kortin numero ja paina kirjaudu sisään");
    }


}

MainWindow::~MainWindow()
{
    qDebug() << "mainwindow destruktori";
    delete ui;
    delete objectKortinValinta;
    objectKortinValinta=nullptr;
    delete objectBankWindow;
    objectBankWindow=nullptr;
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
        ui->lineEditKirjaudu->text();
        break;
    }
    kirjautuminen++;
}
void MainWindow::showWindow() {
         show();
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
                ui->loginButton->hide();
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
void MainWindow::on_peruutaButton_clicked() //tämä ois "restart"
{
    ui->lineEditKirjaudu->clear();
    kirjautuminen=1;
    ui->labelKirjaudu->setText("Anna kortin numero ja paina kirjaudu sisään");
    ui->labelInfo->setText("");
    ui->loginButton->show();
    ui->lineEditKirjaudu->setEchoMode(QLineEdit::Normal);
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

void MainWindow::on_pyyhiButton_clicked()
{
    ui->lineEditKirjaudu->backspace();
}
