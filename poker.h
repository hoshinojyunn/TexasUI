#ifndef POKER_H
#define POKER_H

#include<iostream>
#include<cstdlib>
#include<vector>
class Poker
{
public:
    Poker();
};
void base(std::vector<std::pair<int,char>>&Poker);//分配底牌
void RiverCard(std::vector<std::pair<int,char>>&River_Card);
void add(std::vector<std::pair<int, char>> &River_Card);
//函数返回桌面上是否有三张或三张以上花色相同的牌
void clearPoker(std::vector<std::pair<int,char>>&playerPoker,std::vector<std::pair<int,char>>&opponentPoker,std::vector<std::pair<int,char>>&River_Card);
void clearPoker(std::vector<std::pair<int,char>>&playerPoker,std::vector<std::pair<int,char>>&opponentPoker);
#endif // POKER_H
