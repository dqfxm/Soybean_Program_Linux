#ifndef SOYBEAN_INFO_SYSTEM_H
#define SOYBEAN_INFO_SYSTEM_H

#include "call_python.h"  //要放在最前面
#include "load_py_model.h" //要放在最前面
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include "ThreadObject.h"
#include <QCloseEvent>
#include "help_dialog.h"
#include "switchbutton.h"
#include "my_switch.h"
#include "parameter_description.h"
#include "function_discription.h"
#include "program_test.h"
#include "config_list.h"
#include "opencv2/imgproc/types_c.h"
#include "stepmotor_control_R232.h"
#include "serialthread.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Soybean_Info_System; }
QT_END_NAMESPACE

class transfor_data;

class Soybean_Info_System : public QMainWindow
{
    Q_OBJECT

public:
    Soybean_Info_System(QWidget *parent = nullptr);
    ~Soybean_Info_System();

signals:
    //hik线程启动控制信号
    void startObjThreadWork1();
    void startObjThreadWork2();
    void startObjThreadWork3();
    //kinect线程启动控制信号
    void startObjThreadWork_k1();
    void startObjThreadWork_k2();
    void startObjThreadWork_k3();
    //智能识别区启动控制信号
    void startObjThreadWork_aik1();
    //PLC线程启动控制信号
    void startObjThreadWork_plc();


public slots:
    void browseDir();      //浏览路径
    void Gray_browseDir(); //海康相机图像存储路径浏览

    void receiveInfo(); //串口接收槽
    //多线程控制槽//////////////////////
    void openThreadSlot_1();  //(IN QThread *m_firtThread_privaty, IN ThreadObject *m_objThread_privaty)
    void openThreadSlot_2();
    void openThreadSlot_3();
    void openThreadSlot_kinect_1();
    void openThreadSlot_kinect_2();
    void openThreadSlot_kinect_3();
    //智能识别区多线程控制
    void openThreadSlot_AIK1();
    //PLC控制线程
    void openThreadSlot_PLC();

    void gray_auto_capture_timer(int timer_state);
    void gray_auto_cp_run();
    void kinect_auto_capture_timer(int timer_state);
    void kinect_auto_cp_run();

    void closeThreadSlot();
    void closeThreadSlot_kinect();
    void closeThreadSlot_AIkinect();
    void closeThreadSlot_PLC();
    void finishedThreadSlot();
    void finishedThreadSlot_kinect();
    void finishedThreadSlot_AIkinect();
    void finishedThreadSlot_PLC();

    /////////////////////////////////////
    //hik设备控制槽
    void hik_gray_init();               //hik_gray设备初始化槽
    void open_gray_monitor();           //打开hik_gray设备槽
    void hik_gray_auto_capturing();     //hik_gray图像自动采集槽
    void hik_gray_auto_stop();          //hik_gray图像自动采集停止槽
    void hik_gray_manul_capturing();    //hik_gray图像手动采集槽
    void close_hik_gray();              //关闭hik_gray设备槽
    //kinect控制槽
    void kinect_device_init();
    void open_kinect_device();          //打开kinect设备槽
    void close_kinect_device();         //关闭kinect设备槽
    void rgbd_img_capture_start();      //kinect图像自动采开始集槽
    void rgbd_img_capture_stop();       //kinect图像自动采停止集槽
    void kinect_save_rgb();           //kinect图像rgb与rgbd格式选择
    void kinect_save_rgbd();          //kinect图像rgb与rgbd格式选择
    int Open_All_device();             //打开全部设备槽
    void Close_All_device();            //关闭全部设备槽
    void All_device_capture_start();    //全部设备开始自动采集槽
    void All_device_capture_stop();     //全部设备停止自动采集槽
    //主程序关闭事件槽
    void closeEvent(QCloseEvent *event);//头文件中声明
    void Exposure_auto_contrl(bool checked); //自动调节曝光时间控制
    //步进电机控制槽
    void send_to_stepper(int class_data);
    //PLC控制槽
    void ALL_Device_PLC_AutoRun();         //全部设备采集PLC控制开始采集槽
    void ALL_Device_PLC_Close();           //全部设备采集PLC控制停止采集槽
    void PLC_Contrl_Slot(QString send_data_plc); //向plc发送指令槽


private slots:
    void timeUpdate();
    //kinect采集控制
    void on_kienct_init_Btn_clicked();
    void on_img_start_Btn_clicked();
    void on_img_stop__Btn_clicked();

    //串口控制
    void on_get_serial_Btn_clicked();
    void on_open_port_Btn_clicked();
    void on_m_start__Btn_clicked();
    void on_serial_test_Btn_clicked();
    //伺服点击控制
    void on_m_run_Btn_clicked();
    void on_m_stop__Btn_clicked();
    //步进电机点击控制
    void on_step_run_cw_clicked();
    void on_step_run_ccw_clicked();

    //hik相机操作按钮事件
    void on_gray_monitor_Btn_clicked();
    void on_gray_stop_Btn_clicked();
    void on_gray_manul_Btn_clicked();
    void on_gray_auto_Btn_clicked();
    void on_gray_init_Btn_clicked();

    void on_sys_exit_Btn_clicked();
    void on_gray_auto_stop_Btn_clicked();
    void on_kinect_open_Btn_clicked();
    void on_kinect_close_Btn_clicked();
    //设备整体操作按钮事件
    void on_Open_all_device_Btn_clicked();
    void on_All_device_stop__Btn_clicked();
    void on_All_device_capture_Btn_clicked();
    void on_All_device_capture_stop_Btn_clicked();
    void on_clean_state_history_Btn_clicked();
    //智能识别控制区按钮事件
    void on_load_py_Btn_clicked();
    void on_read_share_Btn_clicked();
    void on_readshare_stop_Btn_clicked();
    void on_readshare_stop_detect_Btn_clicked();


//子窗口控制
//菜单下拉选项弹出对话框的所有接收槽
private slots:
    void Actions_clicked();
    void ParameterDescription_clicked();
    void FunctionDescription_clicked();
    void Program_test_page_clicked();
    void config_list_clicked();
    void conect_program_test();   //程序测试页槽连接初始化
    void received_from_testpage(QString addrr); //测试信息接收槽
    void on_ToolBarContrl_action_toggled(bool checked);
    //接收来自多线程的信息
    void receiveMessage(QString rec_message);

    void on_Device_AutoRun_Btn_clicked();

    void on_Device_AutoStop_Btn_clicked();

private:
    Ui::Soybean_Info_System *ui;
    void creatActions();  //创建action信号与槽连接connect函数
    //创建窗口对象指针实例化
    help_Dialog *m_help_Dialog;   //添加私有成员，为一个dailog（窗口）指针
    Parameter_Description *m_parameter_Dialog;
    Function_Discription *m_functiong_Dialog;
    Program_Test *m_program_test_page;   //程序调页对象
    Config_List *m_config_list;

    QLabel *m_label;
    QLabel *m_label_indict;
    //hik工作线程
    QThread *m_firtThread_privaty = NULL,*m_firtThread_privaty_2 = NULL,*m_firtThread_privaty_3 = NULL;
    ThreadObject *m_objThread_privaty,*m_objThread_privaty_2,*m_objThread_privaty_3;
    //kinect工作线程
    QThread *m_firtThread_privaty_k1 = NULL,*m_firtThread_privaty_k2 = NULL,*m_firtThread_privaty_k3 = NULL;
    ThreadObject *m_objThread_privaty_k1,*m_objThread_privaty_k2,*m_objThread_privaty_k3;

    //智能识别工作线程kinect工作线程
    QThread *m_firtThread_privaty_aik1 = NULL;
    ThreadObject *m_objThread_privaty_aik1;
    ThreadObject python_loop_flag; //停止python循环
    //PLC工作线程
    QThread *m_firtThread_privaty_plc = NULL;
    ThreadObject *m_objThread_privaty_plc;

    SwitchButton *exposure_switch;
    QSerialPort *serial;
    SerialThread *mthread;

    receive_data *receive_and_send;


protected:
    void paintEvent(QPaintEvent *e);


};

#endif // POTATO_AI_SYSTEM_H
