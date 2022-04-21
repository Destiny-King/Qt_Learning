#include "frmdevicesizetable.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    frmDeviceSizeTable w;
    w.setWindowTitle("磁盘容量");
    w.show();
    return a.exec();
}
