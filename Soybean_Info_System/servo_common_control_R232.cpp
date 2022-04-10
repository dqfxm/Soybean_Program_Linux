//#include "Soybean_Info_System.h"
#include <QDebug>
#include "transfor_data.h"
#include "servo_common_control_R232.h"


QString servo_common(QString address,QString order_Data)
{
    bool ok;
    transfor_data data_trans_handle;
    int result = 0;
    QString test_hex_1,test_hex_2,checking_hex;
    QString fanal_data;
    if (order_Data.contains(" "))
    {
        order_Data.replace(QString(" "),QString(""));//我这里是把空格去掉，根据你们定的协议来
    }

    //data_trans_handle.DecToHex(user_data_int,user_data_int_Hex);
    //计算校验位
    int addr = address.toInt(&ok,10);
    test_hex_1 = order_Data;
    test_hex_2 = order_Data;
    int x_1,x_2=0;
    x_1 = test_hex_1.remove(2,2).toInt(&ok,16);
    x_2 = test_hex_2.remove(0,2).toInt(&ok,16);
    // 校验和 A1+A2+A3 取低八位
    result = addr+x_1+x_2;
    data_trans_handle.DecToHex(result,checking_hex);
    if(checking_hex.length()<2)
    {
        checking_hex = checking_hex.insert(0,"0");
    }
    qDebug() << " 校验和"<< checking_hex <<endl;
    qDebug() <<"数据地址：" << address << endl;
    fanal_data = address+order_Data+checking_hex.right(2)+"0d0a";
    return fanal_data;
}
