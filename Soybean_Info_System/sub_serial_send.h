#ifndef SUB_SERIAL_SEND_H
#define SUB_SERIAL_SEND_H

#include <QSerialPort>
#include <QDebug>
#include "transfor_data.h"
#include "string.h"


int serial_open(QString PortName,QString Baud_rate);
void serial_send(const QString &info);


#endif // SUB_SERIAL_SEND_H
