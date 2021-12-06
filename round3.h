#ifndef ROUND3_H
#define ROUND3_H

#include <QMainWindow>

namespace Ui {
class round3;
}

class round3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit round3(QWidget *parent = nullptr);
    ~round3();

private:
    Ui::round3 *ui;
};

#endif // ROUND3_H
