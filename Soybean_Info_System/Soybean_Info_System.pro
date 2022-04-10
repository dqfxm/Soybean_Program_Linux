QT       += core gui
QT       += serialport

RC_ICONS = soybeanico.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ApiShare_dll.cpp \
    CTimer.cpp \
    Soybean_Info_System.cpp \
    ThreadObject.cpp \
    call_python.cpp \
    config_list.cpp \
    delaysleep.cpp \
    function_discription.cpp \
    help_dialog.cpp \
    hik_gray_capture.cpp \
    imag_capture.cpp \
    kinect_init.cpp \
    load_py_model.cpp \
    main.cpp \
    modify_csv_file.cpp \
    my_switch.cpp \
    parameter_description.cpp \
    program_test.cpp \
    receive_data_from_share.cpp \
    send_example.cpp \
    serialport_init.cpp \
    serialport_open.cpp \
    serialport_send.cpp \
    serialthread.cpp \
    servo_common_control_R232.cpp \
    servo_speed_control_R232.cpp \
    sorting_control.cpp \
    stepmotor_control_R232.cpp \
    sub_serial_send.cpp \
    switchbutton.cpp \
    transfor_data.cpp

HEADERS += \
    ApiShare_dll.h \
    CTimer.hpp \
    CameraParams.h \
    ObsoleteCamParams.h \
    PixelType.h \
    Soybean_Info_System.h \
    ThreadObject.h \
    call_python.h \
    config_list.h \
    delaysleep.h \
    function_discription.h \
    help_dialog.h \
    hik_gray_capture.h \
    imag_capture.h \
    k4a.h \
    k4a.hpp \
    k4a_export.h \
    k4arecord_export.h \
    k4atypes.h \
    k4aversion.h \
    kinect_init.h \
    load_py_model.h \
    modify_csv_file.h \
    my_switch.h \
    parameter_description.h \
    playback.h \
    playback.hpp \
    program_test.h \
    receive_data_from_share.h \
    record.h \
    record.hpp \
    serialport_init.h \
    serialport_open.h \
    serialport_send.h \
    serialthread.h \
    servo_common_control_R232.h \
    servo_speed_control_R232.h \
    sorting_control.h \
    stepmotor_control_R232.h \
    sub_serial_send.h \
    switchbutton.h \
    transfor_data.h \
    types.h

FORMS += \
    Soybean_Info_System.ui \
    config_list.ui \
    function_discription.ui \
    help_dialog.ui \
    my_switch.ui \
    parameter_description.ui \
    program_test.ui

#添加第三方库和头文件
INCLUDEPATH += \
        /usr/local/include \
        /usr/local/include/opencv4 \
        /usr/include/k4a \
        /usr/include/k4arecord/

LIBS += \
        /usr/local/lib/libopencv_* \
        /usr/lib/x86_64-linux-gnu/libk4a.so \
        /usr/lib/x86_64-linux-gnu/libk4a1.4/libdepthengine.so.2.0 \
        -L/home/fuxiaoming/Programfile/Qt/5.15.2/gcc_64/lib \  #强制使用5.15最新qt库

#用于生成linux可执行应用程序文件
QMAKE_LFLAGS += -no-pie

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    soybean_res.qrc

##加入python库

unix:!macx: LIBS += -L$$PWD/../../../anaconda3/envs/pytorch_gpu/lib/ -lpython3.8
INCLUDEPATH += $$PWD/../../../anaconda3/envs/pytorch_gpu/include/python3.8
DEPENDPATH += $$PWD/../../../anaconda3/envs/pytorch_gpu/include/python3.8
INCLUDEPATH += $$PWD/../../../anaconda3/envs/pytorch_gpu/lib/python3.8/site-packages/numpy/core/include

##加入共享内存库（/QT_test/QT_test/ -lpython2share）
#unix:!macx: LIBS += -L$$PWD/../../QT_test/QT_test/ -lpython2share
#INCLUDEPATH += $$PWD/../../QT_test/QT_test
#DEPENDPATH += $$PWD/../../QT_test/QT_test
##加入海康MVS-SDK库
unix:!macx: LIBS += -L$$PWD/../../../../../opt/MVS/lib/64/ -lMVGigEVisionSDK
INCLUDEPATH += $$PWD/../../../../../opt/MVS/lib/64
DEPENDPATH += $$PWD/../../../../../opt/MVS/lib/64

unix:!macx: LIBS += -L$$PWD/../../../../../opt/MVS/lib/64/ -lMvCameraControl
INCLUDEPATH += $$PWD/../../../../../opt/MVS/include
DEPENDPATH += $$PWD/../../../../../opt/MVS/include
