#include "widget.h"

#include <QApplication>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QResource::registerResource(PIC_RES_PATH);
    Widget w;
    w.show();
    return a.exec();
}
