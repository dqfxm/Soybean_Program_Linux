#include "imag_capture.h"
#include <QApplication>
#include <QDebug>
#include <QDir>

using namespace cv;
using namespace std;

//imag_state:图像采集标志：1为开始采集，0为停止采集
//const string str1：图像保存地址和名称

int imag_capture(uint8_t Device_ID,Mat *rgb_data,Mat *depth_data)
{
    extern int imag_stop_flag;
    extern int kinect_auto_cap_state;
    extern std::string str_kinect_addr;
    extern int kinect_save_rgb_rgbd_flag;
    extern int kinect_dpi;

    imag_stop_flag = 0;          //kinect停止标记复位
    k4a::capture capture;
    k4a::image rgbImage;
    k4a::image depthImage;
    k4a::image transformed_depth_image = NULL;   //初始化
    k4a::calibration mycalibration;
    k4a::transformation transformation;
    uint8_t deviceID = K4A_DEVICE_DEFAULT;
//    clock_t time_start, time_end; //定义时间类型
    int fname_count = 0;  //文件名序号初始化

    //vector<Mat>::const_iterator n;   //vector类型 计数迭代标记
    //vector<Mat>::const_iterator m;

    cv::Mat color_frame;
    cv::Mat depth_frame;
    cv::Mat transformed_frame; //定义转换后图像的Mat对象
    cv::Mat rgbImage_no_alpha;
    cv::Mat color_frame_720p;   //实时显示的图像分辨率
    cv::Mat transformed_frame_720p;

    const uint32_t device_count = k4a::device::get_installed_count();//查看设备个数
    if (device_count == 0)
    {
        cout << "No K4A devices found" << endl;
        return 0;
    }
    cout << "K4A devices:"<<deviceID<<" have been found!" << endl;

    k4a::device device = k4a::device::open(Device_ID);
//    device_handle = &device;   //获取当前设备地址；

    k4a_device_configuration_t config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL; //初始化配置参数
    switch (kinect_dpi) //分辨率枚举
    {
        case 0:
            config.color_resolution = K4A_COLOR_RESOLUTION_720P;
            break;
        case 1:
            config.color_resolution = K4A_COLOR_RESOLUTION_1080P;
            break;
        case 2:
            config.color_resolution = K4A_COLOR_RESOLUTION_1440P;
            break;
        case 3:
            config.color_resolution = K4A_COLOR_RESOLUTION_2160P;
            break;
    }
    config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;
    config.depth_mode = K4A_DEPTH_MODE_WFOV_2X2BINNED;  //Depth captured at 640x576.Passive IR is also captured at 640x576.K4A_DEPTH_MODE_WFOV_2X2BINNED
    config.camera_fps = K4A_FRAMES_PER_SECOND_30;
    config.synchronized_images_only = true;

    mycalibration = device.get_calibration(config.depth_mode, config.color_resolution);
    transformation = k4a::transformation(mycalibration); //定义转换句柄
    device.start_cameras(&config);
    //time_start = clock();    //计时开始
    while (1)
    {
        if (imag_stop_flag == 1){
                    break;}
        if (device.get_capture(&capture)) //std::chrono::milliseconds(K4A_WAIT_INFINITE)
        {

            rgbImage = capture.get_color_image();
            depthImage = capture.get_depth_image();

            //以下把深度图像转换到彩色图像视角几何的方法，测试成功后写入函数中//
            //**********************************************************//
            int rgbimage_width_pixels = rgbImage.get_width_pixels();   //1280
            int rgbimage_height_pixels = rgbImage.get_height_pixels(); //720
            // int rgbimage_stride_bytes = rgbImage.get_stride_bytes();  // 4*1280=5120
            transformed_depth_image= k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16,
                                            rgbimage_width_pixels,
                                            rgbimage_height_pixels,
                                            rgbimage_width_pixels * (int)sizeof(uint16_t));

            transformation.depth_image_to_color_camera(depthImage, &transformed_depth_image); //深度转到彩色相机视角
            //*************************************************************//

            color_frame = cv::Mat(rgbImage.get_height_pixels(), rgbImage.get_width_pixels(), CV_8UC4, rgbImage.get_buffer());
            depth_frame = cv::Mat(depthImage.get_height_pixels(), depthImage.get_width_pixels(), CV_16U, depthImage.get_buffer());
            depth_frame.convertTo(depth_frame, CV_16U, 256);
//            cv::namedWindow("color_img_from_kinect_"+std::to_string(Device_ID),0);
//            cv::imshow("color_img_from_kinect_"+std::to_string(Device_ID), color_frame );
            transformed_frame = cv::Mat(transformed_depth_image.get_height_pixels(),
                                        transformed_depth_image.get_width_pixels(), CV_16U, transformed_depth_image.get_buffer());
            transformed_frame.convertTo(transformed_frame, CV_8U, 1);

            //以下为拆分cv::Mat类型图片的通道，并增加第四通道dchannel//
            Mat bimg, gimg, rimg;  //定义3个同样大小的图片存储单通道图片
            cv::Mat dst = cv::Mat(color_frame.rows, color_frame.cols, CV_8UC4);//定义了dst类型为4通道Mat类对象
            //cv::Mat save_depth = cv::Mat (depth_frame.rows,color_frame.cols,CV_16U); //定义深度16位图形存储单通道
            vector<Mat> bchannel, gchannel, rchannel, dchannel, src_channels; //定义了rgb-d4个通道和总通道，方便以下分别改变通道信息以输出不同通道图像。
            vector<Mat> dst_channels;  //定义最终的混合通道
            cv::split(color_frame,src_channels);  //把color_frame的通道数据复制到channals中

            dst_channels.push_back(src_channels[0]);
            dst_channels.push_back(src_channels[1]);
            dst_channels.push_back(src_channels[2]);  //把各通道分别增加到dst_channels目标通道中
            //增加深度通道
            dst_channels.push_back(transformed_frame);
            //dst_channels.push_back(depth_channel);//增加深度图像通道,depth_channel需要进一步创建
            //cout << dst_channels.size() << endl;   //输出dst_channels的大小，为4，因为输入了4组Mat类型数据;
            //三通道RGB图像
            cv::cvtColor(color_frame, rgbImage_no_alpha, cv::COLOR_BGRA2BGR);
            cv::resize(color_frame,color_frame_720p,cv::Size(1280,720));
            cv::resize(transformed_frame,transformed_frame_720p,cv::Size(1280,720));
            cv::merge(dst_channels, dst);
            //在主窗口显示，把图像数据复制到rgb_data
            cv::cvtColor(color_frame_720p,*rgb_data, cv::COLOR_BGRA2BGR);
//                cv::cvtColor(transformed_frame,depth_data,cv::COLOR_GRAY2BGR);
//                depth_data = transformed_frame;
            cv::applyColorMap(transformed_frame_720p,*depth_data, cv::COLORMAP_JET);

//                cv::imshow("rgbImage_no_alpha", rgbImage_no_alpha );

//                cv::imshow("depth_frame", depth_frame);
//                cv::imshow("trans_depth", transformed_frame);  //显示转换到彩色相机视角的深度图像
//                //*****向共享内存发送图像*****//
            Sleep(1);//防止绝对的空循环导致CPu占用，其他进程无法修改共享内存
//                if(useShare.pShareData->flag ==0){//读取完毕，允许存图
//                    //发送图像-C++和python模式
//                    useShare.pySend_pic2_share_once((uchar*)rgbImage_no_alpha.data,rgbImage_no_alpha.rows,rgbImage_no_alpha.cols);//发送一张图
//                    useShare.pShareData->flag =1;//存储完毕，允许读图
//    //                cout<<"+++++++++++++"<<fff++<<endl;
//                }
            //************************//

            //kinect图像定时保存模块
            if (kinect_auto_cap_state ==1)
            {
                if(kinect_save_rgb_rgbd_flag == 0) //采集rgb图像
                {
                    kinect_save_image(fname_count,rgbImage_no_alpha,str_kinect_addr,Device_ID);

                }
                if(kinect_save_rgb_rgbd_flag == 1) //采集rgbd图像
                {
                    kinect_save_image(fname_count,dst,str_kinect_addr,Device_ID);
                }
                fname_count++;
                kinect_auto_cap_state = 0;  //自动采集标记复原
            }
            //END

//            color_frame.release();
//            depth_frame.release();
//            transformed_frame.release();
          }
        else
        {
            cout << "false: K4A_WAIT_RESULT_TIMEOUT." << std::endl;
        }
    }

    cv::destroyAllWindows();
    color_frame.release();
    depth_frame.release();
    capture.reset();
    device.close();
    return 1;
}

int kinect_save_image(int fname_num,cv::Mat img_source,string str_kit_addr,uint8_t dev_id)
{
    //按顺序产生文件名
    const string str3 = ".png";
    const string str2 = to_string(fname_num); //转成字符串
    const string str_new = str_kit_addr+"/"+"Kinect_"+std::to_string(dev_id);
    //判断路径并新建文件夹
    if ((access(str_new.c_str(), 0)) != 0)
        {
            int status = mkdir(str_new.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
            qDebug() << "新建目录是否成功" << status;
        }
    const string str_m = str_new +"/"+ "kinect_" + str2;
    fstream imageFile;
    QString filename =QString::fromStdString(str_m+str3);
    //QString filename_in_program = QDir::fromNativeSeparators(filename); //路径格式转换
    imageFile.open(filename.toStdString(),ios::out);

    vector<int>compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    cv::imwrite(filename.toStdString(), img_source, compression_params);
    qDebug() << "自动保存kinectDK采集的图片一张" << Qt::endl;
    return 1;
}




