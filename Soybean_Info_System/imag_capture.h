#ifndef IMAG_CAPTURE_H
#define IMAG_CAPTURE_H

//#pragma comment(lib, "k4a.lib")
#include <QApplication>
//#include "Soybean_Info_System.h"
//#include "ui_Soybean_Info_System.h"

#include <stdio.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>
#include <cstdlib>
#include <k4arecord/record.h>
#include <k4arecord/playback.h>
#include <iostream>
#include <stdlib.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>

#include <vector>
#include <string>

#include <math.h>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include "delaysleep.h"


using namespace std;

int imag_capture(uint8_t Device_ID,cv::Mat *rgb_data,cv::Mat *depth_data);
int kinect_save_image(int fname_num,cv::Mat img_source,string str_kinect_addr,uint8_t dev_id);

#endif // IMAG_CAPTURE_H
