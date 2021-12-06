#include "texasui.h"
#include "ui_texasui.h"

texasui::texasui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::texasui)
{
    ui->setupUi(this);
}

texasui::~texasui()
{
    delete ui;
}
