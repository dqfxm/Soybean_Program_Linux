#include "modify_csv_file.h"

//函数功能：把一个vector二维数组，存入CSV文件

//参数1：vector对象名；参数2：文件名；参数3：设置精度(默认精度是6)

modifyCSVfile::modifyCSVfile(){

}
modifyCSVfile::~modifyCSVfile(){

}

string modifyCSVfile::saveArray(const vector<vector<double>> &arr, string fileName, int precis)
{
    fileName += ".csv"; //保存成VSV格式文件，方便用Excel打开
    //保存数组到文件。如果文件不存在，创建文件，并写入数据；如果文件存在，清空重新写入
    ofstream fout;
    fout.open(fileName.c_str(), ios_base::trunc);
    fout << showpoint;
    fout.precision(precis);

    for (unsigned int i = 0; i < arr.size(); i++)
    {
        for (unsigned int j = 0; j < arr[i].size(); j++)
        {
            if (j < arr[i].size() - 1){
                fout << arr[i][j] << ",";
            }
            else{
                fout << arr[i][j] << endl;
            }
        }
    }
    fout.close();

    return fileName;
}
