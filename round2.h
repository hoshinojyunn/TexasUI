#ifndef ROUND2_H
#define ROUND2_H

#include <QMainWindow>

namespace Ui {
class round2;
}

class round2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit round2(QWidget *parent = nullptr);
    ~round2();

private:
    Ui::round2 *ui;
};

#endif // ROUND2_H
