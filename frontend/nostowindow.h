#ifndef NOSTOWINDOW_H
#define NOSTOWINDOW_H

#include <QWidget>

namespace Ui {
class nostoWindow;
}

class nostoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit nostoWindow(QWidget *parent = nullptr);
    ~nostoWindow();

private:
    Ui::nostoWindow *ui;
};

#endif // NOSTOWINDOW_H
