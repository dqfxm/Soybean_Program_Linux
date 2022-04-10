#ifndef PROGRAM_TEST_H
#define PROGRAM_TEST_H

#include <QDialog>
#include <QSettings>
#include "modify_csv_file.h"
namespace Ui {
class Program_Test;
}

class Program_Test : public QDialog
{
    Q_OBJECT

public:
    explicit Program_Test(QWidget *parent = nullptr);
    ~Program_Test();

    void writeConfig(); //写配置文件
    void readConfig();  //读取配置文件
    void clearConfig(); //删除配置文件

private:
    QString Addr;

signals:
    void Send_Addr(QString Addr);

private slots:
    void on_OK_Btn_clicked();

    void on_Switch_to_back_Btn_clicked();

    void on_Switch_to_Slash_Btn_clicked();

    void on_Save_Conf_Btn_clicked();

    void on_Load__Conf_Btn_clicked();

    void on_time_out_Btn_clicked();

    void on_savefile_Btn_clicked();

    void on_hik_disp_Btn_clicked();

private:
    Ui::Program_Test *ui;
    QSettings *iniFile;
    modifyCSVfile savefile;

};

#endif // PROGRAM_TEST_H
