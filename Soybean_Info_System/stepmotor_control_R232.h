#ifndef STEPMOTOR_CONTROL_R232_H
#define STEPMOTOR_CONTROL_R232_H
#include <QDebug>
#include "serialport_send.h"



//int serial_open(QString PortName,QString Baud_rate); //重定义串口打开
//void serial_send(const QString &info);   //重新定义串口发送
void stepmotor_run(QString run_dir,int steper_angel,int steper_speed);

#endif // STEPMOTOR_CONTROL_R232_H
