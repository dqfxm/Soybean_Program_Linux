#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QObject>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class SerialThread : public QThread
{
    Q_OBJECT

public:
    SerialThread(QString port, long baud);

    void run();


signals:

    void senddata(QByteArray data);//向主线程发送接收到的串口数据

public slots:

    void send_serial_data(const QString &info); //向串口写数据
    void read_serial_data();//读取串口数据

    void close_mthread_serial();//关闭

private:

    QSerialPort *serial;

    QString myport;
    long myBaud;

    float data;
};

#endif // SERIALTHREAD_H

