#include "load_py_model.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <numpy/arrayobject.h>
#include <opencv2/imgproc.hpp>
#include <memory>
#include <QDebug>

using namespace std;
using namespace cv;


int load_detect()
{
    import_array();
    // 检查初始化是否成功
    if (!Py_IsInitialized()) {

        return -1;
    }
    qDebug() << "Python到这." << Qt::endl;
    // 添加当前路径
    //把输入的字符串作为Python代码直接运行，返回0
    //表示成功，-1表示有错。大多时候错误都是因为字符串
    //中有语法错误。
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("print('---import sys---')");
    PyRun_SimpleString("print(sys.path.append('/home/fuxiaoming/QT5_linux/QT_test/QT_test/yolov5-potato'))");
    //PyRun_SimpleString("import mydetect");

    PyObject *pModule = 0;
    PyObject *pFunction = 0;
    //    PyObject *pArgs = 0;
    PyObject *pRetValue = 0;

    pModule = PyImport_ImportModule("mydetect");
    if (!pModule)
        {
            qDebug() << "Python get module failed." << Qt::endl;
            return 0;
        }
        else
            qDebug() << "Python get module succeed!" << Qt::endl;

    //对应math_test.py中的def add_func(a,b)函数
    pFunction = PyObject_GetAttrString(pModule, "run_detect");
    if(pFunction == nullptr)
    {
        cout<<"Error: python pFunc_forward is null!"<<endl;
        return -1;
    }

//    //   C++ 代码传送参数给 python
//    PyObject *PyArray = &stop_detect_flag;
//    PyObject *argarray = PyTuple_New(1);
//    PyTuple_SetItem(argarray,0,pyarray);

    //调用函数
    pRetValue = PyObject_CallObject(pFunction,NULL); //pArgs 运行函数
    if(pRetValue == nullptr)
        {
            cout<<"Error: python pFunc_forward pRet is null!"<<endl;
            return -1;
        }
    qDebug()<<"pRetValue"<<pRetValue<<Qt::endl;


//  //qt5中调用，指针不能释放，释放会闪退
    Py_DECREF(pModule);

    Py_DECREF(pFunction);

//    Py_DECREF(pArgs);

    Py_DECREF(pRetValue);


//    delete [] data;
    Py_Finalize();
/*  system("pause");  //一般在windows平台写代码为了在终端看到运行结果，
    所以加入了system("pause");语句。但是在linux下shell里pause不再是一条命令，
    因此会出现sh: 1: pause: not found的提示。打开源文件删除system("pause");语句即可。*/
    return 0;
}


