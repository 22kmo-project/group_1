#include "kortinvalintawindow.h"
#include "ui_kortinvalintawindow.h"

kortinValintaWindow::kortinValintaWindow(QString cardnum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::kortinValintaWindow)
{
    ui->setupUi(this);
    myCard=cardnum;
}

kortinValintaWindow::~kortinValintaWindow()
{
    delete ui;
}

void kortinValintaWindow::on_creditButton_clicked()
{

}


void kortinValintaWindow::on_debitButton_clicked()
{

}

