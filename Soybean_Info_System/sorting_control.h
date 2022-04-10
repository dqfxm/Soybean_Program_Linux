#ifndef SORTING_CONTROL_H
#define SORTING_CONTROL_H

#include <qdebug.h>
#include "CTimer.hpp"
#include "stepmotor_control_R232.h"


int sort_locat_time_comput_control(float * obj_data);
void send_stepper_signal(int *object_class);


#endif // SORTING_CONTROL_H
