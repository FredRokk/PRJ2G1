#ifndef IDLE_H
#define IDLE_H

#include <QMainWindow>

namespace Ui {
class idle;
}

class idle : public QMainWindow
{
    Q_OBJECT

public:
    explicit idle(QWidget *parent = 0);
    ~idle();
    Ui::idle *ui;

private:
};

#endif // IDLE_H
