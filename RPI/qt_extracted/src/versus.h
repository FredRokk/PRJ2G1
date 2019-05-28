#ifndef VERSUS_H
#define VERSUS_H

#include <QMainWindow>

namespace Ui {
class versus;
}

class versus : public QMainWindow
{
    Q_OBJECT

public:
    explicit versus(QWidget *parent = 0);
    ~versus();

private:
    Ui::versus *ui;
};

#endif // VERSUS_H
