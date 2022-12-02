#ifndef NOSTOWINDOW_H
#define NOSTOWINDOW_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class nostoWindow;
}

class nostoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit nostoWindow(QWidget *parent = nullptr);
    ~nostoWindow();

private:
    Ui::nostoWindow *ui;
};

#endif // NOSTOWINDOW_H
