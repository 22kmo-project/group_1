#ifndef SALDOWINDOW_H
#define SALDOWINDOW_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class saldoWindow;
}

class saldoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit saldoWindow(QWidget *parent = nullptr);
    ~saldoWindow();
    void setWebToken(const QByteArray &newWebToken);

private:
    Ui::saldoWindow *ui;
    QByteArray webToken;
    QString idAccount;
    QString myCard;
    void checkAccount(QString cardnum);
    QByteArray response_data;
};

#endif // SALDOWINDOW_H
