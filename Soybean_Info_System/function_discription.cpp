#include "function_discription.h"
#include "ui_function_discription.h"

Function_Discription::Function_Discription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Function_Discription)
{
    ui->setupUi(this);
    ui->textEdit->setDisabled(true);

}

Function_Discription::~Function_Discription()
{
    delete ui;
}

void Function_Discription::on_pushButton_2_clicked()
{
    close();
}
