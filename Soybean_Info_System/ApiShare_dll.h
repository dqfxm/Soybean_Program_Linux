#ifndef APISHARE_DLL_H
#define APISHARE_DLL_H

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

using namespace std;
using namespace cv;

namespace MyShare{

    #define Shm_addrees 1275 //共享内存地址标识1203

    #define IMAGE_W 1280  //图像宽
    #define IMAGE_H  720  //图像高
    #define IMAGE_SIZE  IMAGE_W*IMAGE_H*3 //图片像素总大小 3通道彩色

     //共享内存-图像
    typedef struct ShareData
    {
        int flag;
        int obtctrl_flag;
        int rows;//图像高
        int cols;//图像宽
        char imgdata[IMAGE_SIZE];//图像数据一维数据，之前用了cv::Mat不行，因为无法在结构体里初始化大小
        float Gps[4];//保存gps信息 经纬高时间戳
        float obtctrl[7]; //保存目标定位控制信息，数量、xyxy，精度，类别
        int stopflag;  //控制python停止标记
    }ShareData_;

    // 非共享内存-传送gps混合数据
    typedef struct StructGpsData
    {
        int flag;
        char *msg;
        float longitude;
        float latitude;
        float high;
        float time;
    } StructGpsData_;
    //非共享内存-传目标定位数据(与传送gps类似)
    typedef struct LocationCtrlData
    {
        int flag;
        int x_leftup;
        int y_leftup;
        int x_rightdown;
        int y_rightdown;
        float obt_precision;
        int cls_name;
    }LocationCtrlData_;

    class Share_class
    {
       //变量定义
       public:
           //1创建共享内存
           int shmid;
           //2映射共享内存地址  shm指针记录了起始地址
           void *shm=nullptr;//如果创建一个函数每次调用都执行，需要执行完释放一下shmdt
           //printf("共享内存地址 ： %p\n", (int *)(shm));

           //2-1以ShareData结构体类型-访问共享内存
           ShareData *pShareData;

           //用来保存转化后的共享内存的图像结果
           cv::Mat cvoutImg;//bufHight,bufWidth

          //未来加速 可以搞一个图像队列 队列大小3  不停存图，然后挨着丢进共享内存，满了就清除。

       //函数定义
       public:
           Share_class();//1构造函数
           ~Share_class();//2销毁执行

           int InitShare();
           int DestroyShare();
           int Send_pic2_share_once(cv::Mat Img);
           int pySend_pic2_share_once(uchar *frame_data, int height, int width);
           int Rec_pic2_data_once();
           uchar* Img_Cgg2py();
           int Get_ImgFlag();
           int Set_ImgFalg(int value);
           float pyarr_set_cgg_gps_share(float *data, int len);
           uchar* py_get_cgg_gps_share();
           StructGpsData py_get_cgg_gps_Struct(StructGpsData gps);
           StructGpsData py_Set_cgg_gps_Struct( StructGpsData gps);
           int Set_loop_flag(int value); //设置停止python主循环控制
           int Get_loop_flag(); //获取停止python主循环控制
           //目标定位控制函数
           float pyarr_set_cgg_obtctrl_share(float *data,int len);

    };//类定义结束
}//namespace 定义

#endif // APISHARE_DLL_H


