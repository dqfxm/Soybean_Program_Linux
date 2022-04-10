#include<QSerialPort>
#include<QDebug>

int serialport_open(QString PortName,QString Baud_rate)
{

    extern QSerialPort *m_serialPort; //= new QSerialPort();//实例化串口类一个对象

    if(m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
    {
        m_serialPort->clear();
        m_serialPort->close();
    }

    //设置串口名字 假设我们上面已经成功获取到了 并且使用第一个
    m_serialPort->setPortName(PortName);

    if(!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug() << PortName << "打开失败!";
        return 0;
    }
    //打开成功
    qint32 current_baud = Baud_rate.toInt();
        qDebug() << "转换后波特率为" << current_baud;

    m_serialPort->setBaudRate(current_baud,QSerialPort::AllDirections);//设置波特率和读写方向
    m_serialPort->setDataBits(QSerialPort::Data8);		//数据位为8位 
    m_serialPort->setParity(QSerialPort::NoParity);	//无校验位
    m_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制，一般没用


        qDebug() << "串口打开成功" << current_baud;
    return 1;
}
