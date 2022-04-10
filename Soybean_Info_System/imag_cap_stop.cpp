#include "imag_capture.h"
#include <QApplication>
#include "ui_potato_ai_system.h"

using namespace cv;
using namespace std;

k4a::device device;
k4a::capture capture;
cv::Mat color_frame;
cv::Mat depth_frame;
cv::Mat transformed_frame;
cv::Mat dst;

int imag_cap_stop(void)
{
    color_frame.release();
    depth_frame.release();
    dst.release();
    transformed_frame.release();
    capture.reset();
    cv::destroyAllWindows();
    device.close();
    return 0;
}
