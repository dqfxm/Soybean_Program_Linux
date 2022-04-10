#include "my_switch.h"
#include "ui_my_switch.h"
#include <QDebug>

my_switch::my_switch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::my_switch)
{
    ui->setupUi(this);


}

my_switch::~my_switch()
{
    delete ui;
}
