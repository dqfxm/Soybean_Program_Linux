#include "receive_data_from_share.h"
#include "ApiShare_dll.cpp"

using namespace std;

extern int read_share_flag;
//vector<int> w(10, 1);
int sendover_flag;

receive_data::receive_data(QObject *parent):QObject(parent)
{

}
receive_data::~receive_data(){

}

void receive_data::receive_frompyhton_init()
{
    //1创建对象
    //MyShare::Share_class useShare;
    useShare.InitShare();
    //qDebug()<<useShare.pShareData->obtctrl_flag<<Qt::endl;
}

//void receive_data::send_signal(int *sendover_flag, int object_class)
//{
//    sorting_ctl.send_stepper_signal(sendover_flag,object_class);
//}

int receive_data::recdata_frompython_run()
{
    //2创建接受图像
    // cv::Mat RecImg = cv::Mat(720,1280,CV_8UC3,cv::Scalar(255, 255, 255));//bufHight,bufWidth

    //3接受GPS数据
    //float Gps_c[4];

    //3接受obtctrl数据
    float Obtctrl_C[7];
    useShare.pShareData->obtctrl_flag = 0; //允许存数据
    //4接受延迟控制时间delay_time
    int delay_time;
    int tt = 0;    //获取延时时间序列计数
    int ss = 0;    //发送延时序列计数
    int obj_class[1] ={0};

    sendover_flag = 1;     //发送完成标记，0：未发送完不可进行发送，1：已发送完可进行下次发送
    timeval currenttime;
    std::vector<int> alltime(0,0);   //记录全部的识别时刻的当前时间
    std::vector<int> all_delay_time(0,0); //记录经过计算的识别后的延迟到达步进电机的时间
    std::vector<int> all_send_time(0,0);  //记录延时启动发送步进程序的时间，送给定时器
    //存储全部数据容器
    std::vector<double> all_data_w(8,0);    //数量，x，y，x，y，精度，类别，识别间隔时间
    vector<vector<double>> all_data_array(0,all_data_w);
    //定时器发送控制命令
    CTimer *pTimer = new CTimer("定时器1");
//    connect(pTimer,&CTimer::taskrunover,this,&receive_data::sendsigal_slots);
    int timeover = 0; //延时计时一次结束，
    //3接受图像
//    useShare.pShareData->flag =1;
    while (1){
        //接受obtctrl数据
        usleep(1000);//防止绝对的空循环导致CPu占用，其他进程无法修改共享内存
        //接受obtctrl共享数据
        if (useShare.pShareData->obtctrl_flag == 1){
            gettimeofday(&currenttime,NULL);;
            Obtctrl_C[0]=useShare.pShareData->obtctrl[0]; //数量、xyxy，精度，类别
            Obtctrl_C[1]=useShare.pShareData->obtctrl[1];
            Obtctrl_C[2]=useShare.pShareData->obtctrl[2];
            Obtctrl_C[3]=useShare.pShareData->obtctrl[3];
            Obtctrl_C[4]=useShare.pShareData->obtctrl[4];
            Obtctrl_C[5]=useShare.pShareData->obtctrl[5];
            Obtctrl_C[6]=useShare.pShareData->obtctrl[6];
            useShare.pShareData->obtctrl_flag = 0; //允许存数据
            //循环存储数据
            for(int i=0;i<=6;i++){
                all_data_w[i] = Obtctrl_C[i];
                cout<<  "obtctrl"<<i <<"    "<<Obtctrl_C[i]  <<"    ";
            }
            cout<<endl;

            delay_time = sort_locat_time_comput_control(Obtctrl_C);
            int curtime = 1000*currenttime.tv_sec+(currenttime.tv_usec/1000); //当前系统时间（单位ms）
            alltime.push_back(curtime);
            all_delay_time.push_back(delay_time);
            //VVVVVVVVV延迟时间控制主程序：：VVVVVVVVVVVVVV
            //如果检测时间小于前一个目标到达分选时间，用时间差控制步进电机延迟
            if (tt>0)
            {
                if ((alltime[tt]+all_delay_time[tt])-(alltime[tt-1]+all_delay_time[tt-1]) <= all_delay_time[tt-1])
                {
                    all_data_w[7] = (alltime[tt]+all_delay_time[tt])-(alltime[tt-1]+all_delay_time[tt-1]);
                    all_send_time.push_back((alltime[tt]+all_delay_time[tt])-(alltime[tt-1]+all_delay_time[tt-1]));
                    cout<<"send_delaytime1:"<<(alltime[tt]+all_delay_time[tt])-(alltime[tt-1]+all_delay_time[tt-1])<<endl;
                }
                //如果检测时间大于前一个目标到达分选电机时间，用当前计算的延迟时间控制步进电机。
                else {
                    all_data_w[7] = all_delay_time[tt];
                    all_send_time.push_back(all_delay_time[tt]);
                    cout<<"send_delaytime2:"<<all_delay_time[tt]<<endl;
                }
            }
            else { //检测到首个目标的时间
                all_data_w[7] = all_delay_time[tt];
                all_send_time.push_back(all_delay_time[tt]);
                cout<<"send_delaytime0:"<<all_delay_time[tt]<<endl;
            }
            all_data_array.push_back(all_data_w);
            tt += 1;
//            cout<<alltime[0]<<";"<<alltime[1]<<";"<<curtime<<"delay_time:"<<delay_time<<endl;
        }
        //
        //准备启动延时函数。参数互锁，当执行完后，在执行下次延时函数。
        if (sendover_flag == 1 and ss<tt){ //启动异步延时。//传递指针
            sendover_flag = 0 ; //0未发送等待延时结束，send_stepper_signal运行完sendover_flag=1。

            int send_time = all_send_time[ss];
            int obj_class_src[1] = {(int)all_data_array[ss][6]};

            memcpy(obj_class,obj_class_src,sizeof (obj_class));
            cout<<"obj_class[0]"<<obj_class[0]<<endl;
            if (send_time>0){//当时间为负时，延时函数执行出错不执行
                pTimer->AsyncOnce(send_time,[](void *self, int *timeover) {
                    *timeover = 1;
                }, this, &timeover); //异步执行一次，间隔时间all_send_time[ss]毫秒
                cout<<send_time<<"ms后发送步进电机执行命令"<<endl;
            }
            else {
                sendover_flag = 1; //允许进行下次发送
            }
            ss +=1;
        }
        if (timeover == 1)
        {
            emit sendsigal(obj_class[0]);
            timeover = 0;    //计时结束复位；
        }
//        cout<< useShare.pShareData->obtctrl_flag<<endl;


//            //接受GPS
//            if( useShare.pShareData->flag ==1){

//                Gps_c[0]=useShare.pShareData->Gps[0];
//                Gps_c[1]=useShare.pShareData->Gps[1];
//                Gps_c[2]=useShare.pShareData->Gps[2];
//                Gps_c[3]=useShare.pShareData->Gps[3];

//                for(int i=0;i<=3;i++){cout<<  "GPS_DATA"<<i <<"    "<<Gps_c[i]  <<"    ";}
//                cout<<endl;
//            }

//            //接受图像
//            if( useShare.pShareData->flag ==1){//存储完毕，允许读图
//                useShare.Rec_pic2_data_once();//接受一张图像自动保存在useShare.cvoutImg中，然后修改标志位
//                RecImg=useShare.cvoutImg;
//                useShare.pShareData->flag =0;//读取完毕，允许存图

//            }
//            cv::namedWindow("RecData_Show", 0);
//            cv::imshow("RecData_Show",RecImg);

            if(read_share_flag == 1)
            {

                save_to_csv.saveArray(all_data_array,"/home/fuxiaoming/savealldata",6);
                useShare.pShareData->flag=3;
                cout <<"按键退出"<<endl;
                break;
            }
    }
//    RecImg.release();
//    cv::destroyWindow("RecData_Show");

//    //销毁
//    useShare.DestroyShare(); //销毁共享内存 类释放自动销毁

    return 0;
}

int receive_data::allow_python_loop()
{
    useShare.pShareData->stopflag=0;
    return useShare.pShareData->stopflag;
}
int receive_data::stop_python_loop()
{
    useShare.pShareData->stopflag=1;
    return useShare.pShareData->stopflag;
}

//void receive_data::sendsigal_slots(int sendclass)
//{
//    emit sendsigal(sendclass);
//    cout<<"emit了"<<endl;
//}
