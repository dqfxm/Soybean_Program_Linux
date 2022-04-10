#include "Soybean_Info_System.h"

#include <QApplication>

// **********************************//
//程序名称：马铃薯智能清选系统控制平台
//版本号：v1.0Beta
//编写人：付晓明
//更新日期：20200916
//更新内容：图像采集模块
//版权信息：黑龙江八一农垦大学 工程学院
// *********************************//

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Soybean_Info_System w;
    w.show();

    return a.exec();
}
