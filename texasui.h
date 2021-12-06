#ifndef TEXASUI_H
#define TEXASUI_H

#include <QMainWindow>

namespace Ui {
class texasui;
}

class texasui : public QMainWindow
{
    Q_OBJECT

public:
    explicit texasui(QWidget *parent = nullptr);
    ~texasui();

private:
    Ui::texasui *ui;
};

#endif // TEXASUI_H
