#include "serialthread.h"
#include "transfor_data.h"

SerialThread::SerialThread(QString port, long baud)
{
    myport = port;
    myBaud = baud;
}


void SerialThread::run()

{
    serial = new QSerialPort();
    //设置串口名字 假设我们上面已经成功获取到了 并且使用第一个
    serial->setPortName(myport);
    serial->open(QIODevice::ReadWrite);
//    if(!serial->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
//    {
//        qDebug() << myport << "打开失败!";
////        return 0;
//    }
    serial->setBaudRate(myBaud,QSerialPort::AllDirections);//设置波特率和读写方向
    serial->setDataBits(QSerialPort::Data8);		//数据位为8位
    serial->setParity(QSerialPort::NoParity);	//无校验位
    serial->setStopBits(QSerialPort::OneStop); //一位停止位
    serial->setFlowControl(QSerialPort::NoFlowControl);//流控制位，无流控制
    //connect(serial, SIGNAL(readyRead()), this, SLOT(read_serial_data()), Qt::QueuedConnection);//有数据就读
//    return 1;
}

void SerialThread::send_serial_data(const QString &info)
{

    transfor_data sendmessage;
    QByteArray sendBuf;
//       if (info.contains(" "))
//        {
//           info.replace(QString(" "),QString(""));//我这里是把空格去掉，根据你们定的协议来
//        }
    qDebug()<<"Write to serial: "<<info;
//    if (info.length()>1)
//    {
    sendmessage.StringToHex(info, sendBuf); //把QString 转换 为 hex
    serial->write(sendBuf);  //这句是真正的给单片机发数据 用到的是QIODevice::write 具体可以看文档
     qDebug()<<"发送的信息: "<<sendBuf;

}

void SerialThread::read_serial_data()
{
    if(serial->bytesAvailable()>= 9)
    {
        QByteArray temp;

        temp = serial->read(9);//每串数据为9个字节

        emit senddata(temp);//发送数据给主线程

//      qDebug() << temp ;
      }
}

void SerialThread::close_mthread_serial(void)

{
    qDebug() <<"close ok"<<endl;

    serial->clear();

    serial->close();//关闭子线程

    serial->deleteLater();
}

