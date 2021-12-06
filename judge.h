#ifndef JUDGE_H
#define JUDGE_H
#include <string>
#include <vector>
class judge
{
public:
    judge();
};
bool judge_straight(const std::vector<std::pair<int, char>> &arr); //判顺子
bool judge_same_flush(const std::vector<std::pair<int, char>> &arr); //判同花
bool judge_pair(const std::vector<std::pair<int, char>> &arr);
bool judge_Three(const std::vector<std::pair<int, char>> &arr);
bool judge_twopair(const std::vector<std::pair<int, char>> &arr);
bool judge_straight_wh(const std::vector<std::pair<int, char>> &arr); //判同花顺
bool judge_straight_royal(const std::vector<std::pair<int, char>> &arr); //判皇家同花顺
bool judge_Four(const std::vector<std::pair<int, char>> &arr);
bool judge_Three_beltTwo(const std::vector<std::pair<int, char>> &arr);
bool judge_single(const std::vector<std::pair<int, char>> &arr); //判gao
std::string same_judge_high(const std::vector<std::pair<int, char>> &arr, const std::vector<std::pair<int, char>> &ar);
std::string same_judge_ThreeBeltTwo(const std::vector<std::pair<int, char>> &yourPoker, const std::vector<std::pair<int, char>> &opponentPoker);
std::string same_judge_sameFlush(const std::vector<std::pair<int, char>> &yourPoker, const std::vector<std::pair<int, char>> &opponentPoker);
std::string same_judge_straight(const std::vector<std::pair<int, char>> &yourPoker, const std::vector<std::pair<int, char>> &opponentPoker);
std::string same_judge_straight_royal(const std::vector<std::pair<int, char>> &yourPoker, const std::vector<std::pair<int, char>> &opponentPoker);
std::string same_judge_pair(const std::vector<std::pair<int, char>> &yourPoker, const std::vector<std::pair<int, char>> &opponentPoker);
std::string same_judge_Three(const std::vector<std::pair<int, char>> &yourPoker, const std::vector<std::pair<int, char>> &opponentPoker);
std::string same_judge_straight_wh(const std::vector<std::pair<int, char>> &yourPoker, const std::vector<std::pair<int, char>> &opponentPoker);
std::string same_judge_Four(const std::vector<std::pair<int, char>> &arr, const std::vector<std::pair<int, char>> &ar);
std::string same_judge_TwoPair(const std::vector<std::pair<int,char>>&arr,const std::vector<std::pair<int,char>>&ar);
std::string compare(const std::vector<std::pair<int, char>> &yourPoker, const std::vector<std::pair<int, char>> &opponentPoker);
#endif // JUDGE_H
