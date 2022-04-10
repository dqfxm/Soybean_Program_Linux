#ifndef IMAG_CAP_STOP_H
#define IMAG_CAP_STOP_H

#include <QApplication>
#include "potato_ai_system.h"
#include "ui_potato_ai_system.h"

#include <stdio.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>
#include <cstdlib>
#include <k4arecord/record.h>
#include <k4arecord/playback.h>
#include <iostream>
#include <stdlib.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2\opencv.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>

#include <ctime>
#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <math.h>
#include <fstream>
#include <sstream>

extern k4a::device device;
extern k4a::capture capture;
extern cv::Mat color_frame;
extern cv::Mat depth_frame;
extern cv::Mat transformed_frame;
extern cv::Mat dst;

int imag_cap_stop(void);

#endif // IMAG_CAP_STOP_H
