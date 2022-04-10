#ifndef SERIALPORT_INIT_H
#define SERIALPORT_INIT_H

#include <QtSerialPort/QtSerialPort>
#include <QList>

QList<QSerialPortInfo> serialList;
QString* serialport_init();

#endif // SERIALPORT_INIT_H
