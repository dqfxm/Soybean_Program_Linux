/********************************************************************************
** Form generated from reading UI file 'function_discription.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTION_DISCRIPTION_H
#define UI_FUNCTION_DISCRIPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Function_Discription
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Function_Discription)
    {
        if (Function_Discription->objectName().isEmpty())
            Function_Discription->setObjectName(QString::fromUtf8("Function_Discription"));
        Function_Discription->resize(500, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Function_Discription->sizePolicy().hasHeightForWidth());
        Function_Discription->setSizePolicy(sizePolicy);
        Function_Discription->setMinimumSize(QSize(500, 400));
        Function_Discription->setMaximumSize(QSize(500, 400));
        verticalLayout = new QVBoxLayout(Function_Discription);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(Function_Discription);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(textEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(Function_Discription);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Function_Discription);

        QMetaObject::connectSlotsByName(Function_Discription);
    } // setupUi

    void retranslateUi(QDialog *Function_Discription)
    {
        Function_Discription->setWindowTitle(QCoreApplication::translate("Function_Discription", "\345\212\237\350\203\275\344\273\213\347\273\215", nullptr));
        textEdit->setHtml(QCoreApplication::translate("Function_Discription", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; color:#000000;\">    \346\234\254\347\263\273\347\273\237\345\237\272\344\272\216KinectDK\346\267\261\345\272\246\347\233\270\346\234\272\345\222\214\346\265\267\345\272\267\345\250\201\350\247\206MV200\347\263\273\345\210\227\345\267\245\344\270\232\347\233\270\346\234\272\345\274\200\345\217\221\347\232\204\345\233\276\345\203\217\351\207\207\351\233\206\347\263\273\347\273\237\357\274\214\345\217\257\346\220\255\350\275\275\344\272\216\347\247\273\345\212\250\345\267\245\345\205\267\343\200\201\350\257\225\351\252\214\345\217"
                        "\260\343\200\201\345\256\232\347\202\271\344\275\215\347\275\256\347\232\204\345\233\276\345\203\217\351\207\207\351\233\206\345\222\214\350\256\276\345\244\207\347\232\204\344\274\272\346\234\215\347\263\273\347\273\237\346\216\247\345\210\266\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; color:#0000ff;\">1.\347\233\256\345\211\215\346\224\257\346\214\201\346\220\255\350\275\2752\344\270\252MV200\345\267\245\344\270\232\347\233\270\346\234\272\345\222\2143\344\270\252Kinect\346\267\261\345\272\246\347\233\270\346\234\272\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:"
                        "'SimSun'; color:#0000ff;\">2.\346\224\257\346\214\2014\351\200\232\351\201\223RGB-D\347\232\204PNG\346\240\274\345\274\217\345\255\230\345\202\250\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; color:#0000ff;\">3.\346\224\257\346\214\201\345\215\225\351\200\232\351\201\223Gray\347\232\204PNG\346\240\274\345\274\217\347\232\204\345\255\230\345\202\250\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; color:#0000ff;\">4.RGB-D\345\233\276\345\203\217\347\232\204\345\210\206\350\276\250\347\216\207\344\270\272\357\274\2321280\303\227800\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; color:#0000ff;\">5.Gray\345\233"
                        "\276\345\203\217\347\232\204\345\210\206\350\276\250\347\216\207\346\234\200\351\253\230\344\270\272\357\274\232\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; color:#0000ff;\">6.\346\224\257\346\214\201\344\270\216\344\274\272\346\234\215\351\251\261\345\212\250\345\231\250\347\232\204R232\344\270\262\345\217\243\351\200\232\344\277\241\346\216\247\345\210\266\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; color:#0000ff;\">7.\345\242\236\345\212\240\344\272\206\344\270\262\345\217\243\351\200\232\344\277\241\350\260\203\350\257\225\345\212\237\350\203\275\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Si"
                        "mSun';\"><br /></p></body></html>", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Function_Discription", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Function_Discription: public Ui_Function_Discription {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTION_DISCRIPTION_H
