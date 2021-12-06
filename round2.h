#ifndef ROUND2_H
#define ROUND2_H

#include <QMainWindow>
#include <QMainWindow>
#include "player.h"
#include "var.h"
#include "texasui.h"
namespace Ui {
class round2;
}

class round2 : public QMainWindow
{
    Q_OBJECT
signals:
    void change_planer();
    void next_round();
public:
    explicit round2(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void init();
    void display_yourPoker(const Player&player);
    void display_RiverCard(const std::vector<std::pair<int,char>>River_Card);
    void update_message(const Player&player,const Player&opponent);
    std::string mechine_action(Player&player,Player&opponent,std::vector<std::pair<int,char>>&River_Card,jackPot&pot);
    void disable(const Player&player,Player&opponent);
    void judge_fold();
    ~round2();

private:
    Ui::round2 *ui;
};

#endif // ROUND2_H
