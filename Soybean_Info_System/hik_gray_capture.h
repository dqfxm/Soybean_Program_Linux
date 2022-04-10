#ifndef HIT_GRAY_CAPTURE_H
#define HIT_GRAY_CAPTURE_H
//#pragma comment(lib, "MvCameraControl.lib")
//#pragma comment  (lib,"User32.lib")
//#pragma comment  (lib,"Gdi32.lib")

#include "MvCameraControl.h"
#include <QApplication>

#include <iostream>
#include <fstream>
#include <sstream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <assert.h>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>

#include "MvCameraControl.h"
#include "delaysleep.h"

using namespace std;
using namespace cv;

int camara_init_access(int Pixel_Width,int Pixel_Height,int Expoture_Time,int Gain_dB);
void* gray_capture_init(void* handle_gray,MV_CC_DEVICE_INFO* my_pDeviceInfo,int Pixel_Width,int Pixel_Height,int Expoture_Time,int Gain_dB);
int gray_capture(void* handle_gray,Mat *rgb_data,string camara_serial);
int gray_stop_capture(void* handle_gray);
int hik_save_image(int fname_num,cv::Mat img_source,string str_hik_addr);

#endif // HIT_GRAY_CAPTURE_H
