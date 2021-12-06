#ifndef PLAYER_H
#define PLAYER_H
#include <bits/stdc++.h>
#include "poker.h"
#include "jackPot.h"
#include <QObject>
class Player{
signals:
    static void player_signal();
    static void opponent_signal();
public:
    std::vector<std::pair<int,char>>Poker;
    int bonus{};//赌注
    int bet{};   //当前进度所下的赌注
    std::string identity;
    explicit Player(double bonus=20000){
        bet=0;
        this->bonus=bonus;
        //base(Poker);
    }
    void make_bet(jackPot&pot,int bet){  //下赌注
        bonus-=bet;
        this->bet+=bet;
        pot.total+=bet;
    }
    void follow(jackPot&pot,Player opponent){  //跟注
        int follow_bet=opponent.bet-bet;  //跟注需要加的钱
        bonus-=follow_bet;
        bet=opponent.bet;
        pot.total+=follow_bet;
    }
    void raise(jackPot&pot,Player opponent){  //加注
        int fill_bet=opponent.bet;  //加注量
        bonus-=fill_bet;
        bet=bet+fill_bet;
        pot.total+=fill_bet;
    }
    void display(){  //显示当前信息
        std::cout<<"your total bonus:"<<bonus<<std::endl;
        std::cout<<"now your bet:"<<bet<<std::endl;
        std::cout<<"identity:"<<identity<<std::endl;
        std::cout<<"your Hand Card:";
        for(int i=0;i!=Poker.size();++i){
            if(Poker[i].second=='A'){
                std::cout<<"diamond ";  //方块
            }else if(Poker[i].second=='B'){
                std::cout<<"club ";   //梅花
            }else if(Poker[i].second=='C'){
                std::cout<<"heart ";   //红桃
            }else if(Poker[i].second=='D'){
                std::cout<<"spade ";   //黑桃
            }
            if(Poker[i].first<=9){
                std::cout<<Poker[i].first+1;
            }else if(Poker[i].first==10){
                std::cout<<"J";
            }else if(Poker[i].first==11){
                std::cout<<"Q";
            }else if(Poker[i].first==12){
                std::cout<<"K";
            }else if(Poker[i].first==13){
                std::cout<<"A";
            }
            std::cout<<" ";
        }
        std::cout<<'\n';
    }
    void fold(jackPot&pot,Player&opponent){  //弃牌  直接结束本轮游戏
        opponent.bonus+=pot.total;
        opponent.bet=0;
        this->bet=0;
        pot.total=0;
    }
    void allin(jackPot&pot){
        this->bet+=this->bonus;
        pot.total+=this->bonus;
        this->bonus=0;
    }
    void check(){   //check 过牌 什么也不做
        return;
    }
    std::string make_plan(jackPot&pot,Player&opponent){
        std::string judge;
        std::string plan="invalid";
        std::cout<<"please make your plan.  fold,follow,check,raise or allin?";
        std::cin>>judge;
        if(judge=="fold"){
                std::cout<<"game over"<<std::endl;
                this->fold(pot,opponent);
                std::cout<<"continue?yes or no?";
                std::cin>>plan;
            }else if(judge=="check"){   //过牌无条件限制
                this->check();
                plan="check";
            }else if(judge=="raise"&&this->bonus>=opponent.bet){    //加注无条件限制
                this->raise(pot,opponent);
                plan="raise";
            }else if(judge=="follow"&&this->bet<opponent.bet&&this->bonus>opponent.bet-this->bet){
                this->follow(pot,opponent);
                plan="follow";
            }else if(judge=="follow"&&this->bonus<opponent.bet-this->bet){
                std::cout<<"you can't follow.arrange allin"<<std::endl;
                this->allin(pot);
                plan="all in";
            }else if(judge=="raise"&&this->bonus<opponent.bet){
                std::cout<<"you can't raise.arrange allin"<<std::endl;
                this->allin(pot);
                plan="all in";
            }
            else if(judge=="allin"){
                this->allin(pot);
                plan="all in";
            }
        return plan;
    }
};
#endif // PLAYER_H
