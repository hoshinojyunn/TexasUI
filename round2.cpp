#include "round2.h"
#include "ui_round2.h"
#include <QDebug>
#include <bits/stdc++.h>
#include "round.h"
#include "round3.h"
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QFont>
#include <QPalette>
using namespace std;
round2::round2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::round2)
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
    ui->round_message->setText("ROUND third");
    qDebug()<<"build round2";
    setFixedSize(1200,800);
    setWindowTitle("TexasHoldem");
    add(River_Card);
    display_yourPoker(player);
    display_RiverCard(River_Card);
    this->update_message(player,opponent);
    /*初始化结束*/
    if(player.identity=="bigblind"){
        disable(player,opponent);
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
        connect(this,&round2::change_planer,[&](){
            if(opponent.bet<player.bet){
                auto plan=this->mechine_action(player,opponent,River_Card,pot);
                update_message(player,opponent);
                if(plan!="fold"){
                    QMessageBox::information(nullptr,"information","into next round");
                    emit this->next_round();
                }
            }else{
                opponent.check();
                ui->opponent_message->setText("opponent check");
                QMessageBox::information(nullptr,"information","into next round");
                emit this->next_round();
            }
        });
    }else{
        if(opponent.bet<player.bet){
            this->mechine_action(player,opponent,River_Card,pot);
            update_message(player,opponent);
        }else{
            opponent.check();
            ui->opponent_message->setText("opponent check");
        }
        disable(player,opponent);
        ui->your_message->setText("your turn");
        connect(ui->fold,&QPushButton::clicked,[&](){
            player.fold(pot,opponent);
            update_message(player,opponent);
            QMessageBox::information(nullptr,"information","into next round");
            emit this->next_round();
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
    connect(this,&round2::next_round,[=](){
        QTimer::singleShot(100,this,[=](){
            qDebug()<<"next round3";
            this->hide();
            round3*r3=new round3();
            delete this;
            r3->show();
        });
    });
}
void round2::init(){   //下次再改
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
void round2::judge_fold(){
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
void round2::disable(const Player&player,Player&opponent){
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
void round2::display_yourPoker(const Player &player){
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

void round2::display_RiverCard(const std::vector<std::pair<int, char> > River_Card){
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
void round2::update_message(const Player &player, const Player &opponent){
    ui->your_identify->setText(QString::fromStdString(player.identity));
    ui->your_bonus->setText(QString::number(player.bonus));
    ui->your_bet->setText(QString::number(player.bet));
    ui->opponent_identify->setText(QString::fromStdString(opponent.identity));
    ui->opponent_bonus->setText(QString::number(opponent.bonus));
    ui->opponent_bet->setText(QString::number(opponent.bet));
}

string round2::mechine_action(Player &player, Player &opponent,vector<pair<int,char>>&River_Card, jackPot &pot){
    auto mechine_plan=machine_make_plan(opponent,player,River_Card,pot);
    if(mechine_plan=="fold"){
        opponent.fold(pot,player);
        clearPoker(player.Poker,opponent.Poker,River_Card);
        ui->opponent_message->setText("opponent fold");
        //ui->your_message->setText("opponent has fold.would you wanna play one more?click the start");
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
void round2::paintEvent(QPaintEvent *){
    //qDebug()<<"paint the background";
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/Image/meinvbackground.png"));
}
round2::~round2()
{
    delete ui;
}
