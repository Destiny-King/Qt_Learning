#include "battery.h"
#include "qtimer.h"
#include "qpainter.h"

Battery::Battery(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    alarmValue = 30;
    step = 0.5;

    borderWidth = 5;
    borderRadius = 8;
    bgRadius = 5;
    headRadius = 3;

    //#646464
    borderColorStart = QColor(100,100,100);
    //#505050
    borderColorEnd = QColor(80,80,80);
    //#FA7671
    alarmColorStart = QColor(250,118,113);
    //#CC2626
    alarmColorEnd = QColor(204,38,38);
    //#32CD33
    normalColorStart = QColor(50,205,51);
    //#3CB385
    normalColorEnd = QColor(60,179,133);

    isForward = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);

    connect(timer,SIGNAL(timeout()),this,SLOT(updateValue()));

}

Battery::~Battery()
{
    if(timer->isActive()){
        timer->stop();
    }
}

void Battery::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制边框
    drawBorder(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制头部
    drawHead(&painter);
}

void Battery::drawBorder(QPainter *painter)
{
    painter->save();

    double headWidth = width() / 15;
    double batteryWidth = width() - headWidth;

    //绘制电池边框
    QPointF topLeft(borderWidth,borderWidth);
    QPointF bottomRight(batteryWidth,height() - borderWidth);
    batteryRect = QRectF(topLeft,bottomRight);

    painter->setPen(QPen(borderColorStart,borderWidth));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(batteryRect,borderRadius,borderRadius);

    painter->restore();
}

void Battery::drawBg(QPainter *painter)
{
    if(value == minValue)
        return;
    painter->save();

    QLinearGradient batteryGradient(QPointF(0,0),QPointF(0,height()));
    if(currentValue <= alarmValue){
        batteryGradient.setColorAt(0.0,alarmColorStart);
        batteryGradient.setColorAt(1.0,alarmColorEnd);
    }else{
        batteryGradient.setColorAt(0.0,normalColorStart);
        batteryGradient.setColorAt(1.0,normalColorEnd);
    }

    int margin = qMin(width(),height()) / 20;
    double unit = (batteryRect.width() - (margin * 2)) / 100;
    double width = currentValue * unit;

    QPointF topLeft(batteryRect.topLeft().x() + margin,batteryRect.topLeft().y() + margin);
    QPointF bottomRight(width + margin + borderWidth,batteryRect.bottomRight().y() - margin);
    QRectF rect(topLeft,bottomRight);

    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    painter->drawRoundedRect(rect,bgRadius,bgRadius);

    painter->restore();
}

void Battery::drawHead(QPainter *painter)
{
    painter->save();

    QPointF headRectTopLeft(batteryRect.topRight().x(),height() / 3);
    QPointF headRectBottonRight(width(),height() - height() / 3);
    QRectF headRect(headRectTopLeft,headRectBottonRight);

    QLinearGradient headRectGradient(headRect.topLeft(),headRect.bottomRight());
    headRectGradient.setColorAt(0.0,borderColorStart);
    headRectGradient.setColorAt(1.0,borderColorEnd);

    painter->setPen(Qt::NoPen);
    painter->setBrush(headRectGradient);
    painter->drawRoundedRect(headRect,headRadius,headRadius);

    painter->restore();
}

void Battery::updateValue()
{
   if(isForward){
       currentValue -= step;
       if(currentValue <= value){
           currentValue = value;
           timer->stop();
       }
   }else{
       currentValue += step;
       if(currentValue >= value){
           currentValue = value;
           timer->stop();
       }
   }

   this->update();
}

void Battery::setValue(int value)
{
        setValue((double)value);
}

void Battery::setValue(double value)
{
    //值和当前一致则无需处理
    if(value == this->value)
        return;
    //值小于最小值则取最小值，大于最大值则取最大值
    if(value < minValue){
        value = minValue;
    }else if(value > maxValue){
        value = maxValue;
    }

    if(value > currentValue){
        isForward = false;
    }else if(value < currentValue){
        isForward = true;
    }else{
        this->value = value;
        this->update();
        return;
    }
    this->value = value;
    this->update();
    emit valueChanged(value);
    timer->stop();
    timer->start();
}
