#include "sorting_control.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <QTime>
#include <unistd.h>
#include <sys/time.h>


//std::vector<int> w(7,0);
//std::vector<std::vector<int> > arr(1, w);   // 9行10列 二维数组

double distance_of_stepper_kinectedge;  //步进电机与镜头边缘距离常数
double distance_of_obj_kinectedge;    //识别目标距镜头边缘距离变量
int vertical_pixel;  //垂直方向像素 720
double vertical_actual_distance; //需实际测量，单位mm
double per_pixel_distance;       //每个像素点的实际距离
double conveyer_speed;        //传送带速度，需要与主传送速度一直，mm/s
extern int sendover_flag;    //传递完成全局变量30
//计算识别位置到步进电机所需延迟控制时间函数
//输入：识别数据数组
//返回：延迟时间ms
//时间：2022.03.26
//编写：fxm


int sort_locat_time_comput_control(float * obj_data)
{
    int contrl_delay_time; //单位ms
    double total_distance; //目标中心点距步进电机的距离,单位mm
    distance_of_stepper_kinectedge = 60; //需实际测量，单位毫米
    conveyer_speed = 68;  //500mm/s的传送速度 3300r/min->449mm/s，500r/min->68mm/s
    vertical_pixel = 720;
    vertical_actual_distance=260;  //需实际测量，单位毫米
    per_pixel_distance=vertical_actual_distance/vertical_pixel;
    distance_of_obj_kinectedge = per_pixel_distance*(720-obj_data[4]+(obj_data[4]-obj_data[2])/2);

    total_distance = distance_of_obj_kinectedge+distance_of_stepper_kinectedge;
    contrl_delay_time = std::round(1000*total_distance/conveyer_speed); //单位毫米/s
//    qDebug()<<obj_data[6]<<Qt::endl;
    return contrl_delay_time;
}

void send_stepper_signal(int *object_class)
{
//    sub_serial_send sub_serialport;
    std::cout <<"发送完成标记"<<sendover_flag<<std::endl;
    sendover_flag = 1;
    int &obj_class = *object_class;
    QString run_dir_clk = "00";
    QString run_dir_cclk = "01";
    std::cout <<"*object_class"<<*object_class<<std::endl;
    std::cout <<"obj_class"<<obj_class<<std::endl;
    if (obj_class == 0){ //步进电机挡板对中，左右判断
        std::cout <<"发现手机phone，开始发送"<<sendover_flag<<std::endl;
        stepmotor_run(run_dir_clk,120,40); //输入：方向QString，角度int，速度int
        //        sub_serialport.serial_send(step_order);
    }
    if (obj_class == 1){
        std::cout <<"发现剪刀scissors，开始发送"<<sendover_flag<<std::endl;
        stepmotor_run(run_dir_cclk,120,40); //输入：方向QString，角度int，速度int
        //        sub_serialport.serial_send(step_order);
    }
    std::cout <<"obj_class"<<obj_class<<std::endl;
    std::cout <<"发送完成标记"<<sendover_flag<<std::endl;

}


//    //长时间计时
//    timeval start, end;
//    gettimeofday(&start,NULL);
//    usleep(50000);
//    //需要计时的代码段
//    gettimeofday(&end, NULL);
//    //运行时间
//    int t = 1000*(end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)/1000; //（单位ms）
//    int t2 = 1000*start.tv_sec+(start.tv_usec/1000); //（单位ms）
//    int t3 = 1000*end.tv_sec+(end.tv_usec/1000); //（单位ms）
//    std::cout << t <<":"<<t2<<":"<<t3<<std::endl;
//   短时间计时，不准 ///////////////////////
//        clock_t start,ends;
//        start = clock();
//        sleep(2);
//        ends = clock();
////        int endtime = ends-start;
////        std::cout<<endtime<<":"<<start<<ends<<":" <<CLOCKS_PER_SEC <<std::endl;
//        double endtime=(double)(ends-start)/CLOCKS_PER_SEC;
//        std::cout<<"Total time:"<<endtime<<std::endl;		//s为单位
//        std::cout<<"Total time:"<<endtime*1000<<"ms"<<std::endl;	//ms为单位

//    std::vector<int>a(7);
//    for (int i=0;i<7;i++)
//    {
//        a[i]=i;
//    }
//    //int w = arr[0];
//    arr.push_back(std::vector<int>(7,9));
