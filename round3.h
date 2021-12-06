#ifndef ROUND3_H
#define ROUND3_H
#include <QMainWindow>
#include <QMainWindow>
#include <QMainWindow>
#include "player.h"
#include "var.h"
#include "texasui.h"
namespace Ui {
class round3;
}

class round3 : public QMainWindow
{
    Q_OBJECT

signals:
    void change_planer();
    void start_compare();
    void judge_same_bet();
    void arrange_same();
    void judge1();
    void change_player();
    void change_opponent();
public slots:
    void bigblind_player_judge();
    void bigblind_opponent_judge();
    void smallblind_player_judge();
    void smallblind_opponent_judge();
    void bigblind_player_fold();
    void bigblind_player_check();
    void bigblind_player_follow();
    void bigblind_player_raise();
    void bigblind_player_allin();
    void smallblind_player_fold();
    void smallblind_player_check();
    void smallblind_player_follow();
    void smallblind_player_raise();
    void smallblind_player_allin();
public:
    explicit round3(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void init();
    void display_yourPoker(const Player&player);
    void display_opponentPoker(const Player&opponent);
    void display_RiverCard(const std::vector<std::pair<int,char>>River_Card);
    void update_message(const Player&player,const Player&opponent);
    std::string mechine_action(Player&player,Player&opponent,std::vector<std::pair<int,char>>&River_Card,jackPot&pot);
    void disable(const Player&player,Player&opponent);
    void enable();
    void judge_fold();
    ~round3();

private:
    Ui::round3 *ui;
};

#endif // ROUND3_H
