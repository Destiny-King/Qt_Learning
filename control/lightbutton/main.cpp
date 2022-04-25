#include "frmlightbutton.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(16);
    a.setFont(font);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    //设置编解码器
    QTextCodec::setCodecForLocale(codec);

    frmLightButton w;
    w.setWindowTitle("高亮发光按钮");
    w.show();

    return a.exec();
}
