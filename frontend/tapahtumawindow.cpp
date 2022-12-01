#include "tapahtumawindow.h"
#include "ui_tapahtumawindow.h"

tapahtumaWindow::tapahtumaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tapahtumaWindow)
{
    ui->setupUi(this);
}

tapahtumaWindow::~tapahtumaWindow()
{
    delete ui;
}
