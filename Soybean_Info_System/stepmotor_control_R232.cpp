#include "stepmotor_control_R232.h"


void stepmotor_run(QString run_dir,int steper_angel,int steper_speed)
{
    //    QString current_port = "ttyUSB1";
    //    QString current_baud = "57600";
//    serial_open("ttyUSB1", "57600");
    QString steper_addr = "01";  //伺服电机地址
//  QString run_dir = "00"; //步进电机方向
    QString steper_angel_hex;
    QString steper_speed_hex;
    QString send_order;

    steper_angel = qRound(steper_angel/0.9);      //400个脉冲一圈。
    steper_speed = 1000000/(steper_speed*400/60);   //频率转化成转速 r/min ,steper_speed<90
    qDebug() << "steper_speed" << steper_speed;
    steper_speed_hex = QString("%1").arg(steper_speed,4,16,QLatin1Char('0'));//int转16进制，并补0
    steper_angel_hex = QString("%1").arg(steper_angel,4,16,QLatin1Char('0'));//k为int型或char型都可;
    send_order = steper_addr+run_dir+steper_speed_hex+steper_angel_hex+"0d0a";
    serialport_send(send_order);

}
