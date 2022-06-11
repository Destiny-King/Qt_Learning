#include <QApplication>

#include "frmmain.h"
#include "jsonmain.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    frmMain w;
    JsonMain w1;
    w.show();
    w1.show();
    return a.exec();
}
