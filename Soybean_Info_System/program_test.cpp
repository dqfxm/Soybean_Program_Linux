#include "program_test.h"
#include "ui_program_test.h"
#include <QDebug>
#include <QDir>
#include <QString>
#include "sorting_control.h"
#include <iostream>
#include <MvCameraControl.h>

Program_Test::Program_Test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Program_Test)
{
    ui->setupUi(this);
}

Program_Test::~Program_Test()
{
    delete ui;
}

void Program_Test::on_OK_Btn_clicked()
{
    //获取应用程序的目录
//    QString strCurrentApplicationDirPath=QCoreApplication::applicationDirPath();
//    qDebug()<<strCurrentApplicationDirPath;
    QString strPath = ui->File_addr_Browser->toPlainText();
    //发送未转换的路径
    Addr = strPath ;
    emit Send_Addr(Addr);
    qDebug()<<"路径已发送";
}

void Program_Test::on_Switch_to_back_Btn_clicked()
{
    QString strPath = ui->File_addr_Browser->toPlainText();

    /*将/转\（斜杠转反斜杠）*/  //系统正常路径未 "D:\"/
    Addr = QDir::toNativeSeparators(strPath);
    emit Send_Addr(Addr);

}

void Program_Test::on_Switch_to_Slash_Btn_clicked()
{
    QString strPath = ui->File_addr_Browser->toPlainText();
    /*将\转/（反斜杠转斜杠）*/  //C语言路径使用 "D:/ "/
    Addr = QDir::fromNativeSeparators(strPath);
    emit Send_Addr(Addr);
}

void Program_Test::on_Save_Conf_Btn_clicked()
{
    writeConfig(); //写配置文件
}


void Program_Test::on_Load__Conf_Btn_clicked()
{
    readConfig(); //读配置文件
}

/***********************************
*  @brief:读写配置文件               *
*  @ param:[in]                    *
*  @ param:[out]                   *
*  @ return:                       *
*  @ author:FXM                    *
*  @ data:2021-5-5                 *
*  @ note:                         *
************************************/
//写配置文件
void Program_Test::writeConfig()
{
    //读取输入栏的值
    QString FileBrowser = ui->File_addr_Browser->toPlainText();

    //创建ini配置文件
    iniFile = new QSettings("./config/testConfig.ini",QSettings::IniFormat);
    //创建组
    iniFile->beginGroup(tr("FXM"));
    //设置键值对
    iniFile->setValue(tr("File_Dir"), FileBrowser);
    iniFile->setValue(tr("Camera_Name"), tr("Kincet"));
    iniFile->setValue(tr("User_Name"), tr("FXM"));
    //获取当前组
    QString group=iniFile->group();
    qDebug().noquote()<<"group:"<<group;
    //组结束
    iniFile->endGroup();
    //写入完成后删除指针
    delete iniFile;
    //删除当前指针配置中的全部配置内容
    //iniFile->clear();

}
//读取配置文件
void Program_Test::readConfig()
{
    iniFile = new QSettings("./config/testConfig.ini",QSettings::IniFormat);
    //判断键是否存在
    bool key=iniFile->contains("FXM/File_Dir");
    qDebug().noquote()<<"FXM/File_Dir is "<<key;
    //移除组或组内键
    //iniFile->remove("FXM");
    //读取键值对
    QString FileDir = iniFile->value("FXM/File_Dir").toString();
    QString CameraName = iniFile->value("FXM/Camera_Name").toString();
    ui->File_addr_Browser->clear();
    ui->File_addr_Browser->append(FileDir);

    qDebug()<<FileDir<<CameraName;
    delete iniFile;



}


//删除配置文件
void Program_Test::clearConfig()
{

}



//写配置文件参考资料
//QCoreApplication a(argc, argv);
//   //Qt中使用QSettings类读写ini文件
//   //QSettings构造函数的第一个参数是ini文件的路径,第二个参数表示针对ini文件,第三个参数可以缺省
//   QSettings *configIniWrite = new QSettings("hahaya.ini", QSettings::IniFormat);
//   //向ini文件中写入内容,setValue函数的两个参数是键值对
//   //向ini文件的第一个节写入内容,ip节下的第一个参数
//   configIniWrite->setValue("/ip/first", "192.168.0.1");
//   //向ini文件的第一个节写入内容,ip节下的第二个参数
//   configIniWrite->setValue("ip/second", "127.0.0.1");
//   //向ini文件的第二个节写入内容,port节下的第一个参数
//   configIniWrite->setValue("port/open", "2222");
//   //写入完成后删除指针
//   delete configIniWrite;

//读配置文件参考资料
//QSettings *configIniRead = new QSettings("hahaya.ini", QSettings::IniFormat);
////将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
//QString ipResult = configIniRead->value("/ip/second").toString();
//QString portResult = configIniRead->value("/port/open").toString();
////打印得到的结果
//qDebug() << ipResult;
//qDebug() << portResult;
////读入入完成后删除指针
//delete configIniRead;


CTimer *pTimer = new CTimer("定时器1");

void Program_Test::on_time_out_Btn_clicked()
{
    int ttest = 0;
//    std::cout << ttest <<std::endl;
//    send_stepper_signal(&ttest);
//    std::cout << ttest <<std::endl;
//    CTimer *pTimer = new CTimer("定时器1");
    pTimer->AsyncOnce(0, send_stepper_signal,&ttest);	//异步执行一次，间隔时间all_send_time[ss]毫秒
    std::cout << ttest <<std::endl;
}


void Program_Test::on_savefile_Btn_clicked()
{

    vector<vector<double>> aaray(3);
    vector<double> linedata(4,0);
    for (int i = 0;i<4 ;i++ ) {
        linedata[i]=i;
    }
    aaray.push_back(linedata);
    for (int i = 0;i<4 ;i++ ) {
        linedata[i]=i+1;
    }
    aaray.push_back(linedata);
    savefile.saveArray(aaray,"/home/fuxiaoming/savetest",6);
}


void Program_Test::on_hik_disp_Btn_clicked()
{
    int nRet = MV_OK;

    // Enum device
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet)
    {
        printf("Enum Devices fail! nRet [0x%x]\n", nRet);

    }

    if (stDeviceList.nDeviceNum > 0)
    {
        for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
        {
            printf("[device %d]:\n", i);
            MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
            if (NULL == pDeviceInfo)
            {
                printf("no device info\n");
            }
        }
    }
    else
    {
        printf("Find No Devices!\n");
    }
}

