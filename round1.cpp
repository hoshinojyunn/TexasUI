#include "round1.h"
#include "ui_round1.h"

round1::round1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::round1)
{
    ui->setupUi(this);
}

round1::~round1()
{
    delete ui;
}
