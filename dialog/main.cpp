//1、spinbox、sliderbox
//#include "mainwindow.h"
//2、创建对话框
//#include "finddialog.h"
//3、GoToCell
#include "gotocelldialog.h"

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

    //2、创建对话框
//    FindDialog fd;
//    fd.setWindowTitle("对话框");
//    fd.show();

    //3、GoToCell
    GoToCellDialog dialog;
    dialog.show();

    return a.exec();
}
