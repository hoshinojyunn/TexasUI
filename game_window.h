#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include "player.h"
#include <QMainWindow>
#include <bits/stdc++.h>
#include "var.h"
namespace Ui {
class game_window;
}

class game_window : public QMainWindow
{
    Q_OBJECT
signals:
    void change_planer();
    void next_round();
public:
    //explicit game_window(QWidget *parent = nullptr);
    game_window(QWidget*parent=nullptr);
    ~game_window();
    void paintEvent(QPaintEvent*);
    void init();
    void display_yourPoker(const Player&player);
    void display_RiverCard(const std::vector<std::pair<int,char>>River_Card);
    void update_message(const Player&player,const Player&opponent);
    bool player_action(Player&player,Player&opponent,std::vector<std::pair<int,char>>River_Card,jackPot&pot);
    bool mechine_action(Player&player,Player&opponent,std::vector<std::pair<int,char>>River_Card,jackPot&pot);
    void disable(const Player&player,Player&opponent);
    void judge_fold();
    void enable();

private:
    Ui::game_window *ui;
};

#endif // GAME_WINDOW_H
