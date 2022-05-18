#include "shapewidget.h"
#include <QPixmap>
#include <QBitmap>
#include <QMouseEvent>
#include <QPainter>

ShapeWidget::ShapeWidget(QWidget *parent)
    : QWidget(parent)
{
    QPixmap pix;
    pix.load(":/images/1.png",0,Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
    resize(pix.size());
    setMask(QBitmap(pix.mask()));
}

ShapeWidget::~ShapeWidget()
{
}

void ShapeWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if(event->button() == Qt::RightButton){
        close();
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent *event)
{
   if(event->buttons()&Qt::LeftButton){
       move(event->globalPos() - dragPosition);
       event->accept();
   }
}

void ShapeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,QPixmap(":/images/1.png"));
}

