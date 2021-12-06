#ifndef TEXASUI_H
#define TEXASUI_H
#include <bits/stdc++.h>
#include <QMainWindow>
#include "player.h"
namespace Ui {
class texasui;
}

class texasui : public QMainWindow
{
    Q_OBJECT
signals:

public:
    explicit texasui(QWidget *parent = nullptr);
    ~texasui();
    void paintEvent(QPaintEvent*);
private:
    Ui::texasui *ui;
};

#endif // TEXASUI_H
