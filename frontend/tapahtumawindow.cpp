#include "tapahtumawindow.h"
#include "ui_tapahtumawindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>
#include <QMessageBox>
#include "bankwindow.h"

tapahtumaWindow::tapahtumaWindow(QByteArray token,QString myCard,bool cardType,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tapahtumaWindow)
{
    ui->setupUi(this);
    tapahtumaWindow::setWindowState(Qt::WindowMaximized);
    webToken=token;
    card_number = myCard;
    qDebug()<<card_number;
    if(cardType==true)//debit käytössä = false , credit käytössä = true
    {
        credit=true;
    }
    else
    {
        credit=false;
    }
    ui->timer->setPalette(Qt::red);
    ui->timer->setAutoFillBackground(true);
    QPalette Pal = ui->timer->palette();
    Pal.setColor(QPalette::Normal, QPalette::WindowText, Qt::red);
    Pal.setColor(QPalette::Normal, QPalette::Window, Qt::black);
    ui->timer->setPalette(Pal);
    ui->timer->setPalette(Pal);
    ui->tapahtumaTable->setRowCount(100);
    ui->tapahtumaTable->setColumnCount(6);
    ui->tapahtumaTable->verticalHeader()->setVisible(false);
    ui->tapahtumaTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tapahtumaTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tapahtumaTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tapahtumaTable->setShowGrid(false);
    ui->tapahtumaTable->setStyleSheet("QTableView {selection-background-color: green;}");

    QString site_url=url::getBaseUrl()+"cards/" + card_number;
    QNetworkRequest request((site_url));
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
void tapahtumaWindow::delay()
{
    int afkTimer=1;
    QTime dieTime= QTime::currentTime().addSecs(afkTimer);
     while (QTime::currentTime() < dieTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void tapahtumaWindow::tapahtumaSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString account = QString::number(json_obj["id_account"].toInt());
    QString card_number = QString::number(json_obj["card_number"].toInt());
    QString debit_credit = json_obj["debit_credit"].toString();
    QString card_owner = json_obj["card_owner"].toString();

    lista += "Account ID: " + account + "\nCard number: "+card_number + "\nDebit/Credit: "+debit_credit +"\nCard owner: "+card_owner;
    qDebug()<<"cards data in tapahtumawindow: "<<account<<card_number<<debit_credit<<card_owner;
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

    for (aika = 10; aika >= 0; aika--) {
        delay();
        ui->timer->display(aika);
        if (aika == 0&& this->isHidden()==false) {
            bankwindow *bank = new bankwindow(webToken,card_number,credit);
            bank->show();
            this->close();
        }
    }

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
            rowsOverTen++;
            qDebug() << rowsOverTen;
            ui->tapahtumaTable->setItem(totalRows, 0, new QTableWidgetItem(id_transactions));
            ui->tapahtumaTable->setItem(totalRows, 1, new QTableWidgetItem(card_numbers));
            ui->tapahtumaTable->setItem(totalRows, 2, new QTableWidgetItem(sums));
            ui->tapahtumaTable->setItem(totalRows, 3, new QTableWidgetItem(dates));
            ui->tapahtumaTable->setItem(totalRows, 4, new QTableWidgetItem(descriptions));
            ui->tapahtumaTable->resizeColumnsToContents();
            ui->tapahtumaTable->resizeRowsToContents();
            totalRows++;
            if (totalRows >= 10) {
                numbersAboveTen++;
                ui->tapahtumaTable->hideRow(rowsOverTen);
            }
        }
    }
    if (numbersAboveTen == 0) {
        numbersAboveTen = 0;
    } else {
        numbersAboveTen--;
    }
    if (totalRows < 10) {
        minimumRows = totalRows;
        lastVisibleRowNumber = minimumRows;
    } else {
        minimumRows = 10;
        lastVisibleRowNumber = minimumRows;
    }
    resetCounter = numbersAboveTen;
    ui->tapahtumaTable->setRowCount(totalRows);
    qDebug() << "OverTenCounter and totalrows:" << numbersAboveTen << totalRows;
    reply->deleteLater();
    asiakasManager->deleteLater();
}

void tapahtumaWindow::on_backwardButton_clicked()
{
    aika = 10;
    if (totalRows < 10) {
        qDebug() << "Total rows < 10.";
    } else if (lastVisibleRowNumber >= 20 && lastVisibleRowNumber != totalRows) {
        numbersAboveTen = resetCounter;
        for(int i = lastVisibleRowNumber;i >= lastVisibleRowNumber - 10;i--) {
            ui->tapahtumaTable->hideRow(i);
        }
        lastVisibleRowNumber = lastVisibleRowNumber - 10;
    } else if (lastVisibleRowNumber == totalRows && lastIncrement == 10) {
        for(int i = lastVisibleRowNumber;i >= lastVisibleRowNumber - 10;i--) {
            ui->tapahtumaTable->hideRow(i);
        }
        lastVisibleRowNumber = lastVisibleRowNumber - 10;
    } else if (lastVisibleRowNumber == totalRows && lastIncrement < 10) {
        for(int i = lastVisibleRowNumber;i >= lastVisibleRowNumber - lastIncrement;i--) {
            ui->tapahtumaTable->hideRow(i);
        }
        lastVisibleRowNumber = lastVisibleRowNumber - lastIncrement;
    }
    if (lastVisibleRowNumber == minimumRows) {
        numbersAboveTen = resetCounter;
    }
}

void tapahtumaWindow::on_forwardButton_clicked()
{
    aika = 10;
    if (lastVisibleRowNumber == totalRows) {
        qDebug() << "All rows visible.";
    } else if (numbersAboveTen >= 10) {
        lastIncrement = 10;
        for (int i = lastVisibleRowNumber; i < lastVisibleRowNumber + 10;i++) {
            ui->tapahtumaTable->showRow(i);
        }
        lastVisibleRowNumber = lastVisibleRowNumber + 10;
        numbersAboveTen = numbersAboveTen - 10;
    } else if (numbersAboveTen < 10) {
        lastIncrement = numbersAboveTen;
        for (int i = lastVisibleRowNumber; i < lastVisibleRowNumber + numbersAboveTen;i++) {
            ui->tapahtumaTable->showRow(i);
        }
        lastVisibleRowNumber = lastVisibleRowNumber + numbersAboveTen;
    }
}

void tapahtumaWindow::on_closeButton_clicked()
{
    bankwindow *bank = new bankwindow(webToken, card_number,credit);
    bank->show();
    close();
}
