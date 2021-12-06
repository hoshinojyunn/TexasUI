#include "poker.h"
#include <bits/stdc++.h>

Poker::Poker()
{

}
const int N=13;
const int M=4;
const int R=0;
const int E=1;
int paper_num[N+1][M+1];
void base(std::vector<std::pair<int,char>>&Poker){//分配底牌
    srand(time(nullptr));
    for(int i=0;i<2;i++){
        int num=0;               //单张纸牌大小
        num=(rand()%14);
        int NUM=(rand()%4);      //花色
        if(num){
            if(NUM==0 && paper_num[num][1]==R ){
                Poker.emplace_back(std::make_pair(num,'A'));
                paper_num[num][1]=E;
            }
            else if(NUM==1 && paper_num[num][2]==R ){
                Poker.emplace_back(std::make_pair(num,'B'));
                paper_num [num][2]=E;
            }
            else if(NUM==2 && paper_num[num][3]==R ){
                Poker.emplace_back(std::make_pair(num,'C'));
                paper_num [num][3]=E;
            }
            else if(NUM==3 && paper_num[num][4]==R ){
                Poker.emplace_back(std::make_pair(num,'D'));
                paper_num [num][4]=E;
            }
            else i--;
        }
        else i--;
    }
}
void RiverCard(std::vector<std::pair<int,char>>&River_Card){
    srand(time(nullptr));
    for(int i=0;i<3;i++){
        int num=0;               //单张纸牌大小
        num=(rand()%14);
        int NUM=(rand()%4);      //花色
        if(num){
            if(NUM==0 && paper_num[num][1]==R ){
                River_Card.emplace_back(std::make_pair(num,'A'));
                paper_num[num][1]=E;
            }
            else if(NUM==1 && paper_num[num][2]==R ){
                River_Card.emplace_back(std::make_pair(num,'B'));
                paper_num [num][2]=E;
            }
            else if(NUM==2 && paper_num[num][3]==R ){
                River_Card.emplace_back(std::make_pair(num,'C'));
                paper_num [num][3]=E;
            }
            else if(NUM==3 && paper_num[num][4]==R ){
                River_Card.emplace_back(std::make_pair(num,'D'));
                paper_num [num][4]=E;
            }
            else i--;
        }
        else i--;
    }
}
void add(std::vector<std::pair<int, char>> &River_Card) {
    srand(time(nullptr));
    for(int i=0;i<1;i++){
        int num=0;               //单张纸牌大小
        num=(rand()%14);
        int NUM=(rand()%4);      //花色
        if(num){
            if(NUM==0 && paper_num[num][1]==R ){
                River_Card.emplace_back(std::make_pair(num,'A'));
                paper_num[num][1]=E;
            }
            else if(NUM==1 && paper_num[num][2]==R ){
                River_Card.emplace_back(std::make_pair(num,'B'));
                paper_num [num][2]=E;
            }
            else if(NUM==2 && paper_num[num][3]==R ){
                River_Card.emplace_back(std::make_pair(num,'C'));
                paper_num [num][3]=E;
            }
            else if(NUM==3 && paper_num[num][4]==R ){
                River_Card.emplace_back(std::make_pair(num,'D'));
                paper_num [num][4]=E;
            }
            else i--;
        }
        else i--;
    }
}
//函数返回桌面上是否有三张或三张以上花色相同的牌
void clearPoker(std::vector<std::pair<int,char>>&playerPoker,std::vector<std::pair<int,char>>&opponentPoker,std::vector<std::pair<int,char>>&River_Card){
    playerPoker.clear();
    opponentPoker.clear();
    River_Card.clear();
    memset(paper_num,0,sizeof(paper_num));
}
void clearPoker(std::vector<std::pair<int,char>>&playerPoker,std::vector<std::pair<int,char>>&opponentPoker){
    playerPoker.clear();
    opponentPoker.clear();
    memset(paper_num,0,sizeof(paper_num));
}
