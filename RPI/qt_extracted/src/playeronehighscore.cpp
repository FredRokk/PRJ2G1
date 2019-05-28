#include "playeronehighscore.h"
#include "ui_playeronehighscore.h"

playerOneHighscore::playerOneHighscore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::playerOneHighscore)
{
    ui->setupUi(this);
}

playerOneHighscore::~playerOneHighscore()
{
    delete ui;
}
