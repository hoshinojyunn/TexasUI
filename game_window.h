#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>

namespace Ui {
class game_window;
}

class game_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit game_window(QWidget *parent = nullptr);
    ~game_window();

private:
    Ui::game_window *ui;
};

#endif // GAME_WINDOW_H
