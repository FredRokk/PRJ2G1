#include "mapselect.h"
#include "ui_mapselect.h"

mapSelect::mapSelect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mapSelect)
{
    ui->setupUi(this);
}

mapSelect::~mapSelect()
{
    delete ui;
}
