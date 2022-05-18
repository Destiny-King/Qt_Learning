#include "digiclock.h"
#include <QTime>
#include <QTimer>
#include <QMouseEvent>

//设置外观及定时器的初始化工作
DigiClock::DigiClock(QWidget *parent) : QLCDNumber(parent)
{
    //设置时钟背景
    QPalette p = palette();
    p.setColor(QPalette::Window,Qt::blue);
    setPalette(p);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowOpacity(0.5);
    //定时器对象
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start(1000);
    //初始时间显示
    showTime();
    //设置电子时钟显示的尺寸
    resize(160,60);
    //初始化
    showColon = true;
}

void DigiClock::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if(event->button() == Qt::RightButton){
        close();
    }
}

void DigiClock::mouseMoveEvent(QMouseEvent *event)
{
   if(event->buttons()&Qt::LeftButton){
       move(event->globalPos() - dragPosition);
       event->accept();
   }
}

void DigiClock::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if(showColon){
        text[2] = ':';
        showColon = false;
    }else{
        text[2] = ' ';
        showColon = true;
    }
    display(text);
}
