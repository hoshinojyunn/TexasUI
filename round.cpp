#include "round.h"
#include "judge.h"
using namespace std;
bool cmp(const pair<string,int>p1,const pair<string,int>p2){
    return p1.second<p2.second;
}
void deliver(const vector<pair<int, char>> &playerRiver, vector<pair<int, char>> &Poker)
{ //  模拟分配
    int paper_num[14][5];
    memset(paper_num, 0, sizeof(paper_num));

    for (auto i = 0; i != playerRiver.size(); ++i)
    { //模拟发对手牌时 排除已经出现的牌 即自己手牌加上河牌
        if (playerRiver[i].second == 'A')
        {
            paper_num[playerRiver[i].first][1] = 1;
        }
        else if (playerRiver[i].second == 'B')
        {
            paper_num[playerRiver[i].first][2] = 1;
        }
        else if (playerRiver[i].second == 'C')
        {
            paper_num[playerRiver[i].first][3] = 1;
        }
        else if (playerRiver[i].second == 'D')
        {
            paper_num[playerRiver[i].first][4] = 1;
        }
    }
    srand(time(nullptr));
    for (int i = 0; i < 2; i++)
    {
        int num = 0; //单张纸牌大小
        num = (rand() % 14);
        int NUM = (rand() % 4); //花色
        if (num)
        {
            if (NUM == 0 && paper_num[num][1] == 0)
            {
                Poker.emplace_back(std::make_pair(num, 'A'));
                paper_num[num][1] = 1;
            }
            else if (NUM == 1 && paper_num[num][2] == 0)
            {
                Poker.emplace_back(std::make_pair(num, 'B'));
                paper_num[num][2] = 1;
            }
            else if (NUM == 2 && paper_num[num][3] == 0)
            {
                Poker.emplace_back(std::make_pair(num, 'C'));
                paper_num[num][3] = 1;
            }
            else if (NUM == 3 && paper_num[num][4] == 0)
            {
                Poker.emplace_back(std::make_pair(num, 'D'));
                paper_num[num][4] = 1;
            }
            else
                i--;
        }
        else
            i--;
    }
}
double cal_winRate(Player player, vector<pair<int, char>> River_Card)
{
    int win = 0;
    int same = 0;
    int lose = 0;
    double EV;
    auto copy = River_Card;
    auto player_River = River_Card;
    player_River.insert(player_River.cbegin(), player.Poker.cbegin(), player.Poker.cend());
    // int opponentBet=opponent.getBet();
    // int playerBet=player.getBet();
    int count = 1000;
    while (count--)
    { //10000局比赛
        vector<pair<int, char>> opponentPoker;
        deliver(player_River, opponentPoker);
        River_Card.insert(River_Card.cbegin(), opponentPoker.cbegin(), opponentPoker.cend());
        string judge = compare(player_River, River_Card);
        if (judge == "bigger")
        {
            ++win;
        }
        else if (judge == "the same")
        {
            ++same;
        }
        else
        {
            ++lose;
        }
        River_Card = copy;
    }
    double winRate = (win+(same/2)) * 1.0 / 1000;
    double loseRate = (lose+(same/2)) * 1.0 / 1000;
    //cout << "winRate is:" << winRate << " loseRate is:" << loseRate;
    // EV=(winRate*(opponent.bet+()))-(loseRate*bet);
    // return EV;
    return winRate;
}

double cal_RR(double winRate, int bet, const jackPot&pot)
{
    double pot_odds = bet*1.0 / (bet + pot.total);
    double RR = winRate*1.0 / pot_odds;
    return RR;
}
void show_bet(const Player&player,const Player&opponent){
    cout<<"now the bet: yours:"<<player.bet<<" opponent's:"<<opponent.bet<<endl;
}

void show_River(const vector<pair<int,char>>&Poker){
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
        cout<<endl;
}
string machine_judge(double RR)
{
    string judge;
    srand(time(nullptr));
    if (RR < 0.8)
    {
        double jud = (rand()%100) * 1.0 / 101;
        if (jud < 0.95)
        {
            judge="fold";
        }
        else
        {
            judge="raise";
        }
    }
    else if (0.8 <= RR && RR < 1.0)
    {
        double jud = (rand()%100) * 1.0 / 101;
        if (jud < 0.8)
        {
            judge="fold";
        }
        else if (jud >= 0.8 && jud < 0.85)
        {
            judge="follow";
        }
        else
        {
            judge="raise";
        }
    }
    else if (RR >= 1.0 && RR < 1.3)
    {
        double jud = (rand()%100) * 1.0 / 101;
        if (jud > 0.6)
        {
            judge="follow";
        }
        else
        {
            judge="raise";
        }
    }
    else if (RR >= 1.3)
    {
        double jud = (rand()%100) * 1.0 / 101;
        if (jud < 0.3)
        {
            judge="follow";
        }
        else
        {
            judge="raise";
        }
    }
    return judge;
}
string machine_make_plan(const Player&opponent,const Player&player,vector<pair<int,char>>River_Card,const jackPot&pot){
    auto winRate = cal_winRate(opponent, River_Card);
    auto RR = cal_RR(winRate, player.bet - opponent.bet, pot);
    int count1=500;
    map<string,int>count;
    map<string,int>judge;
    while(count1--){
        auto machine_plan=machine_judge(RR);
        if(machine_plan=="fold"){
            ++count["fold"];
        }else if(machine_plan=="check"){
            ++count["check"];
        }else if(machine_plan=="follow"){
            ++count["follow"];
        }else if(machine_plan=="raise"){
            ++count["raise"];
        }
    }
    auto i=max_element(count.begin(),count.end(),cmp);    //做出最佳决定
    return i->first;
}
