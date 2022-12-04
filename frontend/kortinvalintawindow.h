#ifndef KORTINVALINTAWINDOW_H
#define KORTINVALINTAWINDOW_H

#include <QWidget>
#include "bankwindow.h"

namespace Ui {
class kortinValintaWindow;
}

class kortinValintaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit kortinValintaWindow(QString cardnum, QWidget *parent = nullptr);
    ~kortinValintaWindow();

    const QString &getWebToken () const;

    void setWebToken(const QByteArray &newWebToken);

private slots:
    void on_creditButton_clicked();

    void on_debitButton_clicked();

private:
    Ui::kortinValintaWindow *ui;
    bankwindow *objectBankWindow;
    QByteArray webToken;
    QString myCard;

};

#endif // KORTINVALINTAWINDOW_H
