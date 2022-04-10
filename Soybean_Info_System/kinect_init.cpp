#include "kinect_init.h"

//extern k4a::device *global_kinect_handle_1;
//extern k4a::device *global_kinect_handle_2;
//extern k4a::device *global_kinect_handle_3;

extern uint8_t *deviceID;
extern string *serialnum;
int kinect_init()
{
    int k_num=0;
    const uint32_t device_count = k4a::device::get_installed_count();//查看>设备个数
    cout << device_count << endl;
    if (device_count == 0)
    {
        cout << "No K4A devices found" << endl;
        delete [] deviceID;
        deviceID = nullptr;
    }
    else{
        for (uint32_t i = 0; i < device_count; i++)
        {
            deviceID[i] = i;
            k_num+=1;
            cout << "K4A devices:"<<deviceID[i]<<" have been found!" << endl;
        }
    }
    if(k_num == 1){
        k4a::device device_1 = k4a::device::open(deviceID[0]);
        cout << "K4A ID_1:" << device_1.get_serialnum()<< endl;
        serialnum[0] = device_1.get_serialnum();
        device_1.close();
    }
    else if(k_num == 2){
        k4a::device device_1 = k4a::device::open(deviceID[0]);
        k4a::device device_2 = k4a::device::open(deviceID[1]);
        cout << "K4A ID_1:" << device_1.get_serialnum()<< endl;
        cout << "K4A ID_2:" << device_2.get_serialnum()<< endl;
        serialnum[0] = device_1.get_serialnum();
        serialnum[1] = device_2.get_serialnum();
        device_1.close();
        device_2.close();
    }
    else if (k_num == 3){
        k4a::device device_1 = k4a::device::open(deviceID[0]);
        k4a::device device_2 = k4a::device::open(deviceID[1]);
        k4a::device device_3 = k4a::device::open(deviceID[2]);
        cout << "K4A ID_1:" << device_1.get_serialnum()<< endl;
        cout << "K4A ID_2:" << device_2.get_serialnum()<< endl;
        cout << "K4A ID_3:" << device_3.get_serialnum()<< endl;
        serialnum[0] = device_1.get_serialnum();
        serialnum[1] = device_2.get_serialnum();
        serialnum[2] = device_3.get_serialnum();

        device_1.close();
        device_2.close();
        device_3.close();
    }
    else{
        cout << "kinect设备数量不能超过3个"<< endl;
    }
    cout << "Is K4A valid?:"<<endl;
    return 1;
}






