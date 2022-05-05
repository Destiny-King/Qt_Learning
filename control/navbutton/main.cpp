#include "frmnavbutton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmNavButton w;
    w.setWindowTitle("Suntor导航按钮控件");
    w.show();
    return a.exec();
}
