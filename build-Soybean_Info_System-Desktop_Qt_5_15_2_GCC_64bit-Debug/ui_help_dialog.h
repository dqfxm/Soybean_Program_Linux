/********************************************************************************
** Form generated from reading UI file 'help_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_DIALOG_H
#define UI_HELP_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_help_Dialog
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QGridLayout *gridLayout;
    QTextBrowser *Description_Browser;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *quit_help_Btn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *help_Dialog)
    {
        if (help_Dialog->objectName().isEmpty())
            help_Dialog->setObjectName(QString::fromUtf8("help_Dialog"));
        help_Dialog->resize(500, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(help_Dialog->sizePolicy().hasHeightForWidth());
        help_Dialog->setSizePolicy(sizePolicy);
        help_Dialog->setMinimumSize(QSize(500, 400));
        help_Dialog->setMaximumSize(QSize(500, 400));
        gridLayout_2 = new QGridLayout(help_Dialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Description_Browser = new QTextBrowser(help_Dialog);
        Description_Browser->setObjectName(QString::fromUtf8("Description_Browser"));
        Description_Browser->setFrameShape(QFrame::NoFrame);
        Description_Browser->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(Description_Browser, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        quit_help_Btn = new QPushButton(help_Dialog);
        quit_help_Btn->setObjectName(QString::fromUtf8("quit_help_Btn"));
        sizePolicy.setHeightForWidth(quit_help_Btn->sizePolicy().hasHeightForWidth());
        quit_help_Btn->setSizePolicy(sizePolicy);
        quit_help_Btn->setMinimumSize(QSize(100, 0));
        quit_help_Btn->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(quit_help_Btn);


        gridLayout->addLayout(horizontalLayout_5, 3, 0, 2, 1);


        gridLayout_2->addLayout(gridLayout, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(0, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 2, 1, 1);


        retranslateUi(help_Dialog);

        QMetaObject::connectSlotsByName(help_Dialog);
    } // setupUi

    void retranslateUi(QDialog *help_Dialog)
    {
        help_Dialog->setWindowTitle(QCoreApplication::translate("help_Dialog", "\345\205\263\344\272\216\346\234\254\347\250\213\345\272\217", nullptr));
        Description_Browser->setHtml(QCoreApplication::translate("help_Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\345\244\247\350\261\206\347\224\260\351\227\264\344\277\241\346\201\257\346\231\272\350\203\275\351\207\207\351\233\206\350\275\246\345\233\276\345\203\217\346\216\247\345\210\266\347\263\273\347\273\237</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">Soybean Info System</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px;"
                        " margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\345\275\223\345\211\215\347\211\210\346\234\254\357\274\232Version 3.0 Linux</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\350\277\220\350\241\214\347\216\257\345\242\203\357\274\232Windows10</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\347\211\210    \346\235\203\357\274\232copyright@\351\273\221\351\276\231\346\261\237\345\205\253\344\270\200\345\206\234\345\236\246\345\244\247\345\255\246</span></p>\n"
"<p"
                        " style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\346\233\264\346\226\260\350\257\264\346\230\216\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">20201101\346\234\254\347\211\210\346\234\254\345\237\272\344\272\216v1.0Beta\347\211\210\357\274\214\345\242\236\345\212\240\344\272\206\345\205\250\351\203\250\350\256\276\345\244\207\345\220\214\346\255\245\344\277\241\346\201\257\351\207\207\351\233\206\345\212\237\350\203\275\357\274\214\344\277\256\345\244\215\344\272\206\346\265\267\345\272\267MV-CE200-10UM\350\256\276\345\244\207\345\217\202\346\225\260\351\207\215\345\244\215\350\256\276\347\275\256\345\220\216\345\257\274\350\207\264\347\263\273\347\273\237\345\264\251\346\272\203\347\232\204\351\227\256\351\242\230\343\200\202</span><"
                        "/p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">20211130\347\211\210\346\234\2543.0Linux\347\211\210\346\234\254\357\274\232\346\224\257\346\214\2013\350\267\257KinectDK\350\256\276\345\244\207\350\277\236\346\216\245\347\232\204\345\233\276\345\203\217\350\207\252\345\212\250\351\207\207\351\233\206</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">20211221\347\211\210\346\234\2543.1Linux\347\211\210\346\234\254\357\274\232\345\242\236\345\212\240Kinect\345\210\206\350\276\250\347\216\207\350\256\276\347\275\256\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">20220102\347\211\210\346\234\254"
                        "3.2Linux\347\211\210\346\234\254: 1.\346\224\257\346\214\201\351\200\211\346\213\251Kinect\347\213\254\347\253\213\351\207\207\351\233\206RGB\344\270\216\345\220\214\346\255\245\351\207\207\351\233\206RGB-D\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">                                                   2.3\350\267\257RGB\343\200\2013\350\267\257Depth\345\220\214\346\255\245\347\252\227\345\217\243\350\276\223\345\207\272\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">20220402\347\211\210\346\234\2543.3Linux\347\211\210\346\234\254\357\274\214\346\224\257\346\214\2013\350\267\257HIK\347\233\270\346\234\272\345\220\214\346\255\245\351\207\207\351\233\206\357\274\214\345\220\214\346\227\266\346\224\257\346\214"
                        "\201GigE\345\222\214USB3\346\216\245\345\217\243\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\"> </span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\351\273\221\351\276\231\346\261\237\345\205\253\344\270\200\345\206\234\345\236\246\345\244\247\345\255\246  \344\273\230\346\231\223\346\230\216</span></p>\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\""
                        ">2022.04.02        </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p></body></html>", nullptr));
        quit_help_Btn->setText(QCoreApplication::translate("help_Dialog", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class help_Dialog: public Ui_help_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_DIALOG_H
