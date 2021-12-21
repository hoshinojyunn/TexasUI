#include "texasui.h"
#include "ui_texasui.h"
#include "game_window.h"
#include "var.h"
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
texasui::texasui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::texasui)
{

    ui->setupUi(this);
    qDebug()<<"texasui build successfully";
    //qDebug()<<"game"
    setFixedSize(1200,600);
    setWindowTitle("TexasHoldem");
    connect(ui->actionexit,&QAction::triggered,[=](){
       this->close();
    });
    connect(ui->game_start,&QPushButton::clicked,[=](){
        QTimer::singleShot(100,this,[=](){
            qDebug()<<"click button";
            game_window*game_w=new game_window();
            qDebug()<<"game_window build successfully";
            this->hide();
            game_w->show();
        });
    });

}
void texasui::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/Image/meinvbackground.png"));
}
texasui::~texasui()
{
    delete ui;
}
