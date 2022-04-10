#include <QApplication>
//#include "ui_soybean_info_system.h"
#include "ThreadObject.h"

extern int imag_stop_flag;  //kinect图像停止标记
extern int gray_stop_flag;  //hik_Gray图像停止标记
extern void *global_handle_1;
extern void *global_handle_2;
extern void *global_handle_3;
extern void *global_kinect_handle_1;
//plc控制状态变量
extern int plc_stop_flag;  //plc停止控制标记
extern int plc_run_state;  //plc运行状态

//extern int current_state;   //Kinect相机返回的运行状态
//kinect相机主窗口显示变量
extern cv::Mat rgb_data_1;
extern cv::Mat depth_data_1;
extern cv::Mat rgb_data_2;
extern cv::Mat depth_data_2;
extern cv::Mat rgb_data_3;
extern cv::Mat depth_data_3;
extern uint8_t *deviceID;
extern string *serialnum;
extern int read_share_flag;

//hik相机主窗口显示变量
extern cv::Mat gray_data_1;
extern cv::Mat gray_data_2;
extern cv::Mat gray_data_3;
//串口数据
extern QByteArray hexData;

//int* imag_state_1;
//std::string* str_1_addr;

ThreadObject::ThreadObject(QObject *parent):QObject(parent)
//    ,m_runCount(10)
//    ,m_runCount2((std::numeric_limits<int>::max)())
//    ,m_isStop(true)
//    ,m_isStop2(true)
{
    m_isStop = false;
//    m_isStop2 = false;
//    m_isStop_Kinect_1 = false;

}
ThreadObject::~ThreadObject()
{
    qDebug() << "ThreadObject destroy";
//    emit message(QString("Destroy %1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}
//关闭线程///////////////////////////////////////
void ThreadObject::closeThread(void* handle_gray)
{
//    QMutexLocker locker(&m_stopMutex);
//    emit message(QString("%1->%2,thread id:%3").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
//    QMutexLocker locker(&m_stopMutex); //进程互斥锁
    m_isStop = true;
    if(m_isStop)
    {
        gray_stop_flag = 1;
        gray_stop_capture(handle_gray);
    }
}
void ThreadObject::closeThread_Kinect()
{

    m_isStop = true;
    if(m_isStop)
    {
        imag_stop_flag = 1;
    }
}
void ThreadObject::closeThread_AIKinect()
{
    read_share_flag = 1;
}

void ThreadObject::closeThread_PLC()
{
    plc_stop_flag = 1;
}

////////////////END//////////////////////////////
//开启hik_gray_1工作线程
void ThreadObject::startThreadSlot_camara_1()
{
    string hik_camara_num = "1";
    gray_capture(global_handle_1,&gray_data_1,hik_camara_num);
}
//开启hik_gray_2工作线程
void ThreadObject::startThreadSlot_camara_2()
{
    string hik_camara_num = "2";
    gray_capture(global_handle_2,&gray_data_2,hik_camara_num);
}
//开启hik_gray_3工作线程
void ThreadObject::startThreadSlot_camara_3()
{
    string hik_camara_num = "3";
    gray_capture(global_handle_3,&gray_data_3,hik_camara_num);
}

//开启Kinect_1工作线程
void ThreadObject::startThreadSlot_Kinect_1()
{
    imag_capture(deviceID[0],&rgb_data_1,&depth_data_1);
}
//开启Kinect_2工作线程
void ThreadObject::startThreadSlot_Kinect_2()
{
    imag_capture(deviceID[1],&rgb_data_2,&depth_data_2);
}
//开启Kinect_3工作线程
void ThreadObject::startThreadSlot_Kinect_3()
{
    imag_capture(deviceID[2],&rgb_data_3,&depth_data_3);
}
//开启kinect动态识别线程
void ThreadObject::startThreadSlot_AIKinect_1()
{
    rec_data = new receive_data;
    connect(rec_data,&receive_data::sendsigal,this,&ThreadObject::rec_from_pyrun);
    rec_data->receive_frompyhton_init();
    rec_data->recdata_frompython_run();
}
void ThreadObject::rec_from_pyrun(int recivecls)
{
    emit sendtomain(recivecls);
}
//开启PLC工作线程
void ThreadObject::startThreadSlot_PLC()
{
    QString send_message = NULL;
    int once_time = 0;
    int run_loop = 0;
    if (plc_run_state != 0)
    {
        cout<<"PLC采集状态：正在运行"<<endl;
    }
    else{
        emit send_to_plc("1001000d0a");  //向PLC首次发送开始工作信号
        plc_run_state =1; //PLC正在运行
        while(1)
        {            
            Sleep(1); //延迟1毫秒
            if(hexData == "ff01010d0a")//PLC正在控制行走
            {

                send_message = "PLC正在控制行走伺服与采集步进电机归位";
                emit message(send_message);
                hexData = NULL; //清空接收数据
            }
            else
            {
                if(once_time ==0)
                {
                    send_message = "系统未接收到PLC信号！等待信号接收中....请检查设备连接。";
                    emit message(send_message);
                    once_time = 1;
                }
            }
            if(hexData == "ff01ff0d0a") //PLC到达指定位置，可以开始采集
            {
                send_message = "采集车到达指定位置，图像开始采集...";
                //ui ->state_Browser ->append(">><font color=\"#0000FF\">采集车到达指定位置，图像开始采集...</font>");
                emit message(send_message);
                emit All_Dev_Cap_Start();  //全部图像采集设备开始图像采集
                emit send_to_plc("1002000d0a"); //已经开始图像采集,向PLC发送控制步进电机工作信号
                hexData = NULL; //清空接收数据
            }
            if(hexData == "ff02010d0a")//PLC正在控制步进电机运行
            {
                send_message = "PLC控制采集步进电机工作，图像正在采集中!";
                emit message(send_message);
                hexData = NULL; //清空接收数据
            }

            if(hexData == "ff02ff0d0a")//PLC控制步进电机到达指定位置
            {
                send_message = "当前位置植株图像采集完成，步进电机到达指定终点!";
                emit message(send_message);
                emit All_Dev_Cap_Stop();  //全部图像采集设备停止图像采集
                emit send_to_plc("1001000d0a"); //向PLC发送开始工作信号，开始进入循环下次采集控制。
                hexData = NULL; //清空接收数据
            }
            if (plc_stop_flag == 1)
            {
                emit send_to_plc("10aadd0d0a"); //向plc发送停止采集指令
                plc_run_state = 0; //PLC运行状态停止
                break;
            }
            run_loop +=1;
            if(run_loop >= 100000)
            {
                cout<<"PLC控制循环100000次"<<endl;
                run_loop = 0;
            }
        }

    }
}

////控制python采集许可与停止
int ThreadObject::allow_detect_loop()
{
    return rec_data->allow_python_loop();
}
int ThreadObject::stop_detect_loop()
{
    return rec_data->stop_python_loop();
}

