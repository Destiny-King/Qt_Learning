#ifndef FRMDEVICEBUTTON_H
#define FRMDEVICEBUTTON_H

#include <QWidget>
#include "devicebutton.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class frmDeviceButton; }
QT_END_NAMESPACE

class frmDeviceButton : public QWidget
{
    Q_OBJECT

public:
    frmDeviceButton(QWidget *parent = 0);
    ~frmDeviceButton();

private slots:
    void initForm();
    void changeStyle();
    void changeColor();
    void on_ckCanMove_stateChanged(int arg1);

private:
    Ui::frmDeviceButton *ui;
    DeviceButton *btn1;
    DeviceButton *btn2;
    DeviceButton *btn3;
    QList<QPushButton *> btnStyle;
    QList<QPushButton *> btnColor;

};
#endif // FRMDEVICEBUTTON_H
