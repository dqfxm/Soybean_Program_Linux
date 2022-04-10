#include "transfor_data.h"
#include "QDebug"


transfor_data::transfor_data(void)
{
}

transfor_data::~transfor_data(void)
{
}


//Qstring 转为 16进制的函数
void transfor_data::StringToHex(const QString &str, QByteArray &byteData)
{
    int hexdata=0;
    int lowhexdata=0;
    int hexdatalen = 0;
        len = str.length();
        byteData.resize(len/2);
        char lstr,hstr;
        for(int i=0; i<len; )
        {
            //char lstr,
            hstr=str[i].toLatin1();
            if(hstr == ' ')
            {
                i++;
                continue;
            }
            i++;
            if(i >= len)
                break;
            lstr = str[i].toLatin1();
            hexdata = CharToHex(hstr);
            lowhexdata = CharToHex(lstr);
            if((hexdata == 16) || (lowhexdata == 16))
                break;
            else
                hexdata = hexdata*16+lowhexdata;
            i++;
            byteData[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        byteData.resize(hexdatalen);


}
char transfor_data::CharToHex(char ch)
{
        /*
        0x30等于十进制的48，48也是0的ASCII值，，
        1-9的ASCII值是49-57，，所以某一个值－0x30，，
        就是将字符0-9转换为0-9

        */
        if((ch >= '0') && (ch <= '9'))
             return ch-0x30;
         else if((ch >= 'A') && (ch <= 'F'))
             return ch-'A'+10;
         else if((ch >= 'a') && (ch <= 'f'))
             return ch-'a'+10;
         else return (-1);
}

int transfor_data::DecToHex(const int &dec_data, QString &hex_data )
{

    int n=0;
    n = dec_data;
    hex_data = QString::number(n,16);
    //qDebug() << QString::number(n,16).toUpper();

    return 0;
}


