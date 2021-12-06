#ifndef ROUND1_H
#define ROUND1_H

#include <QMainWindow>
#include "player.h"
#include "var.h"
#include "texasui.h"
//extern Player player;
//extern Player opponent;
//extern std::vector<std::pair<int,char>>River_Card;
//extern jackPot pot;
//extern bool round_change0;
//extern bool round_change1;
//extern bool round_change2;
//extern bool round_change3;
namespace Ui {
class round1;
}

class round1 : public QMainWindow
{
    Q_OBJECT
signals:
    void change_planer();
    void next_round();
public:
    explicit round1(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void init();
    void display_yourPoker(const Player&player);
    void display_RiverCard(const std::vector<std::pair<int,char>>River_Card);
    void update_message(const Player&player,const Player&opponent);
    std::string mechine_action(Player&player,Player&opponent,std::vector<std::pair<int,char>>&River_Card,jackPot&pot);
    void disable(const Player&player,Player&opponent);
    void judge_fold();
    ~round1();

private:
    Ui::round1 *ui;
};

#endif // ROUND1_H
