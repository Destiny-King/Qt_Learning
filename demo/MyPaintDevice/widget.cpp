#include "widget.h"
#include "ui_widget.h"
#include "QPixmap"
#include "QPainter"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

//    //pixmap绘画设备
//    QPixmap pix(300,300);

//    //填充颜色
//    pix.fill(Qt::white);
//    //声明画家
//    QPainter painter(&pix);
//    painter.setPen(Qt::green);
//    painter.drawEllipse(QPoint(150,150),100,100);

//    //保存
//    pix.save("E:\\Program\\CLion\\Qt\\MyPaintDevice\\pix.png");

    //QImage 绘图设备
//    QImage img(300,300,QImage::Format_RGB32);

//    img.fill(Qt::white);
//    QPainter painter(&img);
//    painter.setPen(Qt::blue);
//    painter.drawEllipse(QPoint(150,150),100,100);

//    img.save("E:\\Program\\CLion\\Qt\\MyPaintDevice\\img.png");

}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    QImage img();
    img.load(":/image/Luffy.jpeg");

    painter.drawImage(0,0,img);
}

Widget::~Widget()
{
    delete ui;
}
