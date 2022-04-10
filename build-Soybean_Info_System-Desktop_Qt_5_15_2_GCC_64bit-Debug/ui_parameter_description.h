/********************************************************************************
** Form generated from reading UI file 'parameter_description.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETER_DESCRIPTION_H
#define UI_PARAMETER_DESCRIPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Parameter_Description
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *camera_tab;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *textBrowser;
    QWidget *capture_tab;
    QHBoxLayout *horizontalLayout_3;
    QTextBrowser *textBrowser_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *Parameter_Description)
    {
        if (Parameter_Description->objectName().isEmpty())
            Parameter_Description->setObjectName(QString::fromUtf8("Parameter_Description"));
        Parameter_Description->resize(500, 395);
        verticalLayout = new QVBoxLayout(Parameter_Description);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(Parameter_Description);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(85, 170, 255);"));
        camera_tab = new QWidget();
        camera_tab->setObjectName(QString::fromUtf8("camera_tab"));
        camera_tab->setLayoutDirection(Qt::RightToLeft);
        horizontalLayout_2 = new QHBoxLayout(camera_tab);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        textBrowser = new QTextBrowser(camera_tab);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(textBrowser);

        tabWidget->addTab(camera_tab, QString());
        capture_tab = new QWidget();
        capture_tab->setObjectName(QString::fromUtf8("capture_tab"));
        horizontalLayout_3 = new QHBoxLayout(capture_tab);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        textBrowser_2 = new QTextBrowser(capture_tab);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_3->addWidget(textBrowser_2);

        tabWidget->addTab(capture_tab, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(Parameter_Description);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(100, 0));
        pushButton->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Parameter_Description);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Parameter_Description);
    } // setupUi

    void retranslateUi(QDialog *Parameter_Description)
    {
        Parameter_Description->setWindowTitle(QCoreApplication::translate("Parameter_Description", "\345\217\202\346\225\260\350\256\276\347\275\256\350\257\264\346\230\216", nullptr));
#if QT_CONFIG(statustip)
        tabWidget->setStatusTip(QCoreApplication::translate("Parameter_Description", "\347\233\270\346\234\272\345\217\202\346\225\260", nullptr));
#endif // QT_CONFIG(statustip)
        textBrowser->setHtml(QCoreApplication::translate("Parameter_Description", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\344\270\200\343\200\201\345\203\217\347\264\240\350\256\276\347\275\256</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\344\273\216\347\233\270\346\234\272\345\235\220\346\240\2070\347\202\271\345\274\200\345\247\213\357\274\214\345\220\221X,Y\350\275\264\344\270\244\344\270\252\346\226\271\345\220\221\346\210\252\345\217\226\345\203\217\347\264\240\347\202\271\346\225\260"
                        "\357\274\214\346\232\202\346\227\266\346\262\241\346\234\211\345\242\236\345\212\240\350\260\203\350\212\202X,Y\350\275\264\345\201\217\347\275\256\350\260\203\350\212\202\345\212\237\350\203\275\357\274\233</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">1.</span><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:600;\">\345\203\217\347\264\240\345\256\275\345\272\246\357\274\232[128\357\274\2145472]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">2.</span><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:600;\">\345\203\217\347\264\240\351\253\230\345\272\246\357\274\232[128\357\274\2143648]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent"
                        ":0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">3.\346\234\200\345\244\247\345\210\206\350\276\250\347\216\207\344\270\272\357\274\2325472\303\2273648</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\344\272\214\343\200\201\346\233\235\345\205\211\350\256\276\347\275\256</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">1</span><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:600;\">.\346\233\235\345\205\211\346\227\266\351\227\264(us)\357\274\232[30,700000]</span></p>\n"
"<p style=\" margin-top:"
                        "0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">2.</span><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:600;\">\350\207\252\345\212\250\346\233\235\345\205\211\357\274\232</span><span style=\" font-family:'SimSun'; font-size:9pt;\">\344\270\215\347\224\250\346\211\213\345\212\250\350\256\276\347\275\256\357\274\214\350\256\276\345\244\207\350\207\252\345\212\250\350\260\203\350\212\202\346\233\235\345\205\211\346\227\266\351\227\264\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\345\220\210\347\220\206\350\256\276\347\275\256\346\233\235\345\205\211\346\227\266\351\227\264\346\233\235\345\205\211\346\227\266\351\227\264\350\277\207\345\244\247\344\274\232\345\257\274\350\207\264\347\247\273\345\212\250\346\213\226\345\275\261\343\200\202<"
                        "/span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\344\270\211\345\242\236\347\233\212</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:600;\">\345\242\236\347\233\212(dB)\357\274\232[0,20]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\345\217\257\346\240\271\346\215\256\345\256\236\351\231\205\347\216\257\345\242\203\350\260\203\350\212\202\345\242\236\347\233\212\357\274\214\345\242\236"
                        "\347\233\212\345\242\236\345\212\240\344\274\232\345\274\225\350\265\267\345\231\252\345\243\260\345\242\236\345\244\247\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\345\233\233\343\200\201\351\207\207\346\240\267\346\227\266\351\227\264</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:600;\">\351\207\207\346\240\267\346\227\266\351\227\264\344\270\215\350\246\201\345\260\217\344\272\216500ms</span><span style=\" font-family:'SimSun'; font-size:9pt;\">\357\274\214\345\220\246\345\210\231\345\217\257\350\203\275\345"
                        "\257\274\350\207\264\351\203\250\345\210\206\346\225\260\346\215\256\346\227\240\346\263\225\345\255\230\345\202\250\357\274\214\345\217\257\350\203\275\346\215\256\345\205\267\344\275\223\350\256\276\345\244\207\350\277\220\350\241\214\351\200\237\345\272\246\347\241\256\345\256\232\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(camera_tab), QCoreApplication::translate("Parameter_Description", "\347\233\270\346\234\272\345\217\202\346\225\260", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("Parameter_Description", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">KinectDK\350\256\276\345\244\207\347\232\204\345\217\202\346\225\260\345\267\262\347\273\217\345\206\205\347\275\256\345\234\250\347\250\213\345\272\217\344\270\255\357\274\214</span><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:600;\">\347\224\250\346\210\267\344\270\215\350\203\275\350\260\203\350\212\202</span><span style=\" font-family:'SimSun'; font-size:9pt;\">\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right"
                        ":0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">RGB\345\233\276\345\203\217\345\210\206\350\276\250\347\216\207\344\270\272\357\274\2321280\303\227800</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">Depth\351\200\232\351\201\223\345\233\276\345\203\217\345\210\206\350\276\250\347\216\207\357\274\2321280\303\227800</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; tex"
                        "t-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">\347\250\213\345\272\217\345\267\262\345\260\206RGB\345\222\214D\351\200\232\351\201\223\350\277\233\350\241\214\344\272\206\346\225\260\346\215\256\350\236\215\345\220\210\357\274\214\344\277\235\345\255\230\350\207\263PNG\346\240\274\345\274\217\345\233\276\347\211\207\346\226\207\344\273\266\344\270\255\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">PNG\347\232\204ALPHA\351\200\232\351\201\223\344\277\235\345\255\230\344\272"
                        "\206D\357\274\214\346\211\200\344\273\245\345\233\276\345\203\217\347\233\264\346\216\245\346\237\245\347\234\213\344\274\232\350\242\253ALPHA\351\200\232\351\201\223\350\246\206\347\233\226\343\200\202</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:600;\">\345\246\202\346\236\234\350\246\201\346\237\245\347\234\213\345\275\251\350\211\262\345\233\276\345\203\217\357\274\214\351\234\200\350\246\201\351\200\232\350\277\207\345\205\266\344\273\226\345\233\276\345\203\217\345\244\204\347\220\206\350\275\257\344\273\266\350\277\233\350\241\214\351\200\232\351\201\223\346\213\206\345\210\206\343\200\202</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(capture_tab), QCoreApplication::translate("Parameter_Description", "Kinect\345\217\202\346\225\260", nullptr));
        pushButton->setText(QCoreApplication::translate("Parameter_Description", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Parameter_Description: public Ui_Parameter_Description {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETER_DESCRIPTION_H
