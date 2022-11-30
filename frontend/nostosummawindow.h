#ifndef NOSTOSUMMAWINDOW_H
#define NOSTOSUMMAWINDOW_H

#include <QWidget>

namespace Ui {
class nostoSummaWindow;
}

class nostoSummaWindow : public QWidget
{
    Q_OBJECT

public:
    explicit nostoSummaWindow(QWidget *parent = nullptr);
    ~nostoSummaWindow();

private:
    Ui::nostoSummaWindow *ui;
};

#endif // NOSTOSUMMAWINDOW_H
