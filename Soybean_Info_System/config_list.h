#ifndef CONFIG_LIST_H
#define CONFIG_LIST_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
//#include <QheaderView>

namespace Ui {
class Config_List;
}

class Config_List : public QDialog
{
    Q_OBJECT

public:
    explicit Config_List(QWidget *parent = nullptr);
    ~Config_List();

private slots:
    void createConfigTable();


private:
    Ui::Config_List *ui;
    QTableWidget *configList_tablet;

};

#endif // CONFIG_LIST_H
