#include "round3.h"
#include "ui_round3.h"

round3::round3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::round3)
{
    ui->setupUi(this);
}

round3::~round3()
{
    delete ui;
}
