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
    explicit tapahtumaWindow(QWidget *parent = nullptr);
    ~tapahtumaWindow();

private:
    Ui::tapahtumaWindow *ui;
};

#endif // TAPAHTUMAWINDOW_H
