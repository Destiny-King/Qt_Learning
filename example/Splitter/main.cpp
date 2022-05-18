#include "mainwindow.h"

#include <QApplication>
#include <QSplitter>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //字体设置QFont类，第一个参数是字体族，第二个参数是字体尺寸，第三个是加粗系数，第四个是斜体设置。
    QFont font("ZYSong18030",12);
    a.setFont(font);
    //主分割窗口
    QSplitter *splitterMain = new QSplitter(Qt::Horizontal,0);
    QTextEdit *textLeft = new QTextEdit(QObject::tr("Left Widget"),splitterMain);
    //设置段落对齐方式
    textLeft->setAlignment(Qt::AlignCenter);
    //右部分割窗口
    QSplitter *splitterRight = new QSplitter(Qt::Vertical,splitterMain);
    splitterRight->setOpaqueResize(false);
    QTextEdit *textUp = new QTextEdit(QObject::tr("Top Widget"),splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    QTextEdit *textBottom = new QTextEdit(QObject::tr("Bottom Widget"),splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);
    //设置QSplitter类的伸缩因子
    splitterMain->setStretchFactor(1,1);
    splitterMain->setWindowTitle(QObject::tr("Splitter"));
    splitterMain->show();

//    MainWindow w;
//    w.show();
    return a.exec();
}
