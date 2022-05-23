#include "mainwindow.h"
#include <QApplication>
#include "connect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnect())
        return 1;
    MainWindow w;
    w.show();

    return a.exec();
}
