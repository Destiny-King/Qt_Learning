//1、spinbox、sliderbox
//#include "mainwindow.h"
//2、创建对话框
#include "finddialog.h"

#include <QApplication>
#include <QSpinBox>
#include <QSlider>
#include <QSlider>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //1、spinbox、sliderbox
//    MainWindow w;
//    w.setWindowTitle("Enter your age:");
//    w.resize(800,600);

    FindDialog fd;
    fd.show();

    return a.exec();
}
