#include <QtSerialPort/QtSerialPort>
#include <QList>

QString* serialport_init()
{
    static QString array[10];  //初始化QString类型数组，存放串口信息
    int n=1;
    QList<QSerialPortInfo> serialList = QSerialPortInfo::availablePorts();
    qDebug() << "串口的个数： " << serialList.count();

    //显示目标串口支持的波特率列表
    QList<qint32> baudRates = QSerialPortInfo::standardBaudRates();
    qDebug() << baudRates;
    QString serial_num;
    array[0] = serial_num.setNum(serialList.count());

    for (int num=0; num < serialList.count();num++)
    {
        array[n]=serialList.at(num).portName();
        n++;
        qDebug() << "portName: " << serialList.at(num).portName();
    }
    return array;
//    qDebug() << "串口的描述：" << serialPortInfo.at(0).description();
//    qDebug() << "hasProductIdentifier(): " << serialPortInfo.at(0).hasProductIdentifier();
//    qDebug() << "hasVendorIdentifier(): " << serialPortInfo.at(0).hasVendorIdentifier();
//    qDebug() << "isBusy: " << serialPortInfo.at(0).isBusy();
//    qDebug() << "manufacturer: " << serialPortInfo.at(0).manufacturer();
//    qDebug() << "portName: " << serialPortInfo.at(0).portName();
//    qDebug() << "productIdentifier: " << serialPortInfo.at(0).productIdentifier();
//    qDebug() << "serialNumber: " << serialPortInfo.at(0).serialNumber();
//    qDebug() << "vendorIdentifier: " << serialPortInfo.at(0).vendorIdentifier();
//    qDebug() << "systemLocation: " << serialPortInfo.at(0).systemLocation();


//    //实例化一个类型参数为QSerialPortInfo模板类链表
//    QList<QSerialPortInfo> serialList;
//    //给链表赋值为获取到的当前设备的所有串口信息的链表
//    serialList = QSerialPortInfo::availablePorts();
//    qDebug()<< "Name : "<<serialList.first().portName();
//    qDebug()<< "Description : "<<serialList.first().description();
//    qDebug()<< "Manufacturer: "<<serialList.first().manufacturer();
//    qDebug()<< "Serial Number: "<<serialList.first().serialNumber();
//    qDebug()<< "System Location: "<<serialList.first().systemLocation();


}
