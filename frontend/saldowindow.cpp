#include "saldowindow.h"
#include "ui_saldowindow.h"

saldoWindow::saldoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saldoWindow)
{
    ui->setupUi(this);
}

saldoWindow::~saldoWindow()
{
    delete ui;
}
