#include "call_python.h"

using namespace std;
//把const char *c转 wchar_t * ，作为Py_SetPythonHome()参数匹配
 wchar_t *GetWC(const char *c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}


int call_python()
{

    //设定参数值
    int a = 0;
    int b = 6;
    //初始化(下面的方法可以在c:\APP\Anaconda3\include\pylifecycle.h中找到)
    Py_SetProgramName(0);
    //很关键的一步，去掉导入numpy报错
    Py_SetPythonHome(GetWC("/home/fuxiaoming/anaconda3/envs/pytorch_gpu"));

    Py_Initialize();
    // 检查初始化是否成功
    if (!Py_IsInitialized())
    {
        return -1;
    }

    //测试python3的打印语句
    PyRun_SimpleString("print('Hello Python!')\n");

    //执行import语句，把当前路径加入路径中，为了找到math_test.py
    PyRun_SimpleString("import os,sys");

    PyRun_SimpleString("sys.path.append('/home/fuxiaoming/QT5_linux/QT_test/QT_test')");
    //测试打印当前路径
    PyRun_SimpleString("print(os.getcwd())");

    PyObject *pModule = 0;

    PyObject *pFunction = 0;

    PyObject *pArgs = 0;

    PyObject *pRetValue = 0;
    //import math_test
//    PyRun_SimpleString("import calltest");
    pModule = PyImport_ImportModule("calltest");

    if (!pModule) {

        printf("import python failed!!\n");
        qDebug()<<"run in here"<<Qt::endl;
        return -1;

    }

    //对应math_test.py中的def add_func(a,b)函数
    pFunction = PyObject_GetAttrString(pModule, "add_func");

    if (!pFunction) {

        printf("get python function failed!!!\n");

        return -1;

    }

    //新建python中的tuple对象
    pArgs = PyTuple_New(2);

    PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", a));

    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", b));
    //调用函数
    pRetValue = PyObject_CallObject(pFunction, pArgs);
    //python3中只有long，PyLong_AsLong（python2中是PyInt_AsLong）
    printf("%d + %d = %ld\n", a, b, PyLong_AsLong(pRetValue));

    Py_DECREF(pModule);

    Py_DECREF(pFunction);

    Py_DECREF(pArgs);

    Py_DECREF(pRetValue);

    if (!pModule) {

        printf("import python failed!!\n");

        return -1;

    }
    //很关键的一步，如果是多次导入PyImport_ImportModule模块
    //只有最后一步才调用Py_Finalize()，此时python全局变量一直保存着
    // 反初始化
    //Py_Finalize();
    //方便查看

//    while (1);
//    qDebug()<<"初始化成功"<<Qt::endl;
    return PyLong_AsLong(pRetValue);

}

 /////////////以下调用python可用//////////////////////////
//{    // 初始化Python
//    //在使用Python系统前，必须使用Py_Initialize对其
//    //进行初始化。它会载入Python的内建模块并添加系统路
//    //径到模块搜索路径中。这个函数没有返回值，检查系统
//    //是否初始化成功需要使用Py_IsInitialized。
//    Py_Initialize();

//    // 检查初始化是否成功
//    if (!Py_IsInitialized()) {
//        return -1;
//    }
//    // 添加当前路径
//    //把输入的字符串作为Python代码直接运行，返回0
//    //表示成功，-1表示有错。大多时候错误都是因为字符串
//    //中有语法错误。
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("print('---import sys---')");
//    PyRun_SimpleString("print(sys.path.append('/home/fuxiaoming/QT5_linux/QT_test/QT_test'))");
//    PyRun_SimpleString("import calltest");
//    PyRun_SimpleString("calltest.add()");
//    Py_Finalize();
///*  system("pause");  //一般在windows平台写代码为了在终端看到运行结果，
//    所以加入了system("pause");语句。但是在linux下shell里pause不再是一条命令，
//    因此会出现sh: 1: pause: not found的提示。打开源文件删除system("pause");语句即可。*/
//    return 0;
//}
///////////////以上调用python可用///////////////


//    // 初始化Python
//    //在使用Python系统前，必须使用Py_Initialize对其
//    //进行初始化。它会载入Python的内建模块并添加系统路
//    //径到模块搜索路径中。这个函数没有返回值，检查系统
//    //是否初始化成功需要使用Py_IsInitialized。
//    Py_Initialize();

//    // 检查初始化是否成功
//    if ( !Py_IsInitialized() ) {
//        return -1;
//    }

//    // 添加当前路径。这里注意下面三句都不可少，
//    //添加的是当前路径。但是我打印了sys.path,
//    //出来了好多路径，有点类似环境变量路径的东西。这点不太懂怎么就成当前路径了
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("print ('---import sys---')");
//    //下面这个./表示当前工程的路径，如果使用../则为上级路径，根据此来设置
//    PyRun_SimpleString("print (sys.path.append('./'))");

//    PyObject *pName,*pModule,*pDict,*pFunc,*pArgs;

//    // 载入名为your_file的脚本
//    pName = PyUnicode_FromString("calltest");
//    pModule = PyImport_Import(pName);
//    if ( !pModule ) {
//        printf("can't find your_file.py");
//        getchar();
//        return -1;
//    }

//    pDict = PyModule_GetDict(pModule);
//    if ( !pDict ) {
//        return -1;
//    }
//    printf("----------------------\n");

//    // 找出函数名为display的函数
//    pFunc = PyDict_GetItemString(pDict, "display");
//    if ( !pFunc || !PyCallable_Check(pFunc) ) {
//        printf("can't find function [display]");
//        getchar();
//        return -1;
//     }

//    //将参数传进去。1代表一个参数。
//    pArgs = PyTuple_New(1);

//    //  PyObject* Py_BuildValue(char *format, ...)
//    //  把C++的变量转换成一个Python对象。当需要从
//    //  C++传递变量到Python时，就会使用这个函数。此函数
//    //  有点类似C的printf，但格式不同。常用的格式有
//    //  s 表示字符串，
//    //  i 表示整型变量，
//    //  f 表示浮点数，
//    //  O 表示一个Python对象。
//    //这里我要传的是字符串所以用s，注意字符串需要双引号！
//    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s"," python in C++"));
//    // 调用Python函数
//    PyObject_CallObject(pFunc, pArgs);

//    // 关闭Python
//    Py_Finalize();
//    return 0;



//int call_python(int argc, char *argv[])
//{
//    PyObject *pName, *pModule, *pFunc;
//    PyObject *pArgs, *pValue;
//    int i;

//    if (argc < 3) {
//        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
//        return 1;
//    }
//    //初始化
//    Py_Initialize();
//    // 指定py文件目录
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("sys.path.append('./')");

//    // 变量转换 模块名
//    pName = PyUnicode_FromString(argv[1]);
//    /* Error checking of pName left out */

//    // 根据模块名引入模块
//    pModule = PyImport_Import(pName);
//    Py_DECREF(pName);

//    if (pModule != NULL) {
//        // 从模块中获取函数
//        pFunc = PyObject_GetAttrString(pModule, argv[2]);
//        /* pFunc is a new reference */

//        if (pFunc && PyCallable_Check(pFunc)) {
//            // 创建参数元组
//            pArgs = PyTuple_New(argc - 3);
//            for (i = 0; i < argc - 3; ++i) {
//                pValue =   PyLong_FromLong(atoi(argv[i + 3]));
//                if (!pValue) {
//                    Py_DECREF(pArgs);
//                    Py_DECREF(pModule);
//                    fprintf(stderr, "Cannot convert argument\n");
//                    return 1;
//                }
//                // 设置参数值
//                /* pValue reference stolen here: */
//                PyTuple_SetItem(pArgs, i, pValue);
//            }
//            // 函数执行
//            pValue = PyObject_CallObject(pFunc, pArgs);
//            Py_DECREF(pArgs);
//            if (pValue != NULL) {
//                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
//                Py_DECREF(pValue);
//            }
//            else {
//                Py_DECREF(pFunc);
//                Py_DECREF(pModule);
//                PyErr_Print();
//                fprintf(stderr,"Call failed\n");
//                return 1;
//            }
//        }
//        else {
//            if (PyErr_Occurred())
//                PyErr_Print();
//            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
//        }
//        Py_XDECREF(pFunc);
//        Py_DECREF(pModule);
//    }
//    else {
//        PyErr_Print();
//        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
//        return 1;
//    }
//    // 反初始化
//    Py_Finalize();
//    return 0;


