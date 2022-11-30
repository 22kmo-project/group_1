#include "nostosummawindow.h"
#include "ui_nostosummawindow.h"

nostoSummaWindow::nostoSummaWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nostoSummaWindow)
{
    ui->setupUi(this);
}

nostoSummaWindow::~nostoSummaWindow()
{
    delete ui;
}
