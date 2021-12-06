#include "game_window.h"
#include <bits/stdc++.h>
#include "ui_game_window.h"
#include "player.h"
#include "judge.h"
#include "round.h"
#include "round1.h"
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
using namespace std;
game_window::game_window(QWidget *parent) :
    QMainWindow (parent),
    ui(new Ui::game_window)
{
    qDebug()<<"build game_window";
    ui->setupUi(this);
    this->init();
    ui->round_message->setText("ROUND first");
    setFixedSize(1200,800);
    setWindowTitle("TexasHoldem");
    srand(time(0));
    if((rand()%100)*1.0/101>=0.5){
        player.identity="bigblind";
        opponent.identity="smallblind";
        player.make_bet(pot,100);
        opponent.make_bet(pot,50);
    }
    else{
        player.identity="smallblind";
        opponent.identity="bigblind";
        player.make_bet(pot,50);
        opponent.make_bet(pot,100);
    }
    update_message(player,opponent);
    base(player.Poker);
    base(opponent.Poker);
    display_yourPoker(player);

    /*流程*/
    if(player.identity=="smallblind"){
        //disable(player,opponent);
        ui->your_message->setText("your turn.");
        connect(ui->fold,&QPushButton::clicked,[&](){
            player.fold(pot,opponent);
            update_message(player,opponent);
            judge_fold();
        });
        connect(ui->check,&QPushButton::clicked,[&](){
            player.check();
            update_message(player,opponent);
            emit this->change_planer();

        });
        connect(ui->follow,&QPushButton::clicked,[&](){
            player.follow(pot,opponent);
            update_message(player,opponent);
            emit this->change_planer();

        });
        connect(ui->raise,&QPushButton::clicked,[&](){
            player.raise(pot,opponent);
            update_message(player,opponent);
            emit this->change_planer();
        });
        connect(ui->allin,&QPushButton::clicked,[&](){
            player.allin(pot);
            update_message(player,opponent);
            emit this->change_planer();
        });
        /*机器*/
        connect(this,&game_window::change_planer,[&](){
            //this->mechine_action(player,opponent,River_Card,pot);
            opponent.check();
            ui->opponent_message->setText("opponent check");
            QMessageBox::information(nullptr,"information","into next round");
            emit this->next_round();
        });
    }else{
        enable();
        disable(player,opponent);
        //this->mechine_action(player,opponent,River_Card,pot);
        opponent.check();
        ui->opponent_message->setText("opponent check");
        //disable(player,opponent);
        ui->your_message->setText("your turn");
        connect(ui->fold,&QPushButton::clicked,[&](){
            player.fold(pot,opponent);
            update_message(player,opponent);
            judge_fold();
        });
        connect(ui->check,&QPushButton::clicked,[&](){
            player.check();
            update_message(player,opponent);
            QMessageBox::information(nullptr,"information","into next round");
            emit this->next_round();
        });
        connect(ui->follow,&QPushButton::clicked,[&](){
            player.follow(pot,opponent);
            update_message(player,opponent);
            QMessageBox::information(nullptr,"information","into next round");
            emit this->next_round();
        });
        connect(ui->raise,&QPushButton::clicked,[&](){
            player.raise(pot,opponent);
            update_message(player,opponent);
            QMessageBox::information(nullptr,"information","into next round");
            emit this->next_round();
        });
        connect(ui->allin,&QPushButton::clicked,[&](){
            player.allin(pot);
            update_message(player,opponent);
            QMessageBox::information(nullptr,"information","into next round");
            emit this->next_round();
        });
    }
    update_message(player,opponent);
    connect(this,&game_window::next_round,[=](){
        QTimer::singleShot(100,this,[=](){
            qDebug()<<"click button";
            this->hide();
            round1*r1=new round1();
            delete this;
            r1->show();
        });
    });
}
void game_window::judge_fold(){
    clearPoker(player.Poker,opponent.Poker,River_Card);
    auto rb=QMessageBox::question(nullptr,"question","would you wanna play one more?",
                                  QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if(rb==QMessageBox::Yes){
        if(player.bonus>0&&opponent.bonus>0){
            this->deleteLater();
            texasui*ui=new texasui;
            ui->show();
        }else if(player.bonus<=0){
            QMessageBox::information(nullptr,"information","your bonus is less than 0");
            exit(0);
        }else if(opponent.bonus<=0){
            QMessageBox::information(nullptr,"information","opponent's bonus is less than 0");
            exit(0);
        }
    }else{
        exit(0);
    }
}
void game_window::init(){   //下次再改
    QImage pix;
    pix.load(":/Image/pokerback.jpg");
    pix.scaled(ui->your_Poker1->size(),Qt::KeepAspectRatio);

    ui->your_Poker1->setScaledContents(true);
    ui->your_Poker2->setScaledContents(true);
    ui->opponent_Poker1->setScaledContents(true);
    ui->opponent_Poker2->setScaledContents(true);
    ui->River1->setScaledContents(true);
    ui->River2->setScaledContents(true);
    ui->River3->setScaledContents(true);
    ui->River4->setScaledContents(true);
    ui->River5->setScaledContents(true);
    ui->your_Poker1->setPixmap(QPixmap::fromImage(pix));
    ui->your_Poker2->setPixmap(QPixmap::fromImage(pix));
    ui->River1->setPixmap(QPixmap::fromImage(pix));
    ui->River2->setPixmap(QPixmap::fromImage(pix));
    ui->River3->setPixmap(QPixmap::fromImage(pix));
    ui->River4->setPixmap(QPixmap::fromImage(pix));
    ui->River5->setPixmap(QPixmap::fromImage(pix));
    ui->opponent_Poker1->setPixmap(QPixmap::fromImage(pix));
    ui->opponent_Poker2->setPixmap(QPixmap::fromImage(pix));
}
void game_window::disable(const Player&player,Player&opponent){
    if(player.bet>=opponent.bet){
        ui->follow->setDisabled(true);
    }
    if(player.bonus<opponent.bet-player.bet){
        ui->follow->setDisabled(true);
    }
    if(player.bonus<opponent.bet){
        ui->raise->setDisabled(true);
    }
    if(player.bonus==0){
        ui->allin->setDisabled(true);
    }
}
void game_window::enable(){
    ui->follow->setEnabled(true);
    ui->raise->setEnabled(true);
}
void game_window::display_yourPoker(const Player &player){
    QImage pix1;
    QString path1=":/Image/"+QString::number(player.Poker[0].first)+player.Poker[0].second+".jpg";
    qDebug()<<"path1 is:"<<path1;
    pix1.load(path1);
    pix1.scaled(ui->your_Poker1->size(),Qt::KeepAspectRatio);
    QImage pix2;
    QString path2=":/Image/"+QString::number(player.Poker[1].first)+player.Poker[1].second+".jpg";
    qDebug()<<"path2 is:"<<path2;
    pix2.load(path2);
    pix2.scaled(ui->your_Poker2->size(),Qt::KeepAspectRatio);
    ui->your_Poker1->setScaledContents(true);
    ui->your_Poker2->setScaledContents(true);
    ui->your_Poker1->setPixmap(QPixmap::fromImage(pix1));
    ui->your_Poker2->setPixmap(QPixmap::fromImage(pix2));
}

void game_window::display_RiverCard(const std::vector<std::pair<int, char> > River_Card){
    for(int i=0;i<River_Card.size();++i){
        QImage pix1;
        QString path=":/Image/"+QString::number(River_Card[i].first)+River_Card[i].second+".jpg";
        pix1.load(path);
        pix1.scaled(ui->River1->size(),Qt::KeepAspectRatio);
        switch(i){
            case 0:
                ui->River1->setScaledContents(true);
                ui->River1->setPixmap(QPixmap::fromImage(pix1));
                break;
            case 1:
                ui->River2->setScaledContents(true);
                ui->River2->setPixmap(QPixmap::fromImage(pix1));
                break;
            case 2:
                ui->River3->setScaledContents(true);
                ui->River3->setPixmap(QPixmap::fromImage(pix1));
                break;
            case 3:
                ui->River4->setScaledContents(true);
                ui->River4->setPixmap(QPixmap::fromImage(pix1));
                break;
            case 4:
                ui->River5->setScaledContents(true);
                ui->River5->setPixmap(QPixmap::fromImage(pix1));
                break;

        }
    }
}
void game_window::update_message(const Player &player, const Player &opponent){
    ui->your_identify->setText(QString::fromStdString(player.identity));
    ui->your_bonus->setText(QString::number(player.bonus));
    ui->your_bet->setText(QString::number(player.bet));
    ui->opponent_identify->setText(QString::fromStdString(opponent.identity));
    ui->opponent_bonus->setText(QString::number(opponent.bonus));
    ui->opponent_bet->setText(QString::number(opponent.bet));
}

bool game_window::mechine_action(Player &player, Player &opponent,vector<pair<int,char>>River_Card, jackPot &pot){
    auto mechine_plan=machine_make_plan(opponent,player,River_Card,pot);
    if(mechine_plan=="fold"){
        opponent.fold(pot,player);
        clearPoker(player.Poker,opponent.Poker,River_Card);
        ui->opponent_message->setText("opponent fold");
    }else if(mechine_plan=="check"){
        opponent.check();
        ui->opponent_message->setText("opponent check");
    }else if(mechine_plan=="follow"){
        opponent.follow(pot,player);
        ui->opponent_message->setText("opponent follow");
    }else if(mechine_plan=="raise"){
        opponent.raise(pot,player);
        ui->opponent_message->setText("opponent raise");
    }else if(mechine_plan=="allin"){
        opponent.allin(pot);
        ui->opponent_message->setText("opponent all in");
    }
}
void game_window::paintEvent(QPaintEvent *){
    //qDebug()<<"paint the background";
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/Image/background.jpg"));
}

game_window::~game_window()
{
    delete ui;
}
