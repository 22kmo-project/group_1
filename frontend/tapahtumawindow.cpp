#include "tapahtumawindow.h"
#include "ui_tapahtumawindow.h"

tapahtumaWindow::tapahtumaWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tapahtumaWindow)
{
    ui->setupUi(this);
}

tapahtumaWindow::~tapahtumaWindow()
{
    delete ui;
}
