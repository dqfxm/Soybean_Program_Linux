//#include "Soybean_Info_System.h"
#include "servo_speed_control_R232.h"
#include <QDebug>
#include "transfor_data.h"

//控制伺服电机旋转，给定地址和转速后，返回伺服驱动器可识别的控制指令

QString servo_speed_control(QString addres, int user_data)
{

    //transfor_data send_message; //要对象实例化再调用成员函数
    bool ok;
    //int speed_address = 0x06;   //数据地址A1
    //int digital_speed;
    //int user_data_int = user_data.toInt();
    transfor_data data_trans_handle;
    int result = 0;
    QString user_data_int_Hex,test_hex_1,test_hex_2,checking_hex;
    QString fanal_data;
    QByteArray Real_HEX_data;

    //转速计算 (实际转速/3000)*8192=设定数字量转速，再转换成16进制
    //digital_speed=(speed_dec_int/3000)*8192;

    data_trans_handle.DecToHex(user_data,user_data_int_Hex);
    user_data_int_Hex=user_data_int_Hex.right(4);

    if (user_data_int_Hex.length()<4 && user_data_int_Hex.length()>2)
    {
        user_data_int_Hex = user_data_int_Hex.insert(0,"0");
    }
    else if((user_data_int_Hex.length()<3 && user_data_int_Hex.length()>1))
    {
        user_data_int_Hex = user_data_int_Hex.insert(0,"00");
    }
    else if((user_data_int_Hex.length()<2 && user_data_int_Hex.length()>=0))
    {
        user_data_int_Hex = user_data_int_Hex.insert(0,"000");
    }

    int addr = addres.toInt(&ok,10);
    test_hex_1 = user_data_int_Hex;
    test_hex_2 = user_data_int_Hex;
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
    qDebug() << "校验和" << checking_hex <<Qt::endl;
    qDebug() << "数据地址：" << addres << Qt::endl;
    fanal_data = addres+user_data_int_Hex+checking_hex.right(2)+"0d0a";
    return fanal_data;

}



