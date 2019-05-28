#ifndef MAPSELECT_H
#define MAPSELECT_H

#include <QMainWindow>

namespace Ui {
class mapSelect;
}

class mapSelect : public QMainWindow
{
    Q_OBJECT

public:
    explicit mapSelect(QWidget *parent = 0);
    ~mapSelect();

private:
    Ui::mapSelect *ui;
};

#endif // MAPSELECT_H
