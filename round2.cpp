#include "round2.h"
#include "ui_round2.h"

round2::round2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::round2)
{
    ui->setupUi(this);
}

round2::~round2()
{
    delete ui;
}
