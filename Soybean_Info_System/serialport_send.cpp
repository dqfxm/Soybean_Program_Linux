//#include "Soybean_Info_System.h"
#include <QSerialPort>
#include <QDebug>
#include "transfor_data.h"
#include "string.h"

//std::string str;
void serialport_send(const QString &info)  //发送的数据必须以0d 0a结尾！
{
    extern QSerialPort *m_serialPort;
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
    m_serialPort->write(sendBuf);  //这句是真正的给单片机发数据 用到的是QIODevice::write 具体可以看文档
     qDebug()<<"发送的信息: "<<sendBuf;
//    }
//    else
//    {
//        str = info.toStdString();
//        const char* p = str.c_str();
//        char info_char = *p;
//        char send_char_Buff = sendmessage.CharToHex(info_char);
//        sendBuf[0] = send_char_Buff;
//        m_serialPort->write(sendBuf);
//      qDebug()<<"发送的信息(char): "<<sendBuf;
//    }

}
