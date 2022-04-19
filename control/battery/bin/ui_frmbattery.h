/********************************************************************************
** Form generated from reading UI file 'frmbattery.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMBATTERY_H
#define UI_FRMBATTERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "battery.h"

QT_BEGIN_NAMESPACE

class Ui_frmBattery
{
public:
    Battery *battery;
    QSlider *horizontalSlider;

    void setupUi(QWidget *frmBattery)
    {
        if (frmBattery->objectName().isEmpty())
            frmBattery->setObjectName(QString::fromUtf8("frmBattery"));
        frmBattery->resize(800, 600);
        battery = new Battery(frmBattery);
        battery->setObjectName(QString::fromUtf8("battery"));
        battery->setGeometry(QRect(20, 10, 500, 250));
        horizontalSlider = new QSlider(frmBattery);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 270, 500, 20));
        horizontalSlider->setOrientation(Qt::Horizontal);

        retranslateUi(frmBattery);

        QMetaObject::connectSlotsByName(frmBattery);
    } // setupUi

    void retranslateUi(QWidget *frmBattery)
    {
        frmBattery->setWindowTitle(QCoreApplication::translate("frmBattery", "frmBattery", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmBattery: public Ui_frmBattery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMBATTERY_H
