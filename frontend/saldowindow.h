#ifndef SALDOWINDOW_H
#define SALDOWINDOW_H

#include <QWidget>

namespace Ui {
class saldoWindow;
}

class saldoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit saldoWindow(QWidget *parent = nullptr);
    ~saldoWindow();

private:
    Ui::saldoWindow *ui;
};

#endif // SALDOWINDOW_H
