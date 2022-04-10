#ifndef RECEIVE_DATA_FROM_SHARE_H
#define RECEIVE_DATA_FROM_SHARE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sys/time.h>

#include "QDebug"
#include "sorting_control.h"
#include "modify_csv_file.h"
//#include "sub_serial_send.h"
//#include "serialthread.h"


class receive_data: public QObject
{
Q_OBJECT
public:
    receive_data(QObject* parent = NULL);
    ~receive_data();
signals:
    void sendsigal(int);

public slots:

    void receive_frompyhton_init();
    int recdata_frompython_run();
    int allow_python_loop();
    int stop_python_loop();
//    void sendsigal_slots(int sendclass);

private:
    modifyCSVfile save_to_csv;
//    QSerialPort *serial;
//    SerialThread *mthread;

};

#endif // RECEIVE_DATA_FROM_SHARE_H
