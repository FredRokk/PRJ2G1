#include "versus.h"
#include "ui_versus.h"

versus::versus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::versus)
{
    ui->setupUi(this);
}

versus::~versus()
{
    delete ui;
}
