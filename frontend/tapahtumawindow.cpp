#include "tapahtumawindow.h"
#include "ui_tapahtumawindow.h"

tapahtumaWindow::tapahtumaWindow(QByteArray wt,QString cardnum,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tapahtumaWindow)
{
    ui->setupUi(this);
    wt=webToken;
    cardnum=card_number;
}

tapahtumaWindow::~tapahtumaWindow()
{
    delete ui;
}
