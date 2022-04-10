#include "sub_serial_send.h"

QSerialPort *sub_serialPort = new QSerialPort();

int serial_open(QString PortName,QString Baud_rate)
{
    if(sub_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
    {
        sub_serialPort->clear();
        sub_serialPort->close();
    }

    //设置串口名字 假设我们上面已经成功获取到了 并且使用第一个
    sub_serialPort->setPortName(PortName);

    if(!sub_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug() << PortName << "打开失败!";
        return 0;
    }
    //打开成功
    qint32 current_baud = Baud_rate.toInt();
        qDebug() << "转换后波特率为" << current_baud;

    sub_serialPort->setBaudRate(current_baud,QSerialPort::AllDirections);//设置波特率和读写方向
    sub_serialPort->setDataBits(QSerialPort::Data8);		//数据位为8位
    sub_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    sub_serialPort->setParity(QSerialPort::NoParity);	//无校验位
    sub_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位

        qDebug() << "串口打开成功" << current_baud;
    return 1;
}

void serial_send(const QString &info)  //发送的数据必须以0d 0a结尾！
{
    extern QSerialPort *sub_serialPort;
    transfor_data sendmessage;
    QByteArray sendBuf;
    qDebug()<<"Write to serial: "<<info;
    sendmessage.StringToHex(info, sendBuf); //把QString 转换 为 hex
    sub_serialPort->write(sendBuf);  //这句是真正的给单片机发数据 用到的是QIODevice::write 具体可以看文档
     qDebug()<<"发送的信息: "<<sendBuf;
}
