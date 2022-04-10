#ifndef TRANSFOR_DATA_H
#define TRANSFOR_DATA_H
//#include "Soybean_Info_System.h"
#include <qobject.h>
//class Soybean_Info_System;
class transfor_data: public QObject
{
public:
    transfor_data();
    ~transfor_data();
public:
    int len;
    void StringToHex(const QString &str, QByteArray &byteData);
    int DecToHex(const int &dec_data, QString &hex_data);
    char CharToHex(char ch);
private:

    char exchange_int_char(int a);

};

#endif // TRANSFOR_DATA_H
