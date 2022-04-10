/********************************************************************************
** Form generated from reading UI file 'program_test.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAM_TEST_H
#define UI_PROGRAM_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Program_Test
{
public:
    QPushButton *OK_Btn;
    QPushButton *Switch_to_back_Btn;
    QPushButton *Switch_to_Slash_Btn;
    QTextEdit *File_addr_Browser;
    QPushButton *Save_Conf_Btn;
    QPushButton *Load__Conf_Btn;
    QPushButton *Delete_Conf_Btn;
    QLineEdit *CameraName_lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *UserName_lineEdit;
    QLabel *label_3;
    QCalendarWidget *calendarWidget;
    QLCDNumber *lcdNumber;
    QProgressBar *progressBar;
    QLabel *label_4;
    QFrame *line;
    QTimeEdit *timeEdit;
    QDateEdit *dateEdit;
    QDial *dial;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QCommandLinkButton *commandLinkButton;
    QGroupBox *groupBox;
    QRadioButton *radioButton;
    QCheckBox *checkBox;
    QToolBox *toolBox;
    QWidget *page;
    QWidget *page_2;
    QTreeWidget *treeWidget;
    QDialogButtonBox *buttonBox;
    QPushButton *savefile_Btn;
    QToolButton *toolButton;
    QPushButton *time_out_Btn;
    QPushButton *hik_disp_Btn;

    void setupUi(QDialog *Program_Test)
    {
        if (Program_Test->objectName().isEmpty())
            Program_Test->setObjectName(QString::fromUtf8("Program_Test"));
        Program_Test->resize(749, 560);
        OK_Btn = new QPushButton(Program_Test);
        OK_Btn->setObjectName(QString::fromUtf8("OK_Btn"));
        OK_Btn->setGeometry(QRect(60, 180, 241, 31));
        Switch_to_back_Btn = new QPushButton(Program_Test);
        Switch_to_back_Btn->setObjectName(QString::fromUtf8("Switch_to_back_Btn"));
        Switch_to_back_Btn->setGeometry(QRect(60, 220, 241, 31));
        Switch_to_Slash_Btn = new QPushButton(Program_Test);
        Switch_to_Slash_Btn->setObjectName(QString::fromUtf8("Switch_to_Slash_Btn"));
        Switch_to_Slash_Btn->setGeometry(QRect(60, 260, 241, 31));
        File_addr_Browser = new QTextEdit(Program_Test);
        File_addr_Browser->setObjectName(QString::fromUtf8("File_addr_Browser"));
        File_addr_Browser->setGeometry(QRect(60, 50, 341, 31));
        Save_Conf_Btn = new QPushButton(Program_Test);
        Save_Conf_Btn->setObjectName(QString::fromUtf8("Save_Conf_Btn"));
        Save_Conf_Btn->setGeometry(QRect(310, 180, 91, 31));
        Load__Conf_Btn = new QPushButton(Program_Test);
        Load__Conf_Btn->setObjectName(QString::fromUtf8("Load__Conf_Btn"));
        Load__Conf_Btn->setGeometry(QRect(310, 220, 91, 31));
        Delete_Conf_Btn = new QPushButton(Program_Test);
        Delete_Conf_Btn->setObjectName(QString::fromUtf8("Delete_Conf_Btn"));
        Delete_Conf_Btn->setGeometry(QRect(310, 260, 91, 31));
        CameraName_lineEdit = new QLineEdit(Program_Test);
        CameraName_lineEdit->setObjectName(QString::fromUtf8("CameraName_lineEdit"));
        CameraName_lineEdit->setGeometry(QRect(170, 90, 113, 31));
        label = new QLabel(Program_Test);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 100, 71, 16));
        label_2 = new QLabel(Program_Test);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 140, 71, 16));
        UserName_lineEdit = new QLineEdit(Program_Test);
        UserName_lineEdit->setObjectName(QString::fromUtf8("UserName_lineEdit"));
        UserName_lineEdit->setGeometry(QRect(170, 130, 113, 31));
        label_3 = new QLabel(Program_Test);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 10, 361, 16));
        calendarWidget = new QCalendarWidget(Program_Test);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(480, 20, 248, 197));
        lcdNumber = new QLCDNumber(Program_Test);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(650, 240, 64, 23));
        progressBar = new QProgressBar(Program_Test);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(110, 300, 118, 23));
        progressBar->setValue(24);
        label_4 = new QLabel(Program_Test);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 300, 51, 16));
        line = new QFrame(Program_Test);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(440, 10, 16, 321));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        timeEdit = new QTimeEdit(Program_Test);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setGeometry(QRect(480, 270, 118, 22));
        dateEdit = new QDateEdit(Program_Test);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(480, 240, 110, 22));
        dial = new QDial(Program_Test);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setGeometry(QRect(320, 300, 50, 64));
        dockWidget = new QDockWidget(Program_Test);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidget->setGeometry(QRect(60, 340, 201, 80));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        commandLinkButton = new QCommandLinkButton(dockWidgetContents);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(10, 10, 172, 41));
        dockWidget->setWidget(dockWidgetContents);
        groupBox = new QGroupBox(Program_Test);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(480, 300, 241, 151));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(50, 50, 89, 16));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(70, 80, 71, 16));
        toolBox = new QToolBox(groupBox);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setGeometry(QRect(160, 10, 69, 121));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 69, 59));
        toolBox->addItem(page, QString::fromUtf8("Page 1"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 69, 59));
        toolBox->addItem(page_2, QString::fromUtf8("Page 2"));
        treeWidget = new QTreeWidget(Program_Test);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(60, 430, 211, 81));
        buttonBox = new QDialogButtonBox(Program_Test);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(540, 510, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        savefile_Btn = new QPushButton(Program_Test);
        savefile_Btn->setObjectName(QString::fromUtf8("savefile_Btn"));
        savefile_Btn->setGeometry(QRect(300, 430, 131, 31));
        toolButton = new QToolButton(Program_Test);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(300, 130, 37, 31));
        time_out_Btn = new QPushButton(Program_Test);
        time_out_Btn->setObjectName(QString::fromUtf8("time_out_Btn"));
        time_out_Btn->setGeometry(QRect(300, 480, 131, 31));
        hik_disp_Btn = new QPushButton(Program_Test);
        hik_disp_Btn->setObjectName(QString::fromUtf8("hik_disp_Btn"));
        hik_disp_Btn->setGeometry(QRect(300, 370, 131, 41));

        retranslateUi(Program_Test);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Program_Test);
    } // setupUi

    void retranslateUi(QDialog *Program_Test)
    {
        Program_Test->setWindowTitle(QCoreApplication::translate("Program_Test", "\347\250\213\345\272\217\351\203\250\345\210\206\345\212\237\350\203\275\346\265\213\350\257\225", nullptr));
        OK_Btn->setText(QCoreApplication::translate("Program_Test", "Send Original ADDR to MainWindow", nullptr));
        Switch_to_back_Btn->setText(QCoreApplication::translate("Program_Test", "Switcth to Backslash ADDR", nullptr));
        Switch_to_Slash_Btn->setText(QCoreApplication::translate("Program_Test", "Switcth to Slash ADDR", nullptr));
        File_addr_Browser->setHtml(QCoreApplication::translate("Program_Test", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">D:/</span></p></body></html>", nullptr));
        Save_Conf_Btn->setText(QCoreApplication::translate("Program_Test", "Save Config", nullptr));
        Load__Conf_Btn->setText(QCoreApplication::translate("Program_Test", "Load Config", nullptr));
        Delete_Conf_Btn->setText(QCoreApplication::translate("Program_Test", "Delet Config", nullptr));
        CameraName_lineEdit->setText(QString());
        label->setText(QCoreApplication::translate("Program_Test", "CameraName:", nullptr));
        label_2->setText(QCoreApplication::translate("Program_Test", "User Name:", nullptr));
        UserName_lineEdit->setText(QString());
        label_3->setText(QCoreApplication::translate("Program_Test", "\346\234\254\351\241\265\344\270\272\351\203\250\345\210\206\345\212\237\350\203\275\346\265\213\350\257\225\351\241\265\357\274\214\350\257\267\345\277\275\347\225\245\357\274\214\345\220\216\346\234\237\351\235\236Beta\347\211\210\344\274\232\345\210\240\351\231\244\346\255\244\351\241\265\351\235\242\357\274\201", nullptr));
        label_4->setText(QCoreApplication::translate("Program_Test", "loading", nullptr));
        commandLinkButton->setText(QCoreApplication::translate("Program_Test", "CommandLinkButton", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Program_Test", "GroupBox", nullptr));
        radioButton->setText(QCoreApplication::translate("Program_Test", "RadioButton", nullptr));
        checkBox->setText(QCoreApplication::translate("Program_Test", "CheckBox", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QCoreApplication::translate("Program_Test", "Page 1", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QCoreApplication::translate("Program_Test", "Page 2", nullptr));
        savefile_Btn->setText(QCoreApplication::translate("Program_Test", "\344\277\235\345\255\230CSV\346\226\207\344\273\266", nullptr));
        toolButton->setText(QCoreApplication::translate("Program_Test", "...", nullptr));
        time_out_Btn->setText(QCoreApplication::translate("Program_Test", "\345\256\232\346\227\266\350\276\223\345\207\272", nullptr));
        hik_disp_Btn->setText(QCoreApplication::translate("Program_Test", "HIK\347\201\260\345\272\246\347\233\270\346\234\272\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Program_Test: public Ui_Program_Test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAM_TEST_H
