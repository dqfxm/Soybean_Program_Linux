#ifndef PARAMETER_DESCRIPTION_H
#define PARAMETER_DESCRIPTION_H

#include <QDialog>

namespace Ui {
class Parameter_Description;
}

class Parameter_Description : public QDialog
{
    Q_OBJECT

public:
    explicit Parameter_Description(QWidget *parent = nullptr);
    ~Parameter_Description();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Parameter_Description *ui;
};

#endif // PARAMETER_DESCRIPTION_H
