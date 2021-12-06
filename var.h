#ifndef VAR_H
#define VAR_H
#include "player.h"
extern Player player;
extern Player opponent;
extern std::vector<std::pair<int,char>>River_Card;
extern jackPot pot;
extern bool round_change0;
extern bool round_change1;
extern bool round_change2;
extern bool round_change3;
class var
{
public:
    var();
};

#endif // VAR_H
