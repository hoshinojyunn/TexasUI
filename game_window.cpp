#include "game_window.h"
#include "ui_game_window.h"

game_window::game_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game_window)
{
    ui->setupUi(this);
}

game_window::~game_window()
{
    delete ui;
}
