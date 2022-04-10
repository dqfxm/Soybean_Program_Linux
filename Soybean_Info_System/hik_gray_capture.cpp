#include "hik_gray_capture.h"

#include <QApplication>
#include <QtDebug>
#include <QDir>

extern void* handle1;
extern void* handle2;
extern void* handle3;

extern int gray_stop_flag;
extern void *global_handle_1;
extern void *global_handle_2;
extern void *global_handle_3;
extern bool exposure_auto_set;

extern std::string str_gray_addr; //Gray冠层图片采集路径-全局
extern int gray_auto_cap_state; //gray图像自动采集状态标记
extern int gray_manul_cap_state; //gray图像手动采集状态标记


bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
    if (NULL == pstMVDevInfo)
    {
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

        // print current ip and user defined name
        printf("CurrentIp: %d.%d.%d.%d\n" , nIp1, nIp2, nIp3, nIp4);
        printf("UserDefinedName: %s\n\n" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {
        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
        printf("Device Number: %d\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.nDeviceNumber);
    }
    else
    {
        printf("Not support.\n");
    }

    return true;
}


int camara_init_access(int Pixel_Width,int Pixel_Height,int Expoture_Time,int Gain_dB)
{
    int nRet = MV_OK;

    // Enum device
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
    if (MV_OK != nRet)
    {
        printf("Enum Devices fail! nRet [0x%x]\n", nRet);
        return 0;

    }

    if (stDeviceList.nDeviceNum > 0)
    {
        for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
        {
            printf("[device %d]:\n", i);
            MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
            if (NULL == pDeviceInfo)
            {
                return 0;
            }
            PrintDeviceInfo(pDeviceInfo);
        }
    }
    else
    {
        printf("Find No Devices!\n");
        return 0;
    }

    // Select device and create handle
    switch (stDeviceList.nDeviceNum)
    {
    case 1:
        nRet = MV_CC_CreateHandle(&handle1, stDeviceList.pDeviceInfo[0]);
        if (MV_OK != nRet)
        {
            printf("Create Handle fail! nRet [0x%x]\n", nRet);
            return 0;
        }
        global_handle_1 = gray_capture_init(handle1, stDeviceList.pDeviceInfo[0], Pixel_Width, Pixel_Height, Expoture_Time, Gain_dB); //初始化camara1参数
        return 1;
        break;
    case 2:
        nRet = MV_CC_CreateHandle(&handle1, stDeviceList.pDeviceInfo[0]);
        if (MV_OK != nRet)
        {
            printf("Create Handle fail! nRet [0x%x]\n", nRet);
            return 0;
        }
        global_handle_1 = gray_capture_init(handle1, stDeviceList.pDeviceInfo[0], Pixel_Width, Pixel_Height, Expoture_Time, Gain_dB); //初始化camara1参数
        nRet = MV_CC_CreateHandle(&handle2, stDeviceList.pDeviceInfo[1]);
        if (MV_OK != nRet)
        {
            printf("Create Handle fail! nRet [0x%x]\n", nRet);
            return 0;
        }
        global_handle_2 = gray_capture_init(handle2, stDeviceList.pDeviceInfo[1], Pixel_Width, Pixel_Height, Expoture_Time, Gain_dB); //初始化camara2参数
        return 2;
        break;
    case 3:
        nRet = MV_CC_CreateHandle(&handle1, stDeviceList.pDeviceInfo[0]);
        if (MV_OK != nRet)
        {
            printf("Create Handle fail! nRet [0x%x]\n", nRet);
            return 0;
        }
        global_handle_1 = gray_capture_init(handle1, stDeviceList.pDeviceInfo[0], Pixel_Width, Pixel_Height, Expoture_Time, Gain_dB); //初始化camara1参数
        nRet = MV_CC_CreateHandle(&handle2, stDeviceList.pDeviceInfo[1]);
        if (MV_OK != nRet)
        {
            printf("Create Handle fail! nRet [0x%x]\n", nRet);
            return 0;
        }
        global_handle_2 = gray_capture_init(handle2, stDeviceList.pDeviceInfo[1], Pixel_Width, Pixel_Height, Expoture_Time, Gain_dB); //初始化camara2参数

        nRet = MV_CC_CreateHandle(&handle3, stDeviceList.pDeviceInfo[2]);
        if (MV_OK != nRet)
        {
            printf("Create Handle fail! nRet [0x%x]\n", nRet);
            return 0;
        }
        global_handle_3 = gray_capture_init(handle3, stDeviceList.pDeviceInfo[2], Pixel_Width, Pixel_Height, Expoture_Time, Gain_dB); //初始化camara3参数
        return 3;
        break;
    default:
        printf("Create Handle fail! nRet [0x%x]\n", nRet);return 0;
    }
    return stDeviceList.nDeviceNum;
}

void* gray_capture_init(void* handle_gray,MV_CC_DEVICE_INFO* my_pDeviceInfo,int Pixel_Width,int Pixel_Height,int Expoture_Time,int Gain_dB)
{
    int nRet = MV_OK;
    MVCC_FLOATVALUE  pstFloatValue;
    // Open device
    nRet = MV_CC_OpenDevice(handle_gray);
    if (MV_OK != nRet)
    {
        printf("Open Device fail! nRet [0x%x]\n", nRet);
//        return 1;
    }
    // ch:探测网络最佳包大小(只对GigE相机有效) |en: Detection network optimal package size(It only works for the GigE camera)
    if (my_pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nPacketSize = MV_CC_GetOptimalPacketSize(handle_gray);
        cout<<"GigE相机最佳数据包大小nPacketSize"<<nPacketSize<<endl;
        if (nPacketSize > 0)
        {
            nRet = MV_CC_SetIntValue(handle_gray,"GevSCPSPacketSize",nPacketSize);
            if(nRet != MV_OK)
            {
                printf("Warning: Set Packet Size fail nRet [0x%x]!", nRet);
            }
        }
        else
        {
            printf("Warning: Get Packet Size fail nRet [0x%x]!", nPacketSize);
        }
    }

    // Set trigger mode as off
    nRet = MV_CC_SetEnumValue(handle_gray, "TriggerMode", 0);
    if (MV_OK != nRet)
    {
        printf("Set Trigger Mode fail! nRet [0x%x]\n", nRet);
//        return 1;
    }
    //设置像素大小


    MV_CC_SetIntValueEx(handle_gray, "Width", Pixel_Width);    //"Width Max", 5472,/8=684
    MV_CC_SetIntValueEx(handle_gray, "Height", Pixel_Height);   //"Height Max", 3648,/8=456

    //设置曝光时间,判断是否为自动曝光模式
    MVCC_ENUMVALUE exposure_state;

    nRet = MV_CC_SetEnumValueByString(handle_gray,"ExposureMode","Timed");  //Sets the operation mode of the Exposure (or shutter).
    MV_CC_GetEnumValue(handle_gray,"ExposureAuto",&exposure_state);
    int expose_state_int = (int)exposure_state.nCurValue;
    cout<<"expose_state_int:"<<expose_state_int<<endl;
    if (exposure_auto_set)
    {
        if(expose_state_int == 0)
        {
            nRet = MV_CC_SetEnumValueByString(handle_gray,"ExposureAuto","Continuous");  //自动曝光模式打开
            if(MV_OK != nRet)
            {
                qDebug()<<"自动曝光设置失败";
            }
        }
    }
    else
    {
        if(expose_state_int != 0)
        {
            nRet = MV_CC_SetEnumValueByString(handle_gray,"ExposureAuto","Off");  //自动曝光模式关闭
            qDebug()<<"自动曝光关闭";
            if(MV_OK != nRet)
            {
                qDebug()<<"自动曝光设置失败";
            }
        }
        nRet = MV_CC_SetFloatValue(handle_gray,"ExposureTime", Expoture_Time);  //手动曝光模式
    }

    nRet = MV_CC_GetFloatValue(handle_gray, "ExposureTime", &pstFloatValue);
    float ExposureTime = (float)pstFloatValue.fCurValue;
    qDebug() << "当前ExposureTime值：" << ExposureTime;

    nRet = MV_CC_SetFloatValue(handle_gray, "Gain", Gain_dB);
    nRet = MV_CC_GetFloatValue(handle_gray, "Gain", &pstFloatValue);
    float Gain = (float)pstFloatValue.fCurValue;
    qDebug() << "当前增益值：" << Gain;

    return handle_gray;
}


int gray_capture(void* handle_gray,Mat *rgb_data,string camara_serial)
{
    gray_stop_flag = 0;
    //cv::Mat pImg_720p;
    int fname_count = 0;  //文件名序号初始化
    int fname_manul_count = 0;  //手动保存文件序号初始化


    int nRet = MV_OK;
    MV_FRAME_OUT stImageInfo;
    //MV_DISPLAY_FRAME_INFO stDisplayInfo = {0};
    // Start grab image
    nRet = MV_CC_StartGrabbing(handle_gray);
    if (MV_OK != nRet)
    {
        printf("Start Grabbing fail! nRet [0x%x]\n", nRet);
     //   break;
    }
    while(1)
    {
        nRet = MV_CC_GetImageBuffer(handle_gray, &stImageInfo, 5000);
        if (nRet == MV_OK)
        {
//            printf("Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",
//            stImageInfo.stFrameInfo.nWidth, stImageInfo.stFrameInfo.nHeight, stImageInfo.stFrameInfo.nFrameNum);

            int width = stImageInfo.stFrameInfo.nWidth;
            int height = stImageInfo.stFrameInfo.nHeight;
            /*if (stImageInfo.stFrameInfo.enPixelType == PixelType_Gvsp_BGR8_Packed)
            {*/
            cv::Mat pImg(height, width, CV_8UC1, stImageInfo.pBufAddr);
            //实际显示分辨率1280，720
            cv::resize(pImg,*rgb_data,cv::Size(1280,720));

            Sleep(1); //延迟1毫秒
            //图像自动保存控制模块
             if (gray_auto_cap_state == 1)
            {
                fname_count++;
                //按顺序产生文件名
                const string str_m = str_gray_addr + "/"+"Auto_"+camara_serial;
                hik_save_image(fname_count, pImg,str_m);
                cout << "自动保存gray_camara_"<<camara_serial<<"采集的图片一张" << endl;
                gray_auto_cap_state = 0; //自动采集标记复原
            }
            //END
            //图像手动保存一张图片控制模块
            if (gray_manul_cap_state == 1)
            {
                fname_manul_count++;
                //按顺序产生文件名
                const string str_m = str_gray_addr + "/" + "Manul_"+camara_serial;
                hik_save_image(fname_manul_count, pImg,str_m);

                cout << "手动保存gray_camara_"<<camara_serial<<"采集的图片一张" << endl;
                gray_manul_cap_state = 0; //手动采集标记复原
            }
            //END
            //cv::imshow(windowname, pImg);

            nRet = MV_CC_FreeImageBuffer(handle_gray, &stImageInfo);
            if(nRet != MV_OK)
            {
                printf("Free Image Buffer fail! nRet [0x%x]\n", nRet);
            }
        }
        else
        {
            printf("No data[0x%x]\n", nRet);

            return 0;
        }
        if(gray_stop_flag == 1)
        {
            break;
        }
    }
    printf("Press a key to stop grabbing.\n");
    return 1;
}

//停止灰度图像获取
int gray_stop_capture(void* handle_gray)
{
    int nRet = MV_OK;
    // Stop grab image
    nRet = MV_CC_StopGrabbing(handle_gray);
    if (MV_OK != nRet)
    {
        printf("Stop Grabbing fail! nRet [0x%x]\n", nRet);
     //   break;
    }

    // Close device
    nRet = MV_CC_CloseDevice(handle_gray);
    if (MV_OK != nRet)
    {
        printf("ClosDevice fail! nRet [0x%x]\n", nRet);
     //   break;
    }

    // Destroy handle
    nRet = MV_CC_DestroyHandle(handle_gray);
    if (MV_OK != nRet)
    {
        printf("Destroy Handle fail! nRet [0x%x]\n", nRet);
     //   break;
    }


    if (nRet != MV_OK)
    {
        if (handle_gray != NULL)
        {
            MV_CC_DestroyHandle(handle_gray);
            handle_gray = NULL;
        }
    }

    printf("Press a key to exit.\n");
    //WaitForKeyPress();

    return 0;
}


int hik_save_image(int fname_num,cv::Mat img_source,string str_hik_addr)
{
    //按顺序产生文件名
    const string str3 = ".png";
    const string str2 = to_string(fname_num); //转成字符串
    const string str_new = str_hik_addr;
    //判断路径并新建文件夹
    if ((access(str_new.c_str(), 0)) != 0)
        {
            int status = mkdir(str_new.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
            qDebug() << "新建目录是否成功" << status;
        }
    const string str_m = str_new +"/"+ "Hik_" + str2;
    fstream imageFile;
    QString filename =QString::fromStdString(str_m+str3);
    //QString filename_in_program = QDir::fromNativeSeparators(filename); //路径格式转换
    imageFile.open(filename.toStdString(),ios::out);

    vector<int>compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);
    cv::imwrite(filename.toStdString(), img_source, compression_params);
    return 1;
}
