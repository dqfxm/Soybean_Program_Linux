#ifndef THREADOBJECT_H
#define THREADOBJECT_H
//#include <QApplication>
//#include <ctime>
//#include "soybean_info_system.h"
//#include "ui_soybean_info_system.h"
#include "load_py_model.h" //要放在最前面
#include <QObject>
#include <QMutex>

#include <QThread>
#include <QDebug>
#include <QDir>
#include <QMutexLocker>
#include <QElapsedTimer>
#include <limits>
//#include <windows.h>
#include "imag_capture.h"
#include "ui_Soybean_Info_System.h"
#include "receive_data_from_share.h"
#include "serialthread.h"
#include "hik_gray_capture.h"


class ThreadObject : public QObject
{
    Q_OBJECT
public:
    ThreadObject(QObject* parent = NULL);
    ~ThreadObject();
    void setRunCount(int count);
    void closeThread(void* handle_gray);
    void closeThread_Kinect();
    void closeThread_AIKinect();
    void closeThread_PLC();
signals:
    void message(const QString& info);
    void progress(int present);
    void sendtomain(int);
    void send_to_plc(QString);
    void All_Dev_Cap_Start();
    void All_Dev_Cap_Stop();

public slots:
    void startThreadSlot_camara_1();
    void startThreadSlot_camara_2();
    void startThreadSlot_camara_3();
    void startThreadSlot_Kinect_1();
    void startThreadSlot_Kinect_2();
    void startThreadSlot_Kinect_3();
    void startThreadSlot_AIKinect_1();
    void startThreadSlot_PLC();
    void rec_from_pyrun(int recivecls);
    //控制python采集许可与停止
    int allow_detect_loop();
    int stop_detect_loop();
private:
    int m_runCount;
    int m_runCount2;
    bool m_isStop;
    bool m_isStop2;
    bool m_isStop_Kinect_1;
    QMutex m_stopMutex;
    receive_data *rec_data;
};
#endif // TEST_LOOP_H
