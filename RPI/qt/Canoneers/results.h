#ifndef RESULTS_H
#define RESULTS_H

#include <QMainWindow>

namespace Ui {
class results;
}

class results : public QMainWindow
{
    Q_OBJECT

public:
    explicit results(QWidget *parent = 0);
    ~results();

private:
    Ui::results *ui;
};

#endif // RESULTS_H
