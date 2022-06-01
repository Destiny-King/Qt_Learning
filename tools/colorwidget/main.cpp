#include <QApplication>

#include "frmcolorwidget.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    frmColorWidget w;
    w.setWindowTitle("屏幕取色器");  //设置标题
    w.show();
    return a.exec();
}
