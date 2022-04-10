#ifndef MY_SWITCH_H
#define MY_SWITCH_H

#include <QWidget>
#include "switchbutton.h"

namespace Ui {
class my_switch;
}

class my_switch : public QWidget
{
    Q_OBJECT

public:
    explicit my_switch(QWidget *parent = nullptr);
    ~my_switch();

signals:


private:
    Ui::my_switch *ui;
         //发送名字测试

public slots:


private slots:

};

#endif // MY_SWITCH_H
