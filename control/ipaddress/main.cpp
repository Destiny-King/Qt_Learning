#include "frmipaddress.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(16);
    a.setFont(font);

    frmIPAddress w;
    w.setWindowTitle("IP地址控件");
    w.show();

    return a.exec();
}
