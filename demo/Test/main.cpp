#include <QApplication>

#include "threadtest.h".h "

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    //注册容器类型
    qRegisterMetaType<QVector<int>>("QVector<int>");
    threadTest w;
    w.setWindowTitle("随机数");

    w.show();
    return a.exec();
}
