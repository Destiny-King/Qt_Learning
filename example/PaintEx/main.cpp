#include "mainwidget.h"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("ZYSong18030",16);
    a.setFont(font);
    MainWidget w;
    w.show();
    return a.exec();
}
