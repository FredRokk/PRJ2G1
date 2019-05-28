#include "idle.h"
#include "ui_idle.h"

idle::idle(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::idle)
{
    ui->setupUi(this);
}

idle::~idle()
{
    delete ui;
}
