#ifndef ROUND_H
#define ROUND_H
#include "player.h"


bool cmp(const std::pair<std::string,int>p1,const std::pair<std::string,int>p2);
void deliver(const std::vector<std::pair<int, char>> &playerRiver, std::vector<std::pair<int, char>> &Poker);
double cal_winRate(Player player, std::vector<std::pair<int, char>> River_Card);

double cal_RR(double winRate, int bet, const jackPot&pot);
void show_bet(const Player&player,const Player&opponent);

void show_River(const std::vector<std::pair<int,char>>&Poker);
std::string machine_judge(int RR);
std::string machine_make_plan(const Player&opponent,const Player&player,std::vector<std::pair<int,char>>River_Card,const jackPot&pot);


#endif // ROUND_H
