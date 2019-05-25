#ifndef PRACTICE_H
#define PRACTICE_H

#include <QMainWindow>

namespace Ui {
class practice;
}

class practice : public QMainWindow
{
    Q_OBJECT

public:
    explicit practice(QWidget *parent = 0);
    ~practice();

private:
    Ui::practice *ui;
};

#endif // PRACTICE_H
