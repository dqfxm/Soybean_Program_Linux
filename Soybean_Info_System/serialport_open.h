#ifndef SERIALPORT_OPEN_H
#define SERIALPORT_OPEN_H
#include<QSerialPort>

extern QSerialPort *m_serialPort;
QSerialPort *m_serialPort = new QSerialPort();

int serialport_open(QString PortName,QString Baud_rate);

#endif // SERIALPORT_OPEN_H
