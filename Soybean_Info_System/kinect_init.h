#ifndef KINECT_INIT_H
#define KINECT_INIT_H

#include <stdio.h>
#include <k4a/k4a.h>
#include <k4a/k4a.hpp>
#include <cstdlib>
#include <k4arecord/record.h>
#include <k4arecord/playback.h>
#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <ctime>
#include <vector>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
//#include <direct.h>
#include <math.h>

using namespace std;
extern k4a::device device;
extern k4a::transformation transformation;

int kinect_init();

#endif // KINECT_INIT_H
