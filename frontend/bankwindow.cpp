#include "bankwindow.h"
#include "ui_bankwindow.h"


bankwindow::bankwindow(QString cardnum, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bankwindow)
{
    ui->setupUi(this);
    myCard=cardnum;
}

bankwindow::~bankwindow()
{
    delete ui;
}

void bankwindow::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}
