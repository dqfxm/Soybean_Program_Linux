#ifndef MODIFY_CSV_FILE_H
#define MODIFY_CSV_FILE_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class modifyCSVfile
{
public:
    modifyCSVfile();
    ~modifyCSVfile();

private:

public:

    string saveArray(const vector<vector<double>> &arr, string fileName, int precis);

};


#endif // MODIFY_CSV_FILE_H
