#ifndef PLAYERONEHIGHSCORE_H
#define PLAYERONEHIGHSCORE_H

#include <QMainWindow>

namespace Ui {
class playerOneHighscore;
}

class playerOneHighscore : public QMainWindow
{
    Q_OBJECT

public:
    explicit playerOneHighscore(QWidget *parent = 0);
    ~playerOneHighscore();

private:
    Ui::playerOneHighscore *ui;
};

#endif // PLAYERONEHIGHSCORE_H
