#include "widget.h"
#include <QGridLayout>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //创建界面
    init_form();
    //参数初始化
    init_args();

    //5.连接信号和槽
    connect(bt_up,SIGNAL(clicked(bool)),this,SLOT(show_up()));
    connect(bt_down,SIGNAL(clicked(bool)),this,SLOT(show_down()));
    connect(bt_roll,SIGNAL(clicked(bool)),this,SLOT(show_roll()));
    connect(timer,SIGNAL(timeout()),this,SLOT(show_down()));
    connect(bt_getpicnames,&QPushButton::clicked,[&](){
        QStringList namex = QFileDialog::getOpenFileNames(this,"打开图片",".","Images(*.png *.jpg *.xpm)");
        names += namex;
        currentIndex = 0;
    });
}

Widget::~Widget()
{
}

void Widget::show_up()
{
    currentIndex--;
    if(currentIndex == -1)
        currentIndex = names.length() - 1;
    lb_pix->setPixmap(QPixmap(names[currentIndex]));
}

void Widget::show_down()
{
    currentIndex++;
    if(currentIndex == names.length())
        currentIndex = 0;
    lb_pix->setPixmap(QPixmap(names[currentIndex]));
}

void Widget::show_roll()
{
    static bool rollf = true;

    if(rollf){
        timer->start(1000);
        bt_roll->setText("停止");
    }else{
        timer->stop();
        bt_roll->setText("开始");
    }
    rollf = !rollf;
}

//2.构造所需控件
void Widget::init_form()
{
    lb_pix = new QLabel;
    lb_pix->setMinimumSize(640,480);
    //确定标签是否会缩放其内容以填充所有可用空间
    lb_pix->setScaledContents(true);

    bt_up = new QPushButton("上一张");
    bt_down = new QPushButton("下一张");
    bt_roll = new QPushButton("开始");
    bt_getpicnames = new QPushButton("选择图片");

    //3.排版
    QGridLayout *gbox = new QGridLayout;
    gbox->addWidget(lb_pix,0,0,1,5);
    gbox->addWidget(bt_getpicnames,1,0,1,1);
    gbox->addWidget(bt_up,1,1,1,1);
    gbox->addWidget(bt_roll,1,2,1,1);
    gbox->addWidget(bt_down,1,3,1,1);
    setLayout(gbox);
}

void Widget::init_args()
{
    currentIndex = 0;
    names.clear();
    names << ":/images/1.jpg" << ":/images/2.png" << ":/images/3.png";
    timer = new QTimer;
}

