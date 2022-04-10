#include "Soybean_Info_System.h"
#include "ui_Soybean_Info_System.h"
#include "imag_capture.h"
#include "kinect_init.h"
#include "serialport_init.h"
#include "serialport_open.h"
#include "transfor_data.h"
#include "serialport_send.h"
#include "servo_speed_control_R232.h"
#include "servo_common_control_R232.h"
#include <math.h>
#include <QLabel>
#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>


//#include "receive_example.cpp"


Soybean_Info_System::Soybean_Info_System(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Soybean_Info_System)
{
    ui->setupUi(this);
    creatActions();      //创建菜单中action按钮执行事件
    conect_program_test();  //执行程序测试页的槽连接
    m_label_indict = new QLabel();
    m_label = new QLabel();           // 创建QLabel控件 
    ui->statusbar->addWidget(m_label_indict); //在状态栏添加此控件
    ui->statusbar->addWidget(m_label); //在状态栏添加此控件
    QTimer *timer = new QTimer();
    timer->start(1000);         //每隔1000ms发送timeout的信号
    connect(timer,&QTimer::timeout,this,&Soybean_Info_System::timeUpdate);

    //自动曝光转换开关配置
    //setLayout(ui->horizontalLayout); //水平布局填满整个widget窗口
    QString imageOff = ":/images/icons/switch_off.png";
    QString imageOn = ":/images/icons/switch_on.png";
    exposure_switch = new SwitchButton();
    ui->horizontalLayout_11->addWidget(exposure_switch);

    //exposure_switch->setText("已关闭","已开启");
    exposure_switch->setButtonStyle(SwitchButton::ButtonStyle::ButtonStyle_Image); //设置图片格式
    exposure_switch->setImage(imageOff,imageOn);
    connect(exposure_switch,&SwitchButton::checkedChanged,this,&Soybean_Info_System::Exposure_auto_contrl);
    //connect(this,&Soybean_Info_System::send_exposure_contrl_state,exposure_switch,&SwitchButton::setChecked);

    //浏览文件目录部件连接槽
    connect(ui->rgbd_dir_Btn,&QPushButton::clicked,this,&Soybean_Info_System::browseDir);
    connect(ui->gray_dir_Btn,&QPushButton::clicked,this,&Soybean_Info_System::Gray_browseDir);

    //END//

    //窗口textEditor初始化显示
    ui->m_speed_input->setText("500");
    ui->PixWidth_dir_input->setText("5472");
    ui->PixHeight_dir_input->setText("3648");
    ui->Exposure_dir_input->setText("5000");
    ui->Gain_dir_input->setText("0");
    ui->rgbd_dir_input->setText("/home/fuxiaoming/KINECTRBG");
    ui->gray_dir_input->setText("/home/fuxiaoming/HIKGRAY");
    ui->rgb_inter_time_input->setText("2000");
    ui->gray_inter_time_input->setText("2000");
    ui->radioButton_rgb->click();
    //下拉窗口初始化显示
    ui->comboBox->addItems({"1280*720", "1920*1080", "2560*1440","3840*2160"});
    ui->comboBox->setCurrentIndex(0);   //设置下拉窗口默认值

    //kinect rgb或rgbd选择控制
    connect(ui->radioButton_rgb, SIGNAL(clicked()), this, SLOT(kinect_save_rgb()));
    connect(ui->radioButton_rgbd, SIGNAL(clicked()), this, SLOT(kinect_save_rgbd()));

    //rendermessge = new SwitchButton();
    //receivemessage = new my_switch();
//    receivemessage->show();

}

Soybean_Info_System::~Soybean_Info_System()
{
    //析构关闭串口
//    if (m_serialPort->isOpen())
//       {
//           m_serialPort->close();
//        }
//    delete m_serialPort;
    closeThreadSlot_kinect();
    qDebug() << ">>程序关闭：KinectDK图像采集已停止！.............";
    closeThreadSlot();
    qDebug() << ">>程序关闭：图像采集已停止！.............";
    delete ui;
}
void Soybean_Info_System::timeUpdate()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString strTime = currentTime.toString("yyyy年MM月dd日 hh:mm:ss"); //设置显示的格式
    m_label_indict->setText("当前时间:");
    m_label->setText(strTime); //设置label的文本内容为时间
}
////////////////////////////////////////////////////////////////////////
/*******************************************************
* @brief        浏览文件目录
* @param        []
* @return       void
* @author       FXM
* @data         2021-5-5
* @note         -
*******************************************************/
void Soybean_Info_System::browseDir()
{
    QString directory =QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("浏览目录"), QDir::currentPath()));

    if (!directory.isEmpty())
    {
        ui->rgbd_dir_input->setText(directory);
        //ui->rgbd_dir_input->setReadOnly(true);
    }
}
void Soybean_Info_System::Gray_browseDir()
{
    QString directory =QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("浏览目录"), QDir::currentPath()));

    if (!directory.isEmpty())
    {
        ui->gray_dir_input->setText(directory);
        //ui->rgbd_dir_input->setReadOnly(true);
    }
}

/////////////////////////////各子窗口创建槽函数///////////////////////////////////////
//创建菜单栏Action
void Soybean_Info_System::creatActions()
{
    //配置工具图标
    ui->actionopen_file->setIcon(QIcon(":/images/icons/open.png"));
    ui->ParameterDescrption_action->setIcon(QIcon(":/images/icons/notebook.png"));
    ui->help_action->setIcon(QIcon(":/images/icons/about.png"));
    ui->open_config_list_action->setIcon(QIcon(":/images/icons/open_list.png"));
    ui->save_config_action->setIcon(QIcon(":/images/icons/save.png"));
    ui->load_config_action->setIcon(QIcon(":/images/icons/download_1.png"));
    ui->FunctionDescription_action->setIcon(QIcon(":/images/icons/introduction.png"));
    ui->program_test_page_action->setIcon(QIcon(":/images/icons/test_2.png"));
    ui->exit_program_action->setIcon(QIcon(":/images/icons/exit.png"));
    //配置列表
    ui->open_config_list_action->setStatusTip(tr("打开已保存的配置列表"));
    connect(ui->open_config_list_action,SIGNAL(triggered()),this,SLOT(config_list_clicked()));
    //退出程序
    ui->exit_program_action->setStatusTip(tr("退出本程序"));
    connect(ui->exit_program_action,SIGNAL(triggered()),this,SLOT(close()));

    //帮助栏
    ui->help_action->setStatusTip(tr("关于本程序版本的说明"));
    connect(ui->help_action, SIGNAL(triggered()), this, SLOT(Actions_clicked()));
    //操作说明栏
    ui->ParameterDescrption_action->setStatusTip(tr("相关参数设置的说明"));
    connect(ui->ParameterDescrption_action,SIGNAL(triggered()),this,SLOT(ParameterDescription_clicked()));
    //功能介绍
    ui->FunctionDescription_action->setStatusTip(tr("关于本程序的功能介绍"));
    connect(ui->FunctionDescription_action,SIGNAL(triggered()),this,SLOT(FunctionDescription_clicked()));
    //程序测试页
    ui->program_test_page_action->setStatusTip(tr("提示：该功能为程序Beta版调试页面，主要用于部分功能的调试和优化，该页部分功能可能引起程序崩溃，请忽略此页！"));
    connect(ui->program_test_page_action,SIGNAL(triggered()),this,SLOT(Program_test_page_clicked()));
    //编辑-工具栏-可checkable设置
    ui->ToolBarContrl_action->setCheckable(true);
    ui->ToolBarContrl_action->setChecked(true);  //开启程序默认工具栏checked

    //以下为，当reatActions执行后，立刻给各子窗口对象分配一个空间，直到主窗口关闭。
    //避免每次点击后重复出现子窗口
    //新建一个窗口对象，其中的this指定了新的窗口的父对象是MainWindow，在销毁Mainwindow时也会销毁子对象，即该窗口对象
    m_help_Dialog = new help_Dialog(this);
    m_help_Dialog->setModal(true);    //此处true为模态，false为非模态
    m_parameter_Dialog = new Parameter_Description(this);
    m_parameter_Dialog->setModal(false);    //此处true为模态，false为非模态
    m_functiong_Dialog = new Function_Discription(this);
    m_functiong_Dialog->setModal(true);
    m_program_test_page = new Program_Test(this);
    m_config_list = new Config_List(this);  //新建配置列表对象
    //配置各功能窗口图标
    m_help_Dialog->setWindowIcon(QIcon(":/images/icons/about.png"));
    m_parameter_Dialog->setWindowIcon(QIcon(":/images/icons/notebook.png"));
    m_functiong_Dialog->setWindowIcon(QIcon(":/images/icons/introduction.png"));
    m_program_test_page->setWindowIcon(QIcon(":/images/icons/test_2.png"));
    m_config_list->setWindowIcon(QIcon(":/images/icons/open_list.png"));

}
//////////////////程序测试页槽连接初始化///////////////////////////////////////

void Soybean_Info_System::conect_program_test(){

    //说明：在不进行参数传递时，信号槽绑定时也是要求信号的参数数量大于等于槽函数的参数数量。这种情况一般是一个带参数的信号去绑定一个无参数的槽函数
    //connect(m_program_test_page,SIGNAL(Send_Addr(QString)),this,SLOT(received_from_testpage()));  //该方法连接槽和信号，必须指定信号参数类型
    connect(m_program_test_page,&Program_Test::Send_Addr,this,&Soybean_Info_System::received_from_testpage);//该方法可用，重载类型，参数隐式传递
}
//从测试页接收数据信息槽//
void Soybean_Info_System::received_from_testpage(QString addrr){
    qDebug() << "已准备显示路径";
    ui->state_Browser->append(addrr);
}

/////////////////////////////////////////////////////////////////////////////
//配置列表
void Soybean_Info_System::config_list_clicked()
{
    ui->state_Browser->append("config_list_clicked_clicked");
    m_config_list->show();
}
//关于页面
void Soybean_Info_System::Actions_clicked()
{

    m_help_Dialog->show();
//    qDebug()<<"inside interval qdialog";
//    ui->state_Browser->append("inside interval qdialog");
}
//参数说明
void Soybean_Info_System::ParameterDescription_clicked()
{
    //新建一个窗口对象，其中的this指定了新的窗口的父对象是MainWindow，在销毁Mainwindow时也会销毁子对象，即该窗口对象
    //m_parameter_Dialog->setGeometry(this->geometry());  //把主窗体几何位置给子窗体//窗口被放大到主窗口大小
    //----------设置子窗口显示在父窗口居中的位置-------------------------//
    QPoint globalPos = this->mapToGlobal(QPoint(0,0));//父窗口绝对坐标
    int x = globalPos.x() + (this->width() - m_parameter_Dialog->width()) / 2;//x坐标
    int y = globalPos.y() + (this->height() - m_parameter_Dialog->height()) / 2;//y坐标
    m_parameter_Dialog->move(x, y);//窗口移动
    //-------------------------------------------------------------//
    m_parameter_Dialog->show();   //显示参数说明窗口
}
//功能介绍
void Soybean_Info_System::FunctionDescription_clicked()
{
    m_functiong_Dialog->show();
}
//程序调试页
void Soybean_Info_System::Program_test_page_clicked()
{
    m_program_test_page->show();
}
//工具栏开关
void Soybean_Info_System::on_ToolBarContrl_action_toggled(bool checked)
{
    if (checked){
        ui->toolBar->show();
    }
    else
    {
        ui->toolBar->close();
    }
}

//END//
//////////////////////////////END////////////////////////////////////

//主程序关闭事件
void Soybean_Info_System::closeEvent(QCloseEvent *event)
{
   // QMessageBox::StandardButton button;
    int button;
    button = QMessageBox::question(this, tr("退出程序"),
                                   QString(tr("确认退出程序?")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No) {
          event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
          event->accept();  //接受退出信号，程序退出
    }
}
//////////////////////////参数定义/////////////////////////////////////
// 全局变量定义
extern int imag_stop_flag;
extern int serial_flag;
extern int gray_stop_flag;

QByteArray hexData;

//kinect相机全局变量
int kinect_devNum=0; //kinect设备数量
uint8_t *deviceID = new uint8_t[10](); //kinect 设备初始化ID
string *serialnum = new string[10]();   //kinect 设备初始化序列号
int kinect_dpi = 0;              //kinect 分辨率枚举全局变量
//int current_state = 1;     //KINECT运行状态，1为开始运行，0未发现设备
std::string str_kinect_addr = "";  //KINECT_1图片路径-全局
void *global_kinect_handle_1 = NULL; //kinect设备全局指针
QTimer *kinect_timer = new QTimer(); //创建kinect图采集全局定时器
QString imag_inter_time_add;  //kinect图像采集时间间隔
int intervel_time_kinect = 0;     //Kinect_rgb图像自动采集间隔时间
int kinect_save_rgb_rgbd_flag = 0; //Kinect采集格式选择全局标记

int kinect_run_state = 0;  //kinect运行状态
int kinect_auto_cap_state = 0; //kinect图像自动采集状态标记
int imag_stop_flag=0;      //kinect设备停止标记

//Hik相机全局变量
int dev_num = 0;          //Hik相机连接数量
QString Pixel_Width_str = "5472";     //像素高度//hik相机参数变量
QString Pixel_Height_str = "3648";    //像素高度//hik相机参数变量
QString Expoture_Time_str = "5000";   //曝光时间//hik相机参数变量
QString Gain_dB_str = "0";            //增益   //hik相机参数变量

std::string str_gray_addr = ""; //Gray图片采集路径-全局

bool exposure_auto_set = false; //gray相机自动曝光设置状态标记全局
int interval_time_gray = 0;    //gray图像自动采集间隔时间
QTimer *gray_timer = new QTimer(); //创建灰度图采集全局定时器

int gray_auto_cap_state = 0; //gray图像自动采集状态标记
int gray_manul_cap_state = 0; //gray图像手动采集状态标记

int gray_auto_cap_cliced_flag = 0; //gray自动采集点击按钮控制
int kinect_clicked_flag = 0;  //kinect自动采集点击按钮控制
int kinect_allow_cap_flag = 0;  //kineck图像自动采集许可标记，为1允许采集，为0禁止采集
int timer_state_flag = 0;               //gray自动采集定时器标记
int gray_stop_flag = 0;    //hik设备停止标记

int Thread_Gray_flag = 0;
//int *receive_Thread1;
//int *receive_Thread2;

int hik_run_state = 0;     //海康相机运行状态
int hik_init_state = 0;    //海康参数设定状态

void* handle1 = NULL;
void* handle2 = NULL;
void* handle3 = NULL;
void *global_handle_1 = NULL;     //hik_gray全局指针
void *global_handle_2 = NULL;
void *global_handle_3 = NULL;

//智能识别控制全局变量
int read_share_flag = 0; //AI读取共享内存停止与启动
//PLC控制全局变量
int plc_stop_flag = 0;  //plc停止控制标记
int plc_run_state = 0;  //plc运行状态

//图像采集时间控制变量
QString gray_inter_time_add;  //hik_gray图像采集时间间隔
//串口控制全局变量
int serial_flag = 0;       //串口标记
extern int sendover_flag;   //向步进电机发送指令完成标记
//图像窗口显示kinect全局变量
cv::Mat rgb_data_1 = cv::Mat::zeros(720, 1280, CV_8UC3);
cv::Mat depth_data_1 = cv::Mat::zeros(720, 1280, CV_8UC3);
cv::Mat rgb_data_2 = cv::Mat::zeros(720, 1280, CV_8UC3);
cv::Mat depth_data_2 = cv::Mat::zeros(720, 1280, CV_8UC3);
cv::Mat rgb_data_3 = cv::Mat::zeros(720, 1280, CV_8UC3);
cv::Mat depth_data_3 = cv::Mat::zeros(720, 1280, CV_8UC3);

//图像窗口显示HIK全局变量
cv::Mat gray_data_1 = cv::Mat::zeros(720, 1280, CV_8UC1);
cv::Mat gray_data_2 = cv::Mat::zeros(720, 1280, CV_8UC1);
cv::Mat gray_data_3 = cv::Mat::zeros(720, 1280, CV_8UC1);


////////////////////////////////////END///////////////////////////////////////

////////////////////////////////主要按钮控制区////////////////////////////////
//KINECT DK DEVICE CONTRLLOR REGION
//Kinect设备初始化
void Soybean_Info_System::on_kienct_init_Btn_clicked()
{
    kinect_device_init();
}

//Kinect设备打开按钮
void Soybean_Info_System::on_kinect_open_Btn_clicked()
{
    open_kinect_device();
}

//图像主界面显示控制
void Soybean_Info_System::paintEvent(QPaintEvent *e)
{
    if(kinect_run_state == 1)
    {
    //显示kinenct_1图像
        //图像主界面窗口显示
        QImage image1 = QImage((uchar*)rgb_data_1.data, 1280, 720, QImage::Format_BGR888);
        //设定图像大小自适应label窗口的大小
        image1 = image1.scaled(ui->imglabel_k1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_k1->setPixmap(QPixmap::fromImage(image1));
//        imageLabel->resize(image1.size());
        ui->imglabel_k1->show();

        //深度图像主界面窗口显示
        QImage image1_depth = QImage((uchar*)depth_data_1.data, 1280, 720, QImage::Format_BGR888);
        image1_depth = image1_depth.scaled(ui->imglabel_k1_depth->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_k1_depth->setPixmap(QPixmap::fromImage(image1_depth));
        ui->imglabel_k1_depth->show();

    //显示kinenct_2图像
        //图像主界面窗口显示
        QImage image2 = QImage((uchar*)rgb_data_2.data, 1280, 720, QImage::Format_BGR888);
        //设定图像大小自适应label窗口的大小
        image2 = image2.scaled(ui->imglabel_k2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_k2->setPixmap(QPixmap::fromImage(image2));
//        imageLabel->resize(image1.size());
        ui->imglabel_k2->show();

        //深度图像主界面窗口显示
        QImage image2_depth = QImage((uchar*)depth_data_2.data, 1280, 720, QImage::Format_BGR888);
        image2_depth = image2_depth.scaled(ui->imglabel_k2_depth->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_k2_depth->setPixmap(QPixmap::fromImage(image2_depth));
        ui->imglabel_k2_depth->show();

    //显示kinenct_2图像
        //图像主界面窗口显示
        QImage image3 = QImage((uchar*)rgb_data_3.data, 1280, 720, QImage::Format_BGR888);
        //设定图像大小自适应label窗口的大小
        image3 = image3.scaled(ui->imglabel_k3->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_k3->setPixmap(QPixmap::fromImage(image3));
//        imageLabel->resize(image1.size());
        ui->imglabel_k3->show();

        //深度图像主界面窗口显示
        QImage image3_depth = QImage((uchar*)depth_data_3.data, 1280, 720, QImage::Format_BGR888);
        image3_depth = image3_depth.scaled(ui->imglabel_k3_depth->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_k3_depth->setPixmap(QPixmap::fromImage(image3_depth));
        ui->imglabel_k3_depth->show();

     }
    if(hik_run_state ==1)
    {
        //显示hik_1图像
        //图像主界面窗口显示
        QImage gray_image1 = QImage((uchar*)gray_data_1.data, 1280, 720, QImage::Format_Grayscale8);
        //设定图像大小自适应label窗口的大小
        gray_image1 = gray_image1.scaled(ui->imglabel_hik1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_hik1->setPixmap(QPixmap::fromImage(gray_image1));
        ui->imglabel_hik1->show();
        //显示hik_2图像
        //图像主界面窗口显示
        QImage gray_image2 = QImage((uchar*)gray_data_2.data, 1280, 720, QImage::Format_Grayscale8);
        //设定图像大小自适应label窗口的大小
        gray_image2 = gray_image2.scaled(ui->imglabel_hik2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_hik2->setPixmap(QPixmap::fromImage(gray_image2));
        ui->imglabel_hik2->show();
        //显示hik_3图像
        //图像主界面窗口显示
        QImage gray_image3 = QImage((uchar*)gray_data_3.data, 1280, 720, QImage::Format_Grayscale8);
        //设定图像大小自适应label窗口的大小
        gray_image3 = gray_image3.scaled(ui->imglabel_hik3->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->imglabel_hik3->setPixmap(QPixmap::fromImage(gray_image3));
        ui->imglabel_hik3->show();
    }
}

//主要控制按钮//////////////////////////////////////////
//Kinect设备关闭按钮
void Soybean_Info_System::on_kinect_close_Btn_clicked()
{
    close_kinect_device();
}

//Kinect图像自动采集开始按钮
void Soybean_Info_System::on_img_start_Btn_clicked()
{
    rgbd_img_capture_start();
}

//Kinect图像采集停止按钮
void Soybean_Info_System::on_img_stop__Btn_clicked()
{
    rgbd_img_capture_stop();
}

//Gray相机参数设置与初始化按钮
void Soybean_Info_System::on_gray_init_Btn_clicked()
{
    hik_gray_init();
}
//HIK GRAY CAMERA DEVICE CONTRLLOR REGION
//Gray图像监视窗口打开按钮
void Soybean_Info_System::on_gray_monitor_Btn_clicked()
{
    open_gray_monitor();
}

//Gray图像自动采集按钮
void Soybean_Info_System::on_gray_auto_Btn_clicked()
{
    hik_gray_auto_capturing();
}

//Gray图像自动采集停止按钮
void Soybean_Info_System::on_gray_auto_stop_Btn_clicked()
{
    hik_gray_auto_stop();
}

//Gray图像手动采集按钮
void Soybean_Info_System::on_gray_manul_Btn_clicked()
{
    hik_gray_manul_capturing();
}

//关闭hik设备按钮
void Soybean_Info_System::on_gray_stop_Btn_clicked()
{
    close_hik_gray();
}

//ALL DEVICE 控制按钮区
void Soybean_Info_System::on_Open_all_device_Btn_clicked()
{
    Open_All_device();
}

void Soybean_Info_System::on_All_device_stop__Btn_clicked()
{
    Close_All_device();
    ALL_Device_PLC_Close();
}

void Soybean_Info_System::on_All_device_capture_Btn_clicked()
{
    All_device_capture_start();
}

void Soybean_Info_System::on_All_device_capture_stop_Btn_clicked()
{
    All_device_capture_stop();
}

//全自动采集PLC控制区域，控制采集车
void Soybean_Info_System::on_Device_AutoRun_Btn_clicked()
{
    ALL_Device_PLC_AutoRun();
}

void Soybean_Info_System::on_Device_AutoStop_Btn_clicked()
{
    ALL_Device_PLC_Close();
}

/////////////////////////////////////END///////////////////////////////////////////////
////                                                                               ////
///////////////////////////////全部设备统一控制区槽函数//////////////////////////////////
//打开全部设备槽函数
int Soybean_Info_System::Open_All_device()
{
    if(kinect_devNum == 0 || dev_num ==0) //必须所有设备全部在线才能全自动采集
    {
        if(kinect_devNum == 0)
        {
            ui->state_Browser->append(">><font color=\"#FF0000\">未发现kinectDK设备，请检查连接后初始化！</font> ");
        }
        if(dev_num ==0)
        {
            ui->state_Browser->append(">><font color=\"#FF0000\">未发现Hik设备，请检查连接后初始化！</font> ");
        }
        return 0;
    }
    else
    {
        open_kinect_device();
        open_gray_monitor();
        return 1;
    }
}

void Soybean_Info_System::Close_All_device()
{
    close_kinect_device();
    close_hik_gray();
}

void Soybean_Info_System::All_device_capture_start()
{
    rgbd_img_capture_start();
    hik_gray_auto_capturing();
}

void Soybean_Info_System::All_device_capture_stop()
{
    rgbd_img_capture_stop();
    hik_gray_auto_stop();
}

////////////////////////////////////END//////////////////////////////////////////////
////////////////////////////////////KINECT设备控制槽//////////////////////////////////

//Kincet设备初始化槽
void Soybean_Info_System::kinect_device_init()
{
    if (kinect_run_state == 0)
    {
        kinect_dpi = ui->comboBox->currentIndex();   // 获得下拉窗口当前内容
        ui->state_Browser->append("当前图像分辨率为：");
        ui->state_Browser->append(ui->comboBox->currentText());
        kinect_devNum = 0; //设备数量初始化
        kinect_init();
        //判断设备数量
        for (int i = 0; i<=2;i++){
            if (serialnum[i].size()<12){  //kinect序列号12位
                break;
            }
            kinect_devNum+=1;
            cout<<serialnum[i]<<endl;
            cout<<serialnum[i].size()<<endl;
        }
        if (kinect_devNum == 0)
        {
            ui->state_Browser->append(">><font color=\"#FF0000\">未发现kinectDK设备，请检查连接后重试！</font> ");
        }
        else if (kinect_devNum == 1)
        {
            ui->state_Browser->append(">><font color=\"#FF0000\">发现1个kinectDK设备！</font> ");
        }
        else if (kinect_devNum == 2)
        {
            ui->state_Browser->append(">><font color=\"#FF0000\">发现2个kinectDK设备！</font> ");
        }
        else if (kinect_devNum == 3)
        {
            ui->state_Browser->append(">><font color=\"#FF0000\">发现3个kinectDK设备！</font> ");
        }
        else
        {
            ui->state_Browser->append(">><font color=\"#FF0000\">kinectDK设备数量超出最大限制，连接数量不能超过3个！</font> ");
        }
    }else
    {

        ui->state_Browser->append(">><font color=\"#FF0000\">kinectDK设备正在运行，请关闭设备后再初始化设备！</font> ");
    }
}

//打开Kincet设备槽
void Soybean_Info_System::open_kinect_device()
{
    if (kinect_run_state == 0)
    {
        if (kinect_devNum == 0)
        {
            ui->state_Browser->append(">><font color=\"#FF0000\">请先初始化Kinect设备！</font> ");
        }
        if(kinect_devNum > 0 && kinect_devNum < 4)
        {
            QString qstr_serial = QString::fromStdString(serialnum[0]);
            QString dev_id = QString::number(deviceID[0]);
            QString print_message = "Kinect设备:"+dev_id+"，ID:"+qstr_serial+"，已启动！";
            ui->state_Browser->append(print_message);
            openThreadSlot_kinect_1();
            emit startObjThreadWork_k1();//主线程通过信号换起子线程的槽函数
            kinect_run_state = 1;
            kinect_allow_cap_flag = 1; // 运行kinect开始自动采集

        }
        if(kinect_devNum > 1 && kinect_devNum < 4)
        {
            QString qstr_serial = QString::fromStdString(serialnum[1]);
            QString dev_id = QString::number(deviceID[1]);
            QString print_message = "Kinect设备:"+dev_id+"，ID:"+qstr_serial+"，已启动！";
            ui->state_Browser->append(print_message);
            openThreadSlot_kinect_2();
            emit startObjThreadWork_k2();//主线程通过信号换起子线程的槽函数
            kinect_run_state = 1;
            kinect_allow_cap_flag = 1; // 运行kinect开始自动采集
        }
        if(kinect_devNum > 2 && kinect_devNum < 4)
        {
            QString qstr_serial = QString::fromStdString(serialnum[2]);
            QString dev_id = QString::number(deviceID[2]);
            QString print_message = "Kinect设备:"+dev_id+"，ID:"+qstr_serial+"，已启动！";
            ui->state_Browser->append(print_message);
            openThreadSlot_kinect_3();
            emit startObjThreadWork_k3();//主线程通过信号换起子线程的槽函数
            kinect_run_state = 1;
            kinect_allow_cap_flag = 1; // 运行kinect开始自动采集
        }
    }
    else
    {
        ui -> state_Browser -> append(">>Kinect设备正在运行，请勿重复点击！");
    }
}

//关闭Kincet设备槽
void Soybean_Info_System::close_kinect_device()
{
    rgbd_img_capture_stop();
    kinect_devNum = 0;          //kinect设备数量标记复位
    kinect_run_state = 0;       //kinect设备运行标记复位
    kinect_allow_cap_flag = 0;  //kineck图像自动采集许可标记复位
    closeThreadSlot_kinect();
    QString stop_message = "KinectDK设备已关闭！";
    ui->state_Browser->append(">><font color=\"#FF0000\">" + stop_message + "</font> ");
    //清除kinect窗口显示图像
    ui->imglabel_k1->setText("kinect_imgshow_1");
    ui->imglabel_k1_depth->setText("kinect_imgshow_1_depth");
    ui->imglabel_k2->setText("kinect_imgshow_1");
    ui->imglabel_k2_depth->setText("kinect_imgshow_1_depth");
    ui->imglabel_k3->setText("kinect_imgshow_1");
    ui->imglabel_k3_depth->setText("kinect_imgshow_1_depth");
}
//END
//图像采集RGB或RGB-D选择
void Soybean_Info_System::kinect_save_rgb()
{
    kinect_save_rgb_rgbd_flag = 0;
    ui->state_Browser->append("采集RGB格式图像");
}
void Soybean_Info_System::kinect_save_rgbd()
{
    kinect_save_rgb_rgbd_flag = 1;
    ui->state_Browser->append("采集RGB-D格式图像");
}


//图像采集开始槽//
void Soybean_Info_System::rgbd_img_capture_start()
{
    if (kinect_allow_cap_flag == 1)
    {
        //初始化kinect返回设备序列号,检测设备是否正常连接
        QString imag_save_add= ui -> rgbd_dir_input -> toPlainText();
        QString wrong_mess;
        QDir dir;
        if (!dir.exists(imag_save_add))
        {
            wrong_mess = ">>路径设置错误，请检查文件夹路径";
            ui -> state_Browser -> append(wrong_mess);
        }
        else
        {
            //rgb采集间隔时间控制
            imag_inter_time_add= ui -> rgb_inter_time_input -> toPlainText();
            QString wrong_mess_rgb_time;
            if (imag_inter_time_add == NULL)
            {
                wrong_mess_rgb_time = ">>请输入Kinect图像采集间隔时间！";
                ui -> state_Browser -> append(wrong_mess_rgb_time);
            }
            else
            {
                int inter_time_length = imag_inter_time_add.length();
                int ii = 0;
                for(int j = 0;j<inter_time_length;j++)
                {
                    if(imag_inter_time_add.at(j)<'0'||imag_inter_time_add.at(j)>'9')
                    {
                        ii += 1;
                    }
                }
                if (ii == 0)
                {
                    str_kinect_addr = imag_save_add.toStdString();
                    //qDebug() << imag_save_add <<endl;
                    cout << str_kinect_addr << imag_save_add.length() <<endl;
//开始图像信息采集程序
                    if (kinect_clicked_flag==0)
                    {
                        kinect_clicked_flag++;
                        intervel_time_kinect = imag_inter_time_add.toUInt();
                        kinect_auto_capture_timer(1); //开始定时采集
                        ui->state_Browser->append(">>Kinect图像采集开始...请注意查看保存路径！");
                        ui->rgbd_dir_input->setDisabled(true); //设置输入地址栏失效
                        ui->rgb_inter_time_input->setDisabled(true);//设置时间输入失效
                        ui->radioButton_rgb->setDisabled(true); //设置rgb选项输入失效
                        ui->radioButton_rgbd->setDisabled(true); //设置rgb选项输入失效
                    }
                    else
                    {
                        QString running_message = "图像采集正在进行中...,如需停止请点击停止采集按钮！";
                        ui->state_Browser->append(">><font color=\"#339900\">" + running_message + "</font>");
                    }
//END
                }
                else
                {
                    ui->state_Browser->append(">>请输入正确时间格式，应为正整数！");
                }
            }
        }
    }
    else
    {
        ui->state_Browser->append(">>请先打开Kincet设备！");
    }
}

//END

//Kinect图片采集控制定时器槽
void Soybean_Info_System::kinect_auto_capture_timer(int timer_state)
{
    //QString setTime = ui -> gray_inter_time_input-> toPlainText();
    //gray_timer->interval(2000);   //setTime.toInt()
    if (timer_state !=0)
    {
        kinect_timer->start(intervel_time_kinect);
        connect(kinect_timer, SIGNAL(timeout()), this, SLOT(kinect_auto_cp_run()));
    }
    else
    {
        kinect_timer->stop();
    }
}
void Soybean_Info_System::kinect_auto_cp_run()
{
    kinect_auto_cap_state = 1;   //kinect自动采集开始标志
}
//END

//kINECT图像采集停止槽//
void Soybean_Info_System::rgbd_img_capture_stop()
{

    kinect_auto_capture_timer(0); //关闭定时采集
    kinect_auto_cap_state = 0;  //kinect自动采集标记初始化
    kinect_clicked_flag = 0;    //kincet点击事件初始化
    ui->state_Browser->append(">>Kinect图像自动采集已停止!");
    ui->rgbd_dir_input->setDisabled(false); //设置输入地址栏可用
    ui->rgb_inter_time_input->setDisabled(false); //设置时间输入可用
    ui->radioButton_rgb->setDisabled(false); //设置rgb选项输入可用
    ui->radioButton_rgbd->setDisabled(false); //设置rgb选项输入可用
}
//END
/////////////////////////////////////END///////////////////////////////////////////
////////////////////////////////串口通信控制槽//////////////////////////////////////
//串口初始化模块//
void Soybean_Info_System::on_get_serial_Btn_clicked()
{
    QString* p;
    p = serialport_init();
    QString port_message[10];
    QStringList port_List;
    QStringList baud_Rate;
    baud_Rate << "57600" << "1200" << "2400" << "4800" << "9600" << "14400" << "19200" << "38400" << "56000" << "115200";

    for ( int w = 0; w < 10; w++ )
       {
           //qDebug() << "*(p + " << w << ") : ";
           //qDebug() << *(p + w);          //输出串口初始化函数返回指针内容
           port_message[w] = *(p + w);      //将返回信息给port_message数组
       }
    int port_n = port_message[0].toInt();
    ui->show_serial_Box->clear();
    ui->choose_baud_Box->clear();
    if (port_n == 0)
    {
        ui->state_Browser->append(">><font color=\"#FF0000\">未发现可用串口，请检测设备连接！</font>");
    }
    else
    {
        for (int u=1;u<port_n+1;u++)
        {
            port_List << port_message[u];
        }
        ui-> show_serial_Box->addItems(port_List);
        ui-> choose_baud_Box->addItems(baud_Rate);
    }
}
//END

//串口打开模块//
void Soybean_Info_System::on_open_port_Btn_clicked()
{

    QString current_port = ui -> show_serial_Box -> currentText();   //返回当前串口
    QString current_baud = ui-> choose_baud_Box-> currentText();     //返回当前波特率
    qDebug() << current_port << current_baud << Qt::endl;
    if (current_port == NULL||current_baud == NULL)
    {
        ui->state_Browser->append(">>请先刷新串口列表！");
    }
    else
    {
        //调用串口打开函数 //
         serial_flag = 0;
         serial_flag = serialport_open(current_port, current_baud);

        if (serial_flag == 1)
        {
            ui->state_Browser->append(">>当前串口打开成功！");
        }
        else
        {
            ui->state_Browser->append(">>串口打开失败！");
        }
    }
     //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号,我们定义个槽void receiveInfo()解析数据
     connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
}
//END

//接收单片机的数据
void Soybean_Info_System::receiveInfo()
{
    extern QByteArray hexData;
    QByteArray receive_info = m_serialPort->readAll();
    hexData = receive_info.toHex();
    //这里面的协议，自己定义就行  单片机发什么 代表什么 我们这里简单模拟一下
    ui ->state_Browser ->append(">>串口接收到的信息为：");
    ui ->state_Browser ->append(hexData);
    qDebug() << "hexData.length:"<<hexData.length();
    qDebug() << hexData <<Qt::endl;

        if(hexData == "0606")
        {
            ui ->state_Browser ->append(">><font color=\"#009900\">电机开始按设定速度运转</font>");
        }
}
//END

// 伺服电机启动按钮
void Soybean_Info_System::on_m_run_Btn_clicked()
{
    extern QByteArray hexData;
    QString servo_addr = "00";  //伺服电机地址
    QString run_address = "00"; //电机启停控制地址
    QString run_order = "00 01";
    QString send_order;
    if(serial_flag == 0)
    {
        ui->state_Browser->append(">>与驱动器通讯异常：串口未打开！");
    }
    else
    {
        send_order = servo_addr+servo_common(run_address,run_order);
        qDebug() << "拟发送启动指令为" << send_order;
        serialport_send(send_order);
        if(hexData == "0000")
        {
            ui ->state_Browser ->append(">><font color=\"#0000FF\">电机已开启！</font>");
        }
    }
}
//END

// 伺服电机关闭按钮
void Soybean_Info_System::on_m_stop__Btn_clicked()
{
    extern QByteArray hexData;
    QString servo_addr = "00";  //伺服电机地址
    QString run_address = "00"; //电机启停控制地址
    QString run_order = "00 00"; //电机关闭指令
    QString send_order;
    if(serial_flag == 0)
    {
        ui->state_Browser->append(">>与驱动器通讯异常：串口未打开！");
    }
    else
    {
        send_order =servo_addr+servo_common(run_address,run_order);
        qDebug() << "拟发送启动指令为" << send_order;
        serialport_send(send_order);
        if(hexData == "0000")
        {
            ui ->state_Browser ->append(">><font color=\"#FF00FF\">电机已关闭！</font>");
        }
    }
}
//END

//伺服电机按给定速度运转按钮，向单片机发送指令
void Soybean_Info_System::on_m_start__Btn_clicked()
{
    //transfor_data send_message; //要对象实例化再调用成员函数
    //速度模式启动
    QString servo_addr = "00";  //伺服电机地址
    QString speed_address = "06";   //pc速度模式给定速度的数据地址A1：0x06
    QString speed_dec =ui -> m_speed_input -> text();
    int digital_speed;
    QString send_speed;
    if(abs(speed_dec.toDouble())>3300)
    {
        ui->state_Browser->append(">>设置未成功，为保护电机，请不要超过3300r/min的转速！");
    }
    else
    {
    //转速计算 (实际转速/3000)*8192=设定数字量转速，再转换成16进制
    digital_speed=round((speed_dec.toDouble()*8192)/3000);
    qDebug() << "精度测试"<< speed_dec.toDouble();
    qDebug() << "计算结果"<< digital_speed;
    if(serial_flag == 0)
    {
        ui->state_Browser->append(">>与驱动器通讯异常：串口未打开！");
    }
    else
    {
        send_speed = servo_addr+servo_speed_control(speed_address, digital_speed);
        serialport_send(send_speed);
        QByteArray receive_info = m_serialPort->readAll();

    }
        send_speed.clear();
    }
}
//END

//串口调试区，自定义数据串口发送
void Soybean_Info_System::on_serial_test_Btn_clicked()
{

    QString current_data = ui -> serial_send_textEdit -> document() ->toPlainText();
    if(serial_flag == 0)
    {
        ui->state_Browser->append(">>与驱动器通讯异常：串口未打开！");
    }
    else
    {
        if (current_data == NULL || current_data.at(0)==" ")
        {
            ui -> state_Browser ->append(">>检测输入数据未空，请正确输入后再发送！");
        }
        else
        {
            serialport_send(current_data);
            qDebug() << current_data;
        }
    }
}

//步进电机手动控制调试区
//步进电机正转
void Soybean_Info_System::on_step_run_cw_clicked()
{
    //sendseiraldata.serial_open("ttyUSB1","57600");
    if(serial_flag == 0)
    {
        ui->state_Browser->append(">>与驱动器通讯异常：串口未打开！");
    }
    else
    {
        QString run_dir = "00"; //步进电机方向
        int steper_angel = ui->step_angle_input->text().toInt();
        int steper_speed = ui->step_speed_input->text().toInt();
        stepmotor_run(run_dir,steper_angel,steper_speed);
        if(hexData == "ff")
        {
            ui ->state_Browser ->append(">><font color=\"#0000FF\">步进电机正转运行！</font>");
        }
    }
}
//步进电机反转
void Soybean_Info_System::on_step_run_ccw_clicked()
{
    if(serial_flag == 0)
    {
        ui->state_Browser->append(">>与驱动器通讯异常：串口未打开！");
    }
    else
    {

        QString run_dir = "01"; //步进电机方向
        int steper_angel = ui->step_angle_input->text().toInt();
        int steper_speed = ui->step_speed_input->text().toInt();
        stepmotor_run(run_dir,steper_angel,steper_speed);
        if(hexData == "ff")
        {
            ui ->state_Browser ->append(">><font color=\"#0000FF\">步进电机反转运行！</font>");
        }
    }
}
//步进电机自动控制槽
void Soybean_Info_System::send_to_stepper(int class_data)
{
    if(serial_flag == 0)
    {
        ui->state_Browser->append(">>与驱动器通讯异常：串口未打开！");
    }
    else
    {
        qDebug()<<"通过槽进入到步进电机控制"<<Qt::endl;
        std::cout <<"发送完成标记"<<sendover_flag<<std::endl;
        sendover_flag = 1;
        QString run_dir = "0"+QString::number(class_data); //步进电机方向
        int steper_angel = ui->step_angle_input->text().toInt();
        int steper_speed = ui->step_speed_input->text().toInt();
        stepmotor_run(run_dir,steper_angel,steper_speed);
        if(hexData == "ff")
        {
            ui ->state_Browser ->append(">><font color=\"#0000FF\">步进电机反转运行！</font>");
        }
    }
};

//END
///////////////////////////////////////////////////////////////////////////////////

/////////////////////////以下为hik_gray相机控制槽///////////////////////////////////

//Gray相机参数设置与初始化槽
void Soybean_Info_System::hik_gray_init()
{
    if(hik_run_state != 0)
    {
        ui->state_Browser->append(">>设备正在运行，请先关闭Hik灰度相机后，再点击更新参数设置！");
    }
    else
    {
        while (1)
        {
            if(hik_init_state == 0)
            {
                Pixel_Width_str = ui ->PixWidth_dir_input -> toPlainText();
                Pixel_Height_str = ui ->PixHeight_dir_input ->toPlainText();
                Expoture_Time_str = ui ->Exposure_dir_input ->toPlainText();;
                Gain_dB_str = ui ->Gain_dir_input ->toPlainText();
                if(Pixel_Width_str == NULL || Pixel_Height_str == NULL || Expoture_Time_str == NULL || Gain_dB_str == NULL)
                {
                    ui->state_Browser->append(">>请输入设备参数，参数不能为空，且为正整数！");
                    break;
                }
                else
                {
                    int Pixel_Width_str_length = Pixel_Width_str.length();
                    int Pixel_Height_str_length = Pixel_Height_str.length();
                    int Expoture_Time_str_length = Expoture_Time_str.length();
                    int Gain_dB_str_length = Gain_dB_str.length();
                    int Width_ii = 0,Height_ii = 0,Expoture_ii = 0,Gain_ii = 0;
                    for(int j = 0;j<Pixel_Width_str_length;j++)
                    {
                        if(Pixel_Width_str.at(j)<'0'||Pixel_Width_str.at(j)>'9')
                        {
                            Width_ii += 1;
                        }
                    }
                    for(int j = 0;j<Pixel_Height_str_length;j++)
                    {
                        if(Pixel_Height_str.at(j)<'0'||Pixel_Height_str.at(j)>'9')
                        {
                            Height_ii += 1;
                        }
                    }
                    for(int j = 0;j<Expoture_Time_str_length;j++)
                    {
                        if(Expoture_Time_str.at(j)<'0'||Expoture_Time_str.at(j)>'9')
                        {
                            Expoture_ii += 1;
                        }
                    }
                    for(int j = 0;j<Gain_dB_str_length;j++)
                    {
                        if(Gain_dB_str.at(j)<'0'||Gain_dB_str.at(j)>'9')
                        {
                            Gain_ii += 1;
                        }
                    }
                    if (Width_ii ==0 && Height_ii==0 && Expoture_ii==0 && Gain_ii == 0)
                    {
                        int Pixel_Width_int =Pixel_Width_str.toInt();
                        int Pixel_Height_int = Pixel_Height_str.toInt();
                        int Expoture_Time_int = Expoture_Time_str.toInt();
                        int Gain_dB_str_int = Gain_dB_str.toInt();
                        if (Pixel_Width_int<128 || Pixel_Width_int>5472)
                        {
                            ui->state_Browser->append(">>>>像素宽度值超出了范围，请设置在[128，5472]之间，步进值:1");
                            break;
                        }
                        else if(Pixel_Height_int<128 || Pixel_Height_int>3648)
                        {
                            ui->state_Browser->append(">>>>像素高度值超出了范围，请设置在[128，3648]之间，步进值:1");
                            break;
                        }
                        else if(Expoture_Time_int<30 || Expoture_Time_int>700000)
                        {
                            ui->state_Browser->append(">>>>曝光时间超出了范围，请设置在[30，700000]之间");
                            break;
                        }
                        else if(Gain_dB_str_int>20)
                        {
                            ui->state_Browser->append(">>>>增益设置超出了范围，请设置在[0，20]之间");
                            break;
                        }
                        else
                        {
                            //开始按给定参数设备初始化
                            dev_num = camara_init_access(Pixel_Width_str.toInt(),Pixel_Height_str.toInt(),Expoture_Time_str.toInt(),Gain_dB_str.toInt()); //相机参数确定与初始化
                            if(dev_num==0)
                            {
                                ui->state_Browser->append(">>Hik_Gray设备未发现，请检查设备连接！");
                                break;
                            }
                            else if(dev_num==1)
                            {
                                ui->state_Browser->append(">>发现1个Hik_Gray设备，参数设置成功，可以开始图像采集！");
                                hik_init_state = 1;
                                break;
                            }
                            else if(dev_num==2)
                            {
                                ui->state_Browser->append(">>发现2个Hik_Gray设备，参数设置成功，可以开始图像采集！");
                                hik_init_state = 1;
                                break;
                            }
                            else
                            {
                                ui->state_Browser->append(">>发现3个或以上Hik_Gray设备，参数设置成功，可以开始图像采集！");
                                hik_init_state = 1;
                                break;
                            }
                        }
                    }
                    else
                    {
                        ui->state_Browser->append(">>设备参数输入了错误的字符类型，请输入正整数！");
                        break;
                    }
                }
            }
            else
            {
                if(dev_num==1)
                {
                    gray_stop_capture(global_handle_1);
                }
                else if(dev_num==2)
                {
                    gray_stop_capture(global_handle_1);
                    gray_stop_capture(global_handle_2);
                }
                else if(dev_num==3)
                {
                    gray_stop_capture(global_handle_1);
                    gray_stop_capture(global_handle_2);
                    gray_stop_capture(global_handle_3);
                }
                else
                {
                    ui->state_Browser->append(">>没有Hik_Gray设备的初始化打开状态！");
                    break;
                }
                hik_init_state = 0;
                ui->state_Browser->append(">>Hik_Gray设备参数更新设置完成！");
            }
        }
    }
}
//END

// 打开hik_gray设备槽
void Soybean_Info_System::open_gray_monitor()
{
    if(hik_run_state == 0)
        {
        if(dev_num != 0)
        {
             ui->state_Browser->append(">>gray_Camera初始化成功！");
             hik_run_state = 1;
             ui->Exposure_dir_input->setEnabled(false); //参数窗口输入失效
             ui->PixWidth_dir_input->setEnabled(false);
             ui->PixHeight_dir_input->setEnabled(false);
             ui->Gain_dir_input->setEnabled(false);
             //设备1开始运行
             openThreadSlot_1();
             emit startObjThreadWork1();//主线程通过信号换起子线程的槽函数
             ui->state_Browser->append(">>Hik_Gray Camera.1 is running at Thread work 1");
             if(dev_num==2)
             {
                 hik_run_state = 1;
                 ui->Exposure_dir_input->setEnabled(false);  //参数窗口输入失效
                 ui->PixWidth_dir_input->setEnabled(false);
                 ui->PixHeight_dir_input->setEnabled(false);
                 ui->Gain_dir_input->setEnabled(false);
                 //设备2开始运行
                 openThreadSlot_2();
                 emit startObjThreadWork2();//主线程通过信号换起子线程的槽函数
                 ui->state_Browser->append(">>Hik_Gray Camera.2 is running at Thread work 2");
             }
             else
             {
                  ui->state_Browser->append(">>Hik_Gray Camera.2未连接！");
             }
             if(dev_num==3)
             {
                 hik_run_state = 1;
                 ui->Exposure_dir_input->setEnabled(false);  //参数窗口输入失效
                 ui->PixWidth_dir_input->setEnabled(false);
                 ui->PixHeight_dir_input->setEnabled(false);
                 ui->Gain_dir_input->setEnabled(false);
                 //设备2开始运行
                 openThreadSlot_2();
                 emit startObjThreadWork2();//主线程通过信号换起子线程的槽函数
                 ui->state_Browser->append(">>Hik_Gray Camera.2 is running at Thread work 2");
                 //设备3开始运行
                 openThreadSlot_3();
                 emit startObjThreadWork3();//主线程通过信号换起子线程的槽函数
                 ui->state_Browser->append(">>Hik_Gray Camera.3 is running at Thread work 3");
             }
             else
             {
                  ui->state_Browser->append(">>Hik_Gray Camera.3未连接！");
             }

        }
        else
        {
             ui->state_Browser->append(">>Hik_Gray Camera初始化失败！请先进行参数设定。");
        }
    }
    else
    {
        ui->state_Browser->append(">>Hik_Gray Camera正在运行，请勿重复点击开始按钮！");
    }
}

//Gray图像自动采集槽
void Soybean_Info_System::hik_gray_auto_capturing()
{
    if(hik_run_state == 1)
    {
        if (gray_auto_cap_cliced_flag != 0)
        {
            ui -> state_Browser -> append(">>Gray图像自动采集正在进行，请勿重复点击！");
        }
        else
        {

            QString gray_addr = ui -> gray_dir_input -> toPlainText();
            QString wrong_mess;

            QDir dir;
            if (!dir.exists(gray_addr))
            {
                wrong_mess = ">>路径设置错误，请检查文件夹路径";
                ui -> state_Browser -> append(wrong_mess);
            }
            else
            {
                //gray自动采集间隔时间控制
                gray_inter_time_add= ui -> gray_inter_time_input -> toPlainText();
                QString wrong_mess_gray_time;
                if (gray_inter_time_add == NULL)
                {
                    wrong_mess_gray_time = ">>请输入Gray图像采集间隔时间！";
                    ui -> state_Browser -> append(wrong_mess_gray_time);
                }
                else
                {
                    int gray_inter_time_length = gray_inter_time_add.length();
                    int jj = 0;
                    for(int k = 0;k<gray_inter_time_length;k++)
                    {
                        if(gray_inter_time_add.at(k)<'0'||gray_inter_time_add.at(k)>'9')
                        {
                            jj += 1;
                        }
                    }
                    if (jj == 0)
                    {
                        str_gray_addr = gray_addr.toStdString();

                        interval_time_gray = gray_inter_time_add.toInt();
                        timer_state_flag = 1;   //开启定时器标记
                        gray_auto_capture_timer(timer_state_flag);  //自动采集定时
                        gray_auto_cap_cliced_flag = 1; //点击事件控制
                        ui->state_Browser->append(">>Hik_Gray图像采集开始...，注意查看保存路径！手动采集按钮失效！");
                        ui->gray_dir_input->setDisabled(true);    //设置输入框失效
                        ui->gray_inter_time_input->setDisabled(true);
                    }
                    else
                    {
                        ui->state_Browser->append(">>Gray自动采集间隔时间错误，请输入正确时间格式，应为正整数！");
                    }
                }
            }
        }
    }
    else
    {
        ui->state_Browser->append(">>Gray自动采集失败！请先打开灰度相机。");
    }
}

//图片采集控制定时器槽
void Soybean_Info_System::gray_auto_capture_timer(int timer_state)
{
    //QString setTime = ui -> gray_inter_time_input-> toPlainText();
    //gray_timer->interval(2000);   //setTime.toInt()
    if (timer_state !=0)
    {
        gray_timer->start(interval_time_gray);
        connect(gray_timer, SIGNAL(timeout()), this, SLOT(gray_auto_cp_run()));
    }
    else
    {
        gray_timer->stop();
    }
}
void Soybean_Info_System::gray_auto_cp_run()
{
//    gray_manul_cap_state = 1; //手动采集停止标记
    gray_auto_cap_state = 1;   //冠层自动采集开始标志

}
//END

//Gray图像自动采集停止槽
void Soybean_Info_System::hik_gray_auto_stop()
{
        timer_state_flag = 0;   //关闭定时器标记
        gray_auto_capture_timer(timer_state_flag);
        gray_auto_cap_state = 0; //自动采集停止标志
        gray_auto_cap_cliced_flag = 0; //点击控制，自动采集按钮可用
        ui->gray_dir_input->setDisabled(false);    //设置输入框可用
        ui->gray_inter_time_input->setDisabled(false);
        ui->state_Browser->append(">>Gray图像自动采集停止，重新点击自动采集可继续采集，若重新启动本程序请重新设置路径或文件名，避免图像被覆盖！");
}
//END

//Gray图像手动采集槽
void Soybean_Info_System::hik_gray_manul_capturing()
{
    if(hik_run_state == 1)
    {
        if(gray_auto_cap_cliced_flag != 0)
        {
            ui -> state_Browser -> append(">>Gray图像正在自动采集中...,请关闭自动采集后再进行手动采集！");
        }
        else
        {
            QString gray_addr = ui -> gray_dir_input -> toPlainText();
            QString wrong_mess;
            QDir dir;
            if (!dir.exists(gray_addr))
            {
                wrong_mess = ">>路径设置错误，请检查文件夹路径";
                ui -> state_Browser -> append(wrong_mess);
            }
            else
            {
                str_gray_addr = gray_addr.toStdString();
                gray_manul_cap_state = 1;   //冠层手动采集一次开始标记
                ui->state_Browser->append(">>Gray图像手动采集一次");
            }
        }
    }
    else
    {
        ui->state_Browser->append(">>Gray手动采集失败！请先打开灰度相机。");
    }
}

//关闭hik_Gray设备槽
void Soybean_Info_System::close_hik_gray()
{
    hik_gray_auto_stop();
    closeThreadSlot();
    hik_run_state = 0;   //运行状态初始化
    hik_init_state = 0;  //参数设定状态初始化
    ui->Exposure_dir_input->setEnabled(true); //参数窗口输入失效
    ui->PixWidth_dir_input->setEnabled(true);
    ui->PixHeight_dir_input->setEnabled(true);
    ui->Gain_dir_input->setEnabled(true);
    QString stop_message = ">>Hik_Gray设备已关闭！";
    ui->state_Browser->append(">><font color=\"#FF0000\">" + stop_message + "</font> ");
    //清除主窗口显示
    ui->imglabel_hik1->setText("Hik imgshow 1");
    ui->imglabel_hik2->setText("Hik imgshow 2");
    ui->imglabel_hik3->setText("Hik imgshow 3");
    ui->imglabel_hik4->setText("Hik imgshow 4");
}

///////////////////////////END/////////////////////////////////

//////////////////////以下为多线程控制函数/////////////////////////
//HIK相机线程///////////////////////////////////////////////////
//创建线程hik1
void Soybean_Info_System::openThreadSlot_1()
{
//    if(m_firtThread)
//    {
//        return;
//    }
//int* arr_Thread = new int [2];

    m_firtThread_privaty = new QThread();
    m_objThread_privaty = new ThreadObject();
    m_objThread_privaty->moveToThread(m_firtThread_privaty);

    connect(m_firtThread_privaty,SIGNAL(finished()),m_firtThread_privaty,SLOT(deleteLater()));
    connect(m_firtThread_privaty,SIGNAL(finished()),m_objThread_privaty,SLOT(deleteLater()));

    connect(this,&Soybean_Info_System::startObjThreadWork1,m_objThread_privaty,&ThreadObject::startThreadSlot_camara_1);
//    connect(this,&Soybean_Info_System::startObjThreadWork2,m_objThread_privaty,&ThreadObject::startThreadSlot_camara_2);

    //connect(m_firtThread,SIGNAL(started()),m_objThread,SLOT(startThreadSlot_camara_1()));

    connect(m_firtThread_privaty,SIGNAL(finished()),this,SLOT(finishedThreadSlot()));

//    connect(this,&Soybean_Info_System::startObjThreadWork1,m_obj,&ThreadObject::runSomeBigWork1);
//    connect(this,&Soybean_Info_System::startObjThreadWork2,m_obj,&ThreadObject::runSomeBigWork2);
//    connect(m_obj,&ThreadObject::progress,this,&Soybean_Info_System::progress);
//    connect(m_obj,&ThreadObject::message,this,&Soybean_Info_System::receiveMessage);
     m_firtThread_privaty->start();
     qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();
//     int * re_m_firstThread = (int *) m_firtThread_privaty;
//     int * re_m_objThread = (int *) m_objThread_privaty;
//     arr_Thread[1] = *re_m_firstThread;
//     arr_Thread[2] = *re_m_objThread;
//     return arr_Thread;
}
//创建线程hik2
void Soybean_Info_System::openThreadSlot_2()
{
//    if(m_firtThread)
//    {
//        return;
//    }
//int* arr_Thread = new int [2];

    m_firtThread_privaty_2 = new QThread();
    m_objThread_privaty_2 = new ThreadObject();
    m_objThread_privaty_2->moveToThread(m_firtThread_privaty_2);

    connect(m_firtThread_privaty_2,SIGNAL(finished()),m_firtThread_privaty_2,SLOT(deleteLater()));
    connect(m_firtThread_privaty_2,SIGNAL(finished()),m_objThread_privaty_2,SLOT(deleteLater()));

//    connect(this,&Soybean_Info_System::startObjThreadWork1,m_objThread_privaty,&ThreadObject::startThreadSlot_camara_1);
    connect(this,&Soybean_Info_System::startObjThreadWork2,m_objThread_privaty_2,&ThreadObject::startThreadSlot_camara_2);

    //connect(m_firtThread,SIGNAL(started()),m_objThread,SLOT(startThreadSlot_camara_1()));

    connect(m_firtThread_privaty_2,SIGNAL(finished()),this,SLOT(finishedThreadSlot()));

//    connect(this,&Soybean_Info_System::startObjThreadWork1,m_obj,&ThreadObject::runSomeBigWork1);
//    connect(this,&Soybean_Info_System::startObjThreadWork2,m_obj,&ThreadObject::runSomeBigWork2);
//    connect(m_obj,&ThreadObject::progress,this,&Soybean_Info_System::progress);
//    connect(m_obj,&ThreadObject::message,this,&Soybean_Info_System::receiveMessage);
     m_firtThread_privaty_2->start();
     qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();
//     int * re_m_firstThread = (int *) m_firtThread_privaty;
//     int * re_m_objThread = (int *) m_objThread_privaty;
//     arr_Thread[1] = *re_m_firstThread;
//     arr_Thread[2] = *re_m_objThread;
//     return arr_Thread;
}

//创建线程hik3
void Soybean_Info_System::openThreadSlot_3()
{
    m_firtThread_privaty_3 = new QThread();
    m_objThread_privaty_3 = new ThreadObject();
    m_objThread_privaty_3->moveToThread(m_firtThread_privaty_3);
    connect(m_firtThread_privaty_3,SIGNAL(finished()),m_firtThread_privaty_3,SLOT(deleteLater()));
    connect(m_firtThread_privaty_3,SIGNAL(finished()),m_objThread_privaty_3,SLOT(deleteLater()));
    connect(this,&Soybean_Info_System::startObjThreadWork3,m_objThread_privaty_3,&ThreadObject::startThreadSlot_camara_3);
    connect(m_firtThread_privaty_3,SIGNAL(finished()),this,SLOT(finishedThreadSlot()));

    m_firtThread_privaty_3->start();
    qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();

}
///////////////////////////////////////////////////////////////////
//KINECT线程////////////////////////////////////////////////////////
//创建kinect_1线程
void Soybean_Info_System::openThreadSlot_kinect_1()
{
    m_firtThread_privaty_k1 = new QThread();
    m_objThread_privaty_k1 = new ThreadObject();
    m_objThread_privaty_k1->moveToThread(m_firtThread_privaty_k1);

    connect(m_firtThread_privaty_k1,SIGNAL(finished()),m_firtThread_privaty_k1,SLOT(deleteLater()));
    connect(m_firtThread_privaty_k1,SIGNAL(finished()),m_objThread_privaty_k1,SLOT(deleteLater()));
    connect(this,&Soybean_Info_System::startObjThreadWork_k1,m_objThread_privaty_k1,&ThreadObject::startThreadSlot_Kinect_1);
    connect(m_firtThread_privaty_k1,SIGNAL(finished()),this,SLOT(finishedThreadSlot_kinect()));

     m_firtThread_privaty_k1->start();
     qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();
}
//创建kinect_2线程
void Soybean_Info_System::openThreadSlot_kinect_2()
{
    m_firtThread_privaty_k2 = new QThread();
    m_objThread_privaty_k2 = new ThreadObject();
    m_objThread_privaty_k2->moveToThread(m_firtThread_privaty_k2);

    connect(m_firtThread_privaty_k2,SIGNAL(finished()),m_firtThread_privaty_k2,SLOT(deleteLater()));
    connect(m_firtThread_privaty_k2,SIGNAL(finished()),m_objThread_privaty_k2,SLOT(deleteLater()));
    connect(this,&Soybean_Info_System::startObjThreadWork_k2,m_objThread_privaty_k2,&ThreadObject::startThreadSlot_Kinect_2);
    connect(m_firtThread_privaty_k2,SIGNAL(finished()),this,SLOT(finishedThreadSlot_kinect()));

     m_firtThread_privaty_k2->start();
     qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();
}
//创建kinect_3线程
void Soybean_Info_System::openThreadSlot_kinect_3()
{
    m_firtThread_privaty_k3 = new QThread();
    m_objThread_privaty_k3 = new ThreadObject();
    m_objThread_privaty_k3->moveToThread(m_firtThread_privaty_k3);

    connect(m_firtThread_privaty_k3,SIGNAL(finished()),m_firtThread_privaty_k3,SLOT(deleteLater()));
    connect(m_firtThread_privaty_k3,SIGNAL(finished()),m_objThread_privaty_k3,SLOT(deleteLater()));
    connect(this,&Soybean_Info_System::startObjThreadWork_k3,m_objThread_privaty_k3,&ThreadObject::startThreadSlot_Kinect_3);
    connect(m_firtThread_privaty_k3,SIGNAL(finished()),this,SLOT(finishedThreadSlot_kinect()));

     m_firtThread_privaty_k3->start();
     qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();
}
//关闭hik线程
void Soybean_Info_System::closeThreadSlot()
{
    qDebug()<<tr("关闭线程");

    if (hik_run_state == 1)
    {
        if (m_firtThread_privaty)
            {
                m_objThread_privaty->closeThread(global_handle_1);  //关闭线程槽函数
                m_firtThread_privaty->quit();            //退出事件循环
                m_firtThread_privaty->wait();            //释放线程槽函数资源
                m_firtThread_privaty = nullptr;
                dev_num = 0;
            }
        else
            {
               qDebug()<<tr("1号灰度相机线程未运行");
            }
        if(m_firtThread_privaty_2)
            {
                m_objThread_privaty_2->closeThread(global_handle_2);  //关闭线程槽函数
                m_firtThread_privaty_2->quit();            //退出事件循环
                m_firtThread_privaty_2->wait();            //释放线程槽函数资源
                m_firtThread_privaty_2 = nullptr;
                dev_num = 0;
            }
        else
            {
               qDebug()<<tr("2号灰度摄像头线程未运行");
            }
        if(m_firtThread_privaty_3)
            {
                m_objThread_privaty_3->closeThread(global_handle_3);  //关闭线程槽函数
                m_firtThread_privaty_3->quit();            //退出事件循环
                m_firtThread_privaty_3->wait();            //释放线程槽函数资源
                m_firtThread_privaty_3 = nullptr;
                dev_num = 0;
            }
        else
            {
               qDebug()<<tr("3号灰度摄像头线程未运行");
            }
    }
    else
    {
        ui->state_Browser->append(">>Hik Camera设备未运行！");
    }

}
//关闭kinect线程
void Soybean_Info_System::closeThreadSlot_kinect()
{
    qDebug()<<tr("关闭kinect线程");
    if(m_firtThread_privaty_k1)
    {
        m_objThread_privaty_k1->closeThread_Kinect();
        m_firtThread_privaty_k1->quit();
        m_firtThread_privaty_k1->wait();
        m_firtThread_privaty_k1 = nullptr;
    }
    if(m_firtThread_privaty_k2)
    {
        m_objThread_privaty_k2->closeThread_Kinect();
        m_firtThread_privaty_k2->quit();
        m_firtThread_privaty_k2->wait();
        m_firtThread_privaty_k2 = nullptr;
    }
    if(m_firtThread_privaty_k3)
    {
        m_objThread_privaty_k3->closeThread_Kinect();
        m_firtThread_privaty_k3->quit();
        m_firtThread_privaty_k3->wait();
        m_firtThread_privaty_k3 = nullptr;
    }
    else
    {
        qDebug() << "当前KINECT线程未运行，不用重复点击！";
    }

}

//线程关闭完成触发信号
void Soybean_Info_System::finishedThreadSlot()
{
    qDebug()<<tr("多线程触发了finished信号hik_camera关闭！");
}
void Soybean_Info_System::finishedThreadSlot_kinect()
{
    qDebug()<<tr("多线程触发了finished信号Kinect关闭！");
}
////////////////////////////////////////////////////////////
//智能识别控制线程A1////////////////////////////////////////
//创建kinect_3线程
void Soybean_Info_System::openThreadSlot_AIK1()
{
    m_firtThread_privaty_aik1 = new QThread();
    m_objThread_privaty_aik1 = new ThreadObject();
    m_objThread_privaty_aik1->moveToThread(m_firtThread_privaty_aik1);

    connect(m_firtThread_privaty_aik1,SIGNAL(finished()),m_firtThread_privaty_aik1,SLOT(deleteLater()));
    connect(m_firtThread_privaty_aik1,SIGNAL(finished()),m_objThread_privaty_aik1,SLOT(deleteLater()));
    connect(this,&Soybean_Info_System::startObjThreadWork_aik1,m_objThread_privaty_aik1,&ThreadObject::startThreadSlot_AIKinect_1);
    connect(m_firtThread_privaty_aik1,SIGNAL(finished()),this,SLOT(finishedThreadSlot_AIkinect()));

    m_firtThread_privaty_aik1->start();
    //连接子线程与步进电机控制槽
    connect(m_objThread_privaty_aik1,&ThreadObject::sendtomain,this,&Soybean_Info_System::send_to_stepper); //连接子线程，获得信号。控制步进电机
    qDebug()<<"mainWidget QThread::currentThreadId()=="<<QThread::currentThreadId();
}

void Soybean_Info_System::closeThreadSlot_AIkinect()
{
    qDebug()<<tr("关闭kinect detect识别线程");
    if(m_firtThread_privaty_aik1)
    {
        m_objThread_privaty_aik1->closeThread_AIKinect();
        m_firtThread_privaty_aik1->quit();
        m_firtThread_privaty_aik1->wait();
        m_firtThread_privaty_aik1 = nullptr;
        read_share_flag = 0; //标记归0，允许下次读取共享数据；
    }
    else
    {
        qDebug() << "当前kinect detect识别线程未运行，不用重复点击！";
    }

}
void Soybean_Info_System::finishedThreadSlot_AIkinect()
{
    qDebug()<<tr("多线程触发了finished信号kinect detect识别关闭！");
}
//////////////////////////////////////////////////////////////
//控制PLC信号线程////////////////////////////////////////////
//创建PLC线程//
void Soybean_Info_System::openThreadSlot_PLC()
{
    m_firtThread_privaty_plc = new QThread();
    m_objThread_privaty_plc = new ThreadObject();
    m_objThread_privaty_plc->moveToThread(m_firtThread_privaty_plc);

    connect(m_firtThread_privaty_plc,SIGNAL(finished()),m_firtThread_privaty_plc,SLOT(deleteLater()));
    connect(m_firtThread_privaty_plc,SIGNAL(finished()),m_objThread_privaty_plc,SLOT(deleteLater()));
    connect(this,&Soybean_Info_System::startObjThreadWork_plc,m_objThread_privaty_plc,&ThreadObject::startThreadSlot_PLC);
    connect(m_firtThread_privaty_plc,SIGNAL(finished()),this,SLOT(finishedThreadSlot_PLC()));

    m_firtThread_privaty_plc->start();
    //连接子线程与PLC控制槽
    connect(m_objThread_privaty_plc,&ThreadObject::send_to_plc,this,&Soybean_Info_System::PLC_Contrl_Slot); //连接子线程，获得信号。控制步进电机
    connect(m_objThread_privaty_plc,&ThreadObject::message,this,&Soybean_Info_System::receiveMessage);//子线程与信息槽连接
    connect(m_objThread_privaty_plc,&ThreadObject::All_Dev_Cap_Start,this,&Soybean_Info_System::All_device_capture_start);//子线程与图像捕捉开始槽连接
    connect(m_objThread_privaty_plc,&ThreadObject::All_Dev_Cap_Stop,this,&Soybean_Info_System::All_device_capture_stop);//子线程与图像捕捉停止槽连接
    qDebug()<<"mainWidget QThread::currentThreadId()==PLC"<<QThread::currentThreadId();
}

void Soybean_Info_System::closeThreadSlot_PLC()
{
    qDebug()<<tr("关闭PLC控制线程");
    if(m_firtThread_privaty_plc)
    {
        m_objThread_privaty_plc->closeThread_PLC();
        m_firtThread_privaty_plc->quit();
        m_firtThread_privaty_plc->wait();
        m_firtThread_privaty_plc = nullptr;
        plc_stop_flag = 0; //PLC停止采集标记归零；
    }
    else
    {
        qDebug() << "当前PLC控制线程未运行，不用重复点击！";
    }
}
void Soybean_Info_System::finishedThreadSlot_PLC()
{
    qDebug()<<tr("多线程触发了finished信号PLC控制关闭！");
}

void Soybean_Info_System::PLC_Contrl_Slot(QString send_data_plc)
{
    //向串口发送数据给PLC
    serialport_send(send_data_plc);
}
void Soybean_Info_System::receiveMessage(QString rec_message)
{
    //向状态窗口显示从PLC线程发来的信息
    ui->state_Browser->append(">><font color=\"#0000FF\">"+rec_message+"</font>");
}

///////////////////////END/////////////////////////////////
///////////////////转换开关控制槽////////////////////////////
//switch开关槽连接函数，曝光自动开关控制//
void Soybean_Info_System::Exposure_auto_contrl(bool checked)
{
    if(checked)
    {
        ui ->state_Browser->append(">>自动曝光打开");
        exposure_auto_set = true;
    }
    else
    {
        ui ->state_Browser->append(">>自动曝光关闭");
        exposure_auto_set = false;
    }

}
//END//
///////////////////////END/////////////////////////////////

//////////////退出程序控制模块//////////////////////////////
//退出系统模块，调用关闭even事件
void Soybean_Info_System::on_sys_exit_Btn_clicked()
{
    close();
}

/////////////////状态窗口清除控制槽/////////////////////////
void Soybean_Info_System::on_clean_state_history_Btn_clicked()
{
    ui->state_Browser->clear();
}
//////////////////////END////////////////////////////////


//智能识别控制区按钮事件
//开启共享内存获取监测数据，同时打开detect识别检测
void Soybean_Info_System::on_load_py_Btn_clicked()
{

    Py_Initialize();
    int fxm = load_detect();

    qDebug()<<"fxm=====007"<<fxm<<Qt::endl;

}

void Soybean_Info_System::on_read_share_Btn_clicked()
{
    read_share_flag = 0;
    openThreadSlot_AIK1();
    emit startObjThreadWork_aik1();//主线程通过信号换起子线程的槽函数

}

void Soybean_Info_System::on_readshare_stop_Btn_clicked()
{

//    read_share_flag = 1;
    closeThreadSlot_AIkinect();

//    python_loop_flag.startThreadSlot_AIKinect_1();
     python_loop_flag.stop_detect_loop();
}


void Soybean_Info_System::on_readshare_stop_detect_Btn_clicked()
{
//    mthread =new SerialThread("ttyUSB1",57600);
//    mthread->run();

//      stop_detect();
////    int stop_flag = python_loop_flag.stop_detect_loop();
////    qDebug()<<"stop_flag"<<stop_flag<<Qt::endl;
}
//////////////////////////////////END////////////////////////////////////
///

//全部设备PLC采集控制槽/////////////////////////////////
//关闭全部设备PLC控制
void Soybean_Info_System::ALL_Device_PLC_Close()
{
    closeThreadSlot_PLC();
    Close_All_device();
    if(hexData == "ffaaff0d0a")
    {
        ui->state_Browser->append(">><font color=\"#0000FF\">以接收到PLC停止反馈信号</font>");
    }
    ui->state_Browser->append(">><font color=\"#0000FF\">全设备图像采集PLC控制停止，请更新图像保存文件夹，避免图像覆盖！！</font>");
}
//打开全部设备PLC控制
void Soybean_Info_System::ALL_Device_PLC_AutoRun()
{
    int is_alldevisopen; //设备是否打开：1打开，0未打开。
    if(plc_run_state ==1)
    {
        ui->state_Browser->append(">>全设备图像采集PLC控制正在运行，请勿重复点击。");
    }
    else{
        if(serial_flag == 0) //检测串口是否初始化
        {
            ui->state_Browser->append(">>与驱动器通讯异常：串口未打开！");
        }
        else
        {
            is_alldevisopen = Open_All_device(); //打开全部图像采集设备
            if (is_alldevisopen ==1)
            {
                plc_stop_flag = 0;
                openThreadSlot_PLC();
                emit startObjThreadWork_plc();//主线程通过信号换起PLC子线程的槽函数
            }
            else
            {
                ui->state_Browser->append(">>请先确认全部参数后重试！");
            }

        }
    }

//串口参数
//  setBaudRate 设置波特率 57600
//  SerialPort::Data8);		//数据位为8位
//  SerialPort::NoParity);	//无校验位
//  SerialPort::OneStop); //一位停止位
//  SerialPort::NoFlowControl);//无流控制
//控制方式
//1：向采集车PLC发送信号开始工作信号， 发送 0x10 0x01 ox00 0x0d 0x0a
//PLC接收到该信号后，控制步进电机归位，同时控制行走伺服电机工作，上位机等待接收PLC信号。

//2：接收到反馈：oxff 0x01 0x01 0x0d 0x0a，PLC正在控制行走

//3：接收到 0xff 0x01 0xff 0x0d 0x0a，PLC到达指定位置，可以开始采集
//接收到PLC允许开始采集信号（采集车运行到位，PLC开始控制两侧步进电机工作，所有图像开始采集）
//同时向PLC发送0x10 0x02 0x00 0x0d 0x0a，即已经开始图像采集，PLC接收到后开始控制步进电机工作
//PLC接受到信号后，向上位机发送0xff 0x02 0x01 0x0d 0x0a反馈，即PLC开始控制步进电机工作

//4：步进电机运行到指定位置后，PLC向上位机发送0xff 0x02 0xff 0x0d 0x0a，即步进电机到达指定位置。
//（采集车控制步进电机到达指定位置后，返回信号，上位机接到信号后停止图像存储）

//5：循环开始：
//向PLC发送采集信号，发送 0x10 0x01 ox00 0x0d 0x0a
//同第一步

//6:设备停止信号 向PLC发送 0x10 0xaa 0xdd 0x0d 0x0a ，PLC停止工作并反馈信号

//7：上位机接收到 0xff 0xaa 0xff 0x0d 0x0a ，采集停止，关闭全部采集设备。
}

