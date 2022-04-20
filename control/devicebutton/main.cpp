#include "frmdevicebutton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(16);
    a.setFont(font);

    frmDeviceButton w;
    w.setWindowTitle("设备按钮控件");
    w.show();

    return a.exec();
}
