#include "tapahtumawindow.h"
#include "ui_tapahtumawindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
tapahtumaWindow::tapahtumaWindow(QByteArray wt,QString myCard,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tapahtumaWindow)
{
    ui->setupUi(this);
    wt=webToken;
    card_number = myCard;
    qDebug()<<card_number;
    ui->tapahtumaTable->setRowCount(10);
    ui->tapahtumaTable->setColumnCount(6);

    ui->tapahtumaTable->verticalHeader()->setVisible(false);
    ui->tapahtumaTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tapahtumaTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tapahtumaTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tapahtumaTable->setShowGrid(false);
    ui->tapahtumaTable->setStyleSheet("QTableView {selection-background-color: green;}");
    ui->tapahtumaTable->setGeometry(QApplication::desktop()->screenGeometry());

    QString site_url=url::getBaseUrl()+"cards/" + card_number;
    QNetworkRequest request((site_url));
    qDebug()<<site_url;
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    tapahtumaManager = new QNetworkAccessManager(this);

    connect(tapahtumaManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tapahtumaSlot(QNetworkReply*)));
    reply = tapahtumaManager->get(request);

}

tapahtumaWindow::~tapahtumaWindow()
{
    delete ui;
}


void tapahtumaWindow::tapahtumaSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data; //toimii tuo tietokannasta tiedot
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonObject json_obj = json_doc.object();

    QString account = QString::number(json_obj["id_account"].toInt());
    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString debit_credit = json_obj["debit_credit"].toString();
    QString card_owner = json_obj["card_owner"].toString();

    lista += "Account ID: " + account + "\nCard number: "+card_number + "\nDebit/Credit: "+debit_credit +"\nCard owner: "+card_owner;

    qDebug()<<"cards data in tapahtumawindow: "<<account<<card_number<<debit_credit<<card_owner;
    //ui->labelAsiakas->setText(lista);

    reply->deleteLater();
    tapahtumaManager->deleteLater();
    QString site_url=url::getBaseUrl()+"transactions/";
    qDebug()<<site_url;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    asiakasManager = new QNetworkAccessManager(this);
    connect(asiakasManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(asiakasSlot(QNetworkReply*)));
    reply = asiakasManager->get(request);
}

void tapahtumaWindow::asiakasSlot(QNetworkReply *reply)
{
    m_TableHeader<<"ID"<<"Kortin numero"<<"Summa"<<"Päivämäärä"<<"Tapahtuma"<<lista;
    ui->tapahtumaTable->setHorizontalHeaderLabels(m_TableHeader);
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonArray array = {};
    int rows = 0;

    for (int i = 0; i < json_array.size();i++) {
        array.insert(i,json_array.at(i));
        QJsonValue items = json_array.at(i);
        QJsonObject obj = items.toObject();
        QString id_transactions = QString::number(obj["id_transactions"].toInt());
        QString card_numbers = QString::number(obj["card_number"].toInt());
        QString sums = QString::number(obj["sum"].toInt());
        QString dates = obj["date"].toString();
        QString descriptions = obj["description"].toString();

        if (card_numbers != tapahtumaWindow::card_number) {
            qDebug() << "ERIT: " << "listasta haettu numero: "<<card_numbers<< "käyttäjän numero: " <<card_number;
        } else {
            ui->tapahtumaTable->setItem(rows, 0, new QTableWidgetItem(id_transactions));
            ui->tapahtumaTable->setItem(rows, 1, new QTableWidgetItem(card_numbers));
            ui->tapahtumaTable->setItem(rows, 2, new QTableWidgetItem(sums));
            ui->tapahtumaTable->setItem(rows, 3, new QTableWidgetItem(dates));
            ui->tapahtumaTable->setItem(rows, 4, new QTableWidgetItem(descriptions));
            ui->tapahtumaTable->resizeColumnsToContents();
            ui->tapahtumaTable->resizeRowsToContents();
            if (rows == 10) {
                ui->tapahtumaTable->setRowCount(10);
            } else {
                rows++;
            }
        }
    }
    reply->deleteLater();
    asiakasManager->deleteLater();
}

void tapahtumaWindow::on_closeButton_clicked()
{
    qDebug () << "sulje";
    this->close();
}


void tapahtumaWindow::on_backwardButton_clicked(bool checked)
{

}


void tapahtumaWindow::on_forwardButton_clicked(bool checked)
{

}

