#include "frmbattery.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(16);
    a.setFont(font);

    frmBattery w;
    w.setWindowTitle("电池电量控件");
    w.show();
    return a.exec();
}
