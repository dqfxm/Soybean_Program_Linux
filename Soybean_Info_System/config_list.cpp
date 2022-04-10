#include "config_list.h"
#include "ui_config_list.h"
#include <QDebug>
#include <QHeaderView>

Config_List::Config_List(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config_List)
{
    ui->setupUi(this);

    createConfigTable();
}

Config_List::~Config_List()
{
    delete ui;
}

void Config_List::createConfigTable()
{
    qDebug()<<("运行configlist");
    configList_tablet = new QTableWidget(1000, 2,this);
    configList_tablet->setGeometry(50,50,400,300);
    configList_tablet->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
    QStringList labels;
    labels << tr("文件名") <<tr("创建时间");
    configList_tablet->setHorizontalHeaderLabels(labels);
    configList_tablet->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);//要包含头文件<QheaderView>
    configList_tablet->verticalHeader()->hide();
    configList_tablet->setShowGrid(false);                                                  //隐藏网格
    configList_tablet->setEditTriggers(QAbstractItemView::NoEditTriggers);                  //不可编辑
    configList_tablet->setStyleSheet("selection-background-color:rgb(150,190,60)");

}
