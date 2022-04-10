#ifndef HELP_DIALOG_H
#define HELP_DIALOG_H

#include <QDialog>

namespace Ui {
class help_Dialog;
}

class help_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit help_Dialog(QWidget *parent = nullptr);
    ~help_Dialog();

private slots:
    void on_quit_help_Btn_clicked();

private:
    Ui::help_Dialog *ui;
};

#endif // HELP_DIALOG_H
