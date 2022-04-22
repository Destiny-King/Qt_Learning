#include "frmimageswitch.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(16);
    a.setFont(font);

    frmImageSwitch w;
    w.setWindowTitle("图片背景开关");
    w.show();

    return a.exec();
}
