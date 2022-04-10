/********************************************************************************
** Form generated from reading UI file 'my_switch.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MY_SWITCH_H
#define UI_MY_SWITCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_my_switch
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QWidget *my_switch)
    {
        if (my_switch->objectName().isEmpty())
            my_switch->setObjectName(QString::fromUtf8("my_switch"));
        my_switch->resize(468, 289);
        horizontalLayoutWidget = new QWidget(my_switch);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(90, 70, 251, 101));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(my_switch);

        QMetaObject::connectSlotsByName(my_switch);
    } // setupUi

    void retranslateUi(QWidget *my_switch)
    {
        my_switch->setWindowTitle(QCoreApplication::translate("my_switch", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class my_switch: public Ui_my_switch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MY_SWITCH_H
