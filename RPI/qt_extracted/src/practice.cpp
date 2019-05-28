#include "practice.h"
#include "ui_practice.h"

practice::practice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::practice)
{
    ui->setupUi(this);
}

practice::~practice()
{
    delete ui;
}
