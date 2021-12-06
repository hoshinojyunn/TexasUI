#ifndef ROUND1_H
#define ROUND1_H

#include <QMainWindow>

namespace Ui {
class round1;
}

class round1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit round1(QWidget *parent = nullptr);
    ~round1();

private:
    Ui::round1 *ui;
};

#endif // ROUND1_H
