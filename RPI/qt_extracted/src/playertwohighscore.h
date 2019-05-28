#ifndef PLAYERTWOHIGHSCORE_H
#define PLAYERTWOHIGHSCORE_H

#include <QMainWindow>

namespace Ui {
class playerTwoHighscore;
}

class playerTwoHighscore : public QMainWindow
{
    Q_OBJECT

public:
    explicit playerTwoHighscore(QWidget *parent = 0);
    ~playerTwoHighscore();

private:
    Ui::playerTwoHighscore *ui;
};

#endif // PLAYERTWOHIGHSCORE_H
