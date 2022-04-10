#ifndef FUNCTION_DISCRIPTION_H
#define FUNCTION_DISCRIPTION_H

#include <QDialog>

namespace Ui {
class Function_Discription;
}

class Function_Discription : public QDialog
{
    Q_OBJECT

public:
    explicit Function_Discription(QWidget *parent = nullptr);
    ~Function_Discription();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Function_Discription *ui;
};

#endif // FUNCTION_DISCRIPTION_H
