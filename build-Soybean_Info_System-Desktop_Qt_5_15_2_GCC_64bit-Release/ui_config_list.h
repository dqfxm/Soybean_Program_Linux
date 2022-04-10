/********************************************************************************
** Form generated from reading UI file 'config_list.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_LIST_H
#define UI_CONFIG_LIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_Config_List
{
public:

    void setupUi(QDialog *Config_List)
    {
        if (Config_List->objectName().isEmpty())
            Config_List->setObjectName(QString::fromUtf8("Config_List"));
        Config_List->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Config_List->sizePolicy().hasHeightForWidth());
        Config_List->setSizePolicy(sizePolicy);
        Config_List->setMinimumSize(QSize(600, 400));
        Config_List->setMaximumSize(QSize(600, 400));

        retranslateUi(Config_List);

        QMetaObject::connectSlotsByName(Config_List);
    } // setupUi

    void retranslateUi(QDialog *Config_List)
    {
        Config_List->setWindowTitle(QCoreApplication::translate("Config_List", "\351\205\215\347\275\256\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Config_List: public Ui_Config_List {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_LIST_H
