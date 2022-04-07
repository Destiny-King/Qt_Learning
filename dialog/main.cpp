//1、spinbox、sliderbox
//#include "mainwindow.h"
//2、创建对话框
//#include "finddialog.h"
//3、GoToCell
//#include "gotocelldialog.h"
//4、SortDialog
//#include "sortdialog.h"
//5、SpreadSheet
#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
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
//    GoToCellDialog dialog;
//    dialog.setWindowTitle("GoToCell");
//    dialog.show();

    //4、SortDialog
//    SortDialog dialog;
//    dialog.setColumnRange('C','F');
//    dialog.show();
    //5、SpreadSheet
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/images/slash.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),topRight,Qt::white);
    MainWindow mainWin;
    splash->showMessage(QObject::tr("Loading modules..."),topRight,Qt::white);
//    loadModules;
    splash->showMessage(QObject::tr("Establishing connections..."),topRight,Qt::white);
//    establishConnections();
    mainWin.show();
    splash->finish(&mainWin);
    delete splash;

    return a.exec();
}
