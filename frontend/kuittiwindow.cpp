#include "kuittiwindow.h"
#include "ui_kuittiwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>

kuittiwindow::kuittiwindow(QByteArray token,QString cardnum,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kuittiwindow)
{
    ui->setupUi(this);
    webToken = token;
    card_number = cardnum;
    ui->kuittiTable->setRowCount(10);
    ui->kuittiTable->setColumnCount(6);

    ui->kuittiTable->verticalHeader()->setVisible(false);
    ui->kuittiTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->kuittiTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->kuittiTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->kuittiTable->setShowGrid(false);
    ui->kuittiTable->setStyleSheet("QTableView {selection-background-color: green;}");
    ui->kuittiTable->setGeometry(QApplication::desktop()->screenGeometry());
    QString site_url=url::getBaseUrl()+"cards/" + card_number;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    kuittiManager = new QNetworkAccessManager(this);

    connect(kuittiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(kuittiSlot(QNetworkReply*)));
    reply = kuittiManager->get(request);

}

kuittiwindow::~kuittiwindow()
{
    delete ui;
}

void kuittiwindow::kuittiSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonObject json_obj = json_doc.object();

    QString account = QString::number(json_obj["id_account"].toInt());
    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString debit_credit = json_obj["debit_credit"].toString();
    QString card_owner = json_obj["card_owner"].toString();

    lista += "Account ID: " + account + "\nCard number: "+card_number + "\nDebit/Credit: "+debit_credit +"\nCard owner: "+card_owner;
    //ui->labelAsiakas->setText(lista);

    reply->deleteLater();
    kuittiManager->deleteLater();
    QString site_url=url::getBaseUrl()+"transactions/";
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    asiakasManager = new QNetworkAccessManager(this);
    connect(asiakasManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(asiakasSlot(QNetworkReply*)));
    reply = asiakasManager->get(request);
}

void kuittiwindow::asiakasSlot(QNetworkReply *reply)
{
    m_TableHeader<<"ID"<<"Kortin numero"<<"Summa"<<"Päivämäärä"<<"Tapahtuma"<<lista;
    ui->kuittiTable->setHorizontalHeaderLabels(m_TableHeader);
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QJsonArray array = {};
    int rows = 0;

    //TÄÄ ON TODO: pitää hakea vain viimeisin transaction! ui:n pitää olla vähän
    //isompi ja laittaa sulkemisnappi

    for (int i = 0; i < json_array.size();i++) {
        array.insert(i,json_array.at(i));
        QJsonValue items = json_array.at(i);
        QJsonObject obj = items.toObject();
        QString id_transactions = QString::number(obj["id_transactions"].toInt());
        QString card_numbers = QString::number(obj["card_number"].toInt());
        QString sums = QString::number(obj["sum"].toInt());
        QString dates = obj["date"].toString();
        QString descriptions = obj["description"].toString();

        if (card_numbers != kuittiwindow::card_number) {
            qDebug() << "ERIT: " << "listasta haettu numero: "<<card_numbers<< "käyttäjän numero: " <<card_number;
        } else {
            ui->kuittiTable->setItem(rows, 0, new QTableWidgetItem(id_transactions));
            ui->kuittiTable->setItem(rows, 1, new QTableWidgetItem(card_numbers));
            ui->kuittiTable->setItem(rows, 2, new QTableWidgetItem(sums));
            ui->kuittiTable->setItem(rows, 3, new QTableWidgetItem(dates));
            ui->kuittiTable->setItem(rows, 4, new QTableWidgetItem(descriptions));
            ui->kuittiTable->resizeColumnsToContents();
            ui->kuittiTable->resizeRowsToContents();
            if (rows == 10) {
                ui->kuittiTable->setRowCount(10);
            } else {
                rows++;
            }
        }
    }
    reply->deleteLater();
    asiakasManager->deleteLater();
}