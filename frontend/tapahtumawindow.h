#ifndef TAPAHTUMAWINDOW_H
#define TAPAHTUMAWINDOW_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class tapahtumaWindow;
}

class tapahtumaWindow : public QDialog
{
    Q_OBJECT

public:
    explicit tapahtumaWindow(QByteArray wt,QString cardnum,QWidget *parent = nullptr);
    ~tapahtumaWindow();
    void setWebToken(const QByteArray &newWebToken);

private:
    Ui::tapahtumaWindow *ui;
    QByteArray webToken;
    QString card_number;
};

#endif // TAPAHTUMAWINDOW_H
