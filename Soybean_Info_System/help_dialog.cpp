#include "help_dialog.h"
#include "ui_help_dialog.h"

help_Dialog::help_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help_Dialog)
{
    ui->setupUi(this);
}

help_Dialog::~help_Dialog()
{
    delete ui;
}

void help_Dialog::on_quit_help_Btn_clicked()
{
    close();  //关闭当前对话框
}
