#include "nostowindow.h"
#include "ui_nostowindow.h"

nostoWindow::nostoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nostoWindow)
{
    ui->setupUi(this);
}

nostoWindow::~nostoWindow()
{
    delete ui;
}
