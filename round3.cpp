#include "round3.h"
#include "ui_round3.h"
#include <QDebug>
#include <bits/stdc++.h>
#include "judge.h"
#include "round.h"
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QFont>
#include <QPalette>
using namespace std;
round3::round3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::round3)
{
    ui->setupUi(this);
    QFont ft;
    ft.setPointSize(12);
    ui->label_11->setFont(ft);
    ui->label_4->setFont(ft);
    ui->label_3->setFont(ft);
    ui->label_2->setFont(ft);
    ui->label->setFont(ft);
    //字号
    QPalette pa;
    QPalette bgc;
    pa.setColor(QPalette::WindowText,Qt::red);
    bgc.setColor(QPalette::Background,Qt::white);
    ui->label_11->setPalette(pa);
    ui->label_4->setPalette(pa);
    ui->label_3->setPalette(pa);
    ui->label_2->setPalette(pa);
    ui->label->setPalette(pa);
    ui->Widget_3->setAutoFillBackground(true);
    ui->widget_2->setAutoFillBackground(true);
    ui->Widget_3->setPalette(bgc);
    ui->widget_2->setPalette(bgc);
    //颜色
    init();
    ui->round_message->setText("ROUND fourth");
    qDebug()<<"build round3";
    setFixedSize(1200,800);
    setWindowTitle("TexasHoldem");
    add(River_Card);
    display_yourPoker(player);
    display_RiverCard(River_Card);
    this->update_message(player,opponent);
    qDebug()<<"player identify:"<<QString::fromStdString(player.identity);
    qDebug()<<"opponent identify:"<<QString::fromStdString(opponent.identity);
    /*初始化结束*/
    if(player.identity=="bigblind"){
        connect(this,&round3::start_compare,[&](){  //开始比较
            vector<pair<int,char>>player_River;
            vector<pair<int,char>>opponent_River;
            player_River.insert(player_River.begin(),player.Poker.begin(),player.Poker.end());
            player_River.insert(player_River.begin(),River_Card.begin(),River_Card.end());
            opponent_River.insert(opponent_River.begin(),opponent.Poker.begin(),opponent.Poker.end());
            opponent_River.insert(opponent_River.begin(),River_Card.begin(),River_Card.end());
            qDebug()<<player_River;
            qDebug()<<opponent_River;
            /*牌初始化*/
            auto mes=QMessageBox::information(nullptr,"compare","start to compare");
            this->show();
            qDebug()<<"start to compare";
            string result=compare(player_River,opponent_River);
            qDebug()<<QString::fromStdString(result);
            this->display_opponentPoker(opponent);
            clearPoker(player.Poker,opponent.Poker,River_Card);
            if(result=="bigger"){
                opponent.fold(pot,player);
                auto rb=QMessageBox::question(nullptr,"question","You Win!!!play one more?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                if(rb==QMessageBox::Yes){
                    if(player.bonus>0&&opponent.bonus>0){
                        texasui*ui=new texasui;
                        ui->show();
                        delete this;
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
            }else if(result=="smaller"){
                player.fold(pot,opponent);
                auto rb=QMessageBox::question(nullptr,"question","You Lose...play one more?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                if(rb==QMessageBox::Yes){
                    if(player.bonus>0&&opponent.bonus>0){
                        texasui*ui=new texasui;
                        ui->show();
                        delete this;
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
            }else{
                player.bonus+=pot.total/2;
                opponent.bonus+=pot.total/2;
                player.bet=0;
                opponent.bet=0;
                pot.total=0;
                auto rb=QMessageBox::question(nullptr,"question","Your Poker is the same Point with opponent.play one more?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                if(rb==QMessageBox::Yes){
                    if(player.bonus>0&&opponent.bonus>0){
                        texasui*ui=new texasui;
                        ui->show();
                        delete this;
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
        });
        connect(this,&round3::change_player,this,&round3::bigblind_player_judge,Qt::UniqueConnection);
        connect(this,&round3::change_opponent,this,&round3::bigblind_opponent_judge,Qt::UniqueConnection);
        emit this->change_player();
    }else{    //小盲 太难了 我囸尼玛
        connect(this,&round3::start_compare,[&](){  //开始比较
            vector<pair<int,char>>player_River;
            vector<pair<int,char>>opponent_River;
            player_River.insert(player_River.begin(),player.Poker.begin(),player.Poker.end());
            player_River.insert(player_River.begin(),River_Card.begin(),River_Card.end());
            opponent_River.insert(opponent_River.begin(),opponent.Poker.begin(),opponent.Poker.end());
            opponent_River.insert(opponent_River.begin(),River_Card.begin(),River_Card.end());
            qDebug()<<player_River;
            qDebug()<<opponent_River;
            /*牌初始化*/
            auto mes=QMessageBox::information(nullptr,"compare","start to compare");
            this->show();
            qDebug()<<"start to compare";
            string result=compare(player_River,opponent_River);
            qDebug()<<QString::fromStdString(result);
            this->display_opponentPoker(opponent);
            clearPoker(player.Poker,opponent.Poker,River_Card);
            if(result=="bigger"){
                opponent.fold(pot,player);
                auto rb=QMessageBox::question(nullptr,"question","You Win!!!play one more?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                if(rb==QMessageBox::Yes){
                    if(player.bonus>0&&opponent.bonus>0){
                        texasui*ui=new texasui;
                        ui->show();
                        delete this;
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
            }else if(result=="smaller"){
                player.fold(pot,opponent);
                auto rb=QMessageBox::question(nullptr,"question","You Lose...play one more?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                if(rb==QMessageBox::Yes){
                    if(player.bonus>0&&opponent.bonus>0){
                        texasui*ui=new texasui;
                        ui->show();
                        delete this;
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
            }else{
                player.bonus+=pot.total/2;
                opponent.bonus+=pot.total/2;
                player.bet=0;
                opponent.bet=0;
                pot.total=0;
                auto rb=QMessageBox::question(nullptr,"question","Your Poker is the same Point with opponent.play one more?",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
                if(rb==QMessageBox::Yes){
                    if(player.bonus>0&&opponent.bonus>0){
                        texasui*ui=new texasui;
                        ui->show();
                        delete this;
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
        });
        connect(this,&round3::change_player,this,&round3::smallblind_player_judge,Qt::UniqueConnection);
        connect(this,&round3::change_opponent,this,&round3::smallblind_opponent_judge,Qt::UniqueConnection);
        emit this->change_opponent();
    }
}
void round3::init(){   //下次再改
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
void round3::judge_fold(){
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
void round3::disable(const Player&player,Player&opponent){
    if(player.bet>=opponent.bet){
        ui->follow->setDisabled(true);
    }
    if(player.bonus<opponent.bet-player.bet){
        ui->follow->setDisabled(true);
    }
    if(player.bonus<opponent.bet){
        ui->raise->setDisabled(true);
    }
    if(player.bet!=opponent.bet){
        ui->check->setDisabled(true);
    }
    if(player.bonus==0){
        ui->allin->setDisabled(true);
    }
}
void round3::enable(){
    ui->follow->setEnabled(true);
    ui->raise->setEnabled(true);
    ui->check->setEnabled(true);
}
void round3::display_yourPoker(const Player &player){
    QImage pix1;
    QString path1=":/Image/"+QString::number(player.Poker[0].first)+player.Poker[0].second+".jpg";
    //qDebug()<<"path1 is:"<<path1;
    pix1.load(path1);
    pix1.scaled(ui->your_Poker1->size(),Qt::KeepAspectRatio);
    QImage pix2;
    QString path2=":/Image/"+QString::number(player.Poker[1].first)+player.Poker[1].second+".jpg";
    //qDebug()<<"path2 is:"<<path2;
    pix2.load(path2);
    pix2.scaled(ui->your_Poker2->size(),Qt::KeepAspectRatio);
    ui->your_Poker1->setScaledContents(true);
    ui->your_Poker2->setScaledContents(true);
    ui->your_Poker1->setPixmap(QPixmap::fromImage(pix1));
    ui->your_Poker2->setPixmap(QPixmap::fromImage(pix2));
}
void round3::display_opponentPoker(const Player &opponent){
    QImage pix1;
    QString path1=":/Image/"+QString::number(opponent.Poker[0].first)+opponent.Poker[0].second+".jpg";
    //qDebug()<<"path1 is:"<<path1;
    pix1.load(path1);
    pix1.scaled(ui->opponent_Poker1->size(),Qt::KeepAspectRatio);
    QImage pix2;
    QString path2=":/Image/"+QString::number(opponent.Poker[1].first)+opponent.Poker[1].second+".jpg";
    //qDebug()<<"path2 is:"<<path2;
    pix2.load(path2);
    pix2.scaled(ui->opponent_Poker2->size(),Qt::KeepAspectRatio);
    ui->opponent_Poker1->setScaledContents(true);
    ui->opponent_Poker2->setScaledContents(true);
    ui->opponent_Poker1->setPixmap(QPixmap::fromImage(pix1));
    ui->opponent_Poker2->setPixmap(QPixmap::fromImage(pix2));
}
void round3::display_RiverCard(const std::vector<std::pair<int, char> > River_Card){
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
void round3::update_message(const Player &player, const Player &opponent){
    ui->your_identify->setText(QString::fromStdString(player.identity));
    ui->your_bonus->setText(QString::number(player.bonus));
    ui->your_bet->setText(QString::number(player.bet));
    ui->opponent_identify->setText(QString::fromStdString(opponent.identity));
    ui->opponent_bonus->setText(QString::number(opponent.bonus));
    ui->opponent_bet->setText(QString::number(opponent.bet));
}

string round3::mechine_action(Player &player, Player &opponent,vector<pair<int,char>>&River_Card, jackPot &pot){
    auto mechine_plan=machine_make_plan(opponent,player,River_Card,pot);
    if(mechine_plan=="fold"){
        opponent.fold(pot,player);
        clearPoker(player.Poker,opponent.Poker,River_Card);
        ui->opponent_message->setText("opponent fold");
        auto rb=QMessageBox::question(nullptr,"question","opponent has fold.would you wanna play one more?",
                                      QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        if(rb==QMessageBox::Yes){
            if(player.bonus>0&&opponent.bonus>0){
                texasui*ui=new texasui;
                ui->show();
                this->deleteLater();
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
    }else if(mechine_plan=="check"){
        opponent.check();
        ui->opponent_message->setText("opponent check");
    }else if(mechine_plan=="follow"&&opponent.bonus>=player.bet-opponent.bet){
        opponent.follow(pot,player);
        ui->opponent_message->setText("opponent follow");
    }else if(mechine_plan=="raise"&&opponent.bonus>=player.bet){
        opponent.raise(pot,player);
        ui->opponent_message->setText("opponent raise");
    }else if(mechine_plan=="follow"&&opponent.bonus<player.bet-opponent.bet){
        opponent.allin(pot);
        ui->opponent_message->setText("opponent all in");
    }else if(mechine_plan=="raise"&&opponent.bonus<player.bet){
        opponent.allin(pot);
        ui->opponent_message->setText("opponent all in");
    }
    return mechine_plan;
}

void round3::paintEvent(QPaintEvent *){
    //qDebug()<<"paint the background";
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/Image/meinvbackground.png"));
}
void round3::bigblind_player_fold(){
    player.fold(pot,opponent);
    update_message(player,opponent);
    judge_fold();
}
void round3::bigblind_player_check(){
    player.check();
    update_message(player,opponent);
    emit this->change_opponent();
}
void round3::bigblind_player_follow(){
    player.follow(pot,opponent);
    update_message(player,opponent);
    emit this->change_opponent();
}
void round3::bigblind_player_raise(){
    player.raise(pot,opponent);
    update_message(player,opponent);
    emit this->change_opponent();
}
void round3::bigblind_player_allin(){
    player.allin(pot);
    update_message(player,opponent);
    if(player.bonus==0&&player.bet<opponent.bet){  //做无筹码情况判断
        pot.total-=opponent.bet-player.bet;
        opponent.bonus+=opponent.bet-player.bet;
        opponent.bet=player.bet;
        update_message(player,opponent);
    }
    emit this->change_opponent();
}
void round3::smallblind_player_fold(){
    player.fold(pot,opponent);
    update_message(player,opponent);
    judge_fold();
}
void round3::smallblind_player_check(){
    player.check();
    update_message(player,opponent);
    emit this->start_compare();
}
void round3::smallblind_player_follow(){
    player.follow(pot,opponent);
    update_message(player,opponent);
    emit this->start_compare();
}
void round3::smallblind_player_raise(){
    player.raise(pot,opponent);
    update_message(player,opponent);
    emit this->change_opponent();
}
void round3::smallblind_player_allin(){
    player.allin(pot);
    update_message(player,opponent);
    if(player.bonus==0&&player.bet<opponent.bet){  //做无筹码情况判断
        pot.total-=opponent.bet-player.bet;
        opponent.bonus+=opponent.bet-player.bet;
        opponent.bet=player.bet;
        update_message(player,opponent);
    }
    if(opponent.bet==player.bet){
        emit this->start_compare();
    }else{
        emit this->change_opponent();
    }
}
void round3::bigblind_player_judge(){
    qDebug()<<"into bigblind_player_judge";
    enable();
    disable(player,opponent);
    connect(ui->fold,&QPushButton::clicked,this,&round3::bigblind_player_fold,Qt::UniqueConnection);
    connect(ui->check,&QPushButton::clicked,this,&round3::bigblind_player_check,Qt::UniqueConnection);
    connect(ui->follow,&QPushButton::clicked,this,&round3::bigblind_player_follow,Qt::UniqueConnection);
    connect(ui->raise,&QPushButton::clicked,this,&round3::bigblind_player_raise,Qt::UniqueConnection);
    connect(ui->allin,&QPushButton::clicked,this,&round3::bigblind_player_allin,Qt::UniqueConnection);
}
void round3::bigblind_opponent_judge(){
    qDebug()<<"into bigblind_opponent_judge";
    string plan;
    if(opponent.bet<player.bet){
        plan=this->mechine_action(player,opponent,River_Card,pot);
        update_message(player,opponent);
        enable();
        disable(player,opponent);
    }else{
        opponent.check();
        ui->opponent_message->setText("opponent check");
        plan="check";
        enable();
        disable(player,opponent);
    }
//    if(plan=="fold"){
//        delete this;
//    }
    qDebug()<<"opponent's bet:"<<opponent.bet;
    if(opponent.bonus==0&&opponent.bet<player.bet){
        pot.total-=player.bet-opponent.bet;
        player.bonus+=player.bet-opponent.bet;
        player.bet=opponent.bet;
        update_message(player,opponent);
    }

    if(opponent.bet==player.bet&&plan!="follow"&&plan!="fold"){
        emit this->start_compare();
    }else{
        emit this->change_player();
    }
}
void round3::smallblind_player_judge(){
    qDebug()<<"into smallblind_player_judge";
    enable();
    disable(player,opponent);
    connect(ui->fold,&QPushButton::clicked,this,&round3::smallblind_player_fold,Qt::UniqueConnection);
    connect(ui->check,&QPushButton::clicked,this,&round3::smallblind_player_check,Qt::UniqueConnection);
    connect(ui->follow,&QPushButton::clicked,this,&round3::smallblind_player_follow,Qt::UniqueConnection);
    connect(ui->raise,&QPushButton::clicked,this,&round3::smallblind_player_raise,Qt::UniqueConnection);
    connect(ui->allin,&QPushButton::clicked,this,&round3::smallblind_player_allin,Qt::UniqueConnection);

}
void round3::smallblind_opponent_judge(){
    qDebug()<<"into smallblind_opponent_judge";
    string plan;
    if(opponent.bet<player.bet){
        plan=this->mechine_action(player,opponent,River_Card,pot);
        update_message(player,opponent);
        enable();
        disable(player,opponent);
    }else{
        opponent.check();
        ui->opponent_message->setText("opponent check");
        plan="check";
        enable();
        disable(player,opponent);
    }
//    if(plan=="fold"){
//        delete this;
//    }
    if(opponent.bonus==0&&opponent.bet<player.bet){
        pot.total-=player.bet-opponent.bet;
        player.bonus+=player.bet-opponent.bet;
        player.bet=opponent.bet;
        update_message(player,opponent);
    }
    emit this->change_player();
}
round3::~round3()
{
    delete ui;
}
