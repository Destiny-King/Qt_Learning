#include "lightbutton.h"
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>

LightButton::LightButton(QWidget *parent) : QWidget(parent)
{
    text = "";
    textColor = QColor(255,255,255);                  //#ffffff   白色
    alarmColor = QColor(255,107,107);                 //#ff6b6b   淡红色
    normalColor = QColor(10,10,10);                   //#0a0a0a   黑色

    borderOutColorStart = QColor(255,255,255);
    borderOutColorEnd = QColor(166,166,166);          //#a6a6a6   淡灰色

    borderInColorStart = QColor(166,166,166);
    borderInColorEnd = QColor(255,255,255);

    bgColor = QColor(100,184,255);                    //#64b8ff   淡蓝色

    showRect = false;
    showOverlay = true;
    overlayColor = QColor(255,255,255);

    canMove = false;
    this->installEventFilter(this);

    isAlarm = false;
    timerAlarm = new QTimer(this);
    connect(timerAlarm,SIGNAL(timeout()),this,SLOT(alarm()));
    timerAlarm->setInterval(500);
}

bool LightButton::eventFilter(QObject *watched, QEvent *event)
{
    if(canMove){
        static QPoint lastPoint;
        static bool pressed = false;
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if(mouseEvent->type() == QEvent::MouseButtonPress){
            if(this->rect().contains(mouseEvent->pos()) && (mouseEvent->button() == Qt::LeftButton)){
                lastPoint = mouseEvent->pos();
                pressed = true;
            }
        }else if(mouseEvent->type() == QEvent::MouseMove && pressed){
            int dx = mouseEvent->pos().x() - lastPoint.x();
            int dy = mouseEvent->pos().y() - lastPoint.y();
            this->move(this->x() + dx,this->y() + dy);
        }else if(mouseEvent->type() == QEvent::MouseButtonRelease && pressed){
            pressed = false;
        }
    }
    return QWidget::eventFilter(watched,event);
}

void LightButton::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width,height);

    //绘制准备工作，启用反锯齿，平移坐标轴中心，等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if(showRect){
        //绘制矩形区域
        painter.setPen(Qt::NoPen);
        painter.setBrush(bgColor);
        //绘制带有圆角的矩形
        painter.drawRoundedRect(this->rect(),5,5);

        //绘制文字
        if(!text.isEmpty()){
            QFont font;
            //将字体大小设置为pixelSize像素
            font.setPixelSize(side - 20);
            painter.setFont(font);
            painter.setPen(textColor);
            painter.drawText(this->rect(),Qt::AlignCenter,text);
        }
    }else {
        //按给定偏移量平移坐标系
        painter.translate(width / 2,height / 2);
        //用(sx, sy)缩放坐标系
        painter.scale(side / 200.0, side / 200.0);

        //绘制外边框
        drawBorderOut(&painter);
        //绘制内边框
        drawBorderIn(&painter);
        //绘制内部指示颜色
        drawBg(&painter);
        //绘制居中文字
        drawText(&painter);
        //绘制遮罩层
        drawOverlay(&painter);
    }
}

void LightButton::drawBorderOut(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0,-radius,0,radius);
    borderGradient.setColorAt(0,borderOutColorStart);
    borderGradient.setColorAt(1,borderOutColorEnd);
    painter->setBrush(borderGradient);
    //绘制由给定矩形定义的椭圆
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightButton::drawBorderIn(QPainter *painter)
{
    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient borderGradient(0,-radius,0,radius);
    borderGradient.setColorAt(0,borderInColorStart);
    borderGradient.setColorAt(1,borderInColorEnd);
    painter->setBrush(borderGradient);
    //绘制由给定矩形定义的椭圆
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightButton::drawBg(QPainter *painter)
{
    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LightButton::drawText(QPainter *painter)
{
    if(text.isEmpty()){
        return;
    }
    int radius = 100;
    painter->save();

    QFont font;
    font.setPixelSize(85);
    painter->setFont(font);
    painter->setPen(textColor);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect,Qt::AlignCenter,text);
    painter->restore();
}

void LightButton::drawOverlay(QPainter *painter)
{
    if(!showOverlay){
        return;
    }

    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    //在指定的边界矩形内创建一个椭圆
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //高光的形状为小圆扣掉大圆部分
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0,0);
    //设置这个颜色的alpha值
    overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0,overlayColor);
    overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0,overlayColor);
    painter->setBrush(linearGradient);
    //顺时针旋转坐标系
    painter->rotate(-20);
    //使用当前笔绘制轮廓，使用当前笔刷绘制填充，绘制给定的画家路径
    painter->drawPath(highlight);

    painter->restore();
}

void LightButton::setBgColor(const QColor &bgColor)
{
    if(this->bgColor != bgColor){
        this->bgColor = bgColor;
        this->update();
    }
}

void LightButton::setLightGreen()
{
    textColor = QColor(255,255,255);
    setBgColor(QColor(24,189,155));
}

void LightButton::setLightRed()
{
    textColor = QColor(255,255,255);
    setBgColor(QColor(255,107,107));
}

void LightButton::setLightBlue()
{
    textColor = QColor(255, 255, 255);
    setBgColor(QColor(100, 184, 255));
}

void LightButton::alarm()
{
   if(isAlarm){
       textColor = QColor(255,255,255);
       bgColor = normalColor;
   } else{
       textColor = QColor(255,255,255);
       bgColor = alarmColor;
   }

   this->update();
   isAlarm = !isAlarm;
}
