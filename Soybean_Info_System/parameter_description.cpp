#include "parameter_description.h"
#include "ui_parameter_description.h"

Parameter_Description::Parameter_Description(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parameter_Description)
{
    ui->setupUi(this);
}

Parameter_Description::~Parameter_Description()
{
    delete ui;
}

void Parameter_Description::on_pushButton_clicked()
{
    close();
}
