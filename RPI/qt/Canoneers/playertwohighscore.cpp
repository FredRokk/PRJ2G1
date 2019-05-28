#include "playertwohighscore.h"
#include "ui_playertwohighscore.h"

playerTwoHighscore::playerTwoHighscore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::playerTwoHighscore)
{
    ui->setupUi(this);
}

playerTwoHighscore::~playerTwoHighscore()
{
    delete ui;
}
