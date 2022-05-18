#include "paintarea.h"
#include <QPainter>

PaintArea::PaintArea(QWidget *parent) : QWidget(parent)
{
    //设置窗体背景色
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    setMinimumSize(400,400);
}

//设置形状
void PaintArea::setShape(Shape s)
{
    shape = s;
    update();
}

//设置画笔
void PaintArea::setPen(QPen p)
{
    pen = p;
    update();
}

//设置画刷
void PaintArea::setBrush(QBrush b)
{
    brush = b;
    update();
}

//设置填充模式
void PaintArea::setFillRule(Qt::FillRule rule)
{
    fillRule = rule;
    update();
}

//重画绘制区窗体
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setPen(pen);
    p.setBrush(brush);

    //设定一个方形区域
    QRect rect(50,100,300,200);

    //创建一个QPoint数组
    static const QPoint points[4] = {
        QPoint(150,100),
        QPoint(300,150),
        QPoint(350,250),
        QPoint(100,300)
    };

    //定义一个起始角
    int startAngle = 30 * 16;
    //定义一个跨度角
    int spanAngle = 120 * 16;

    QPainterPath path;
    path.addRect(150,150,100,100);
    path.moveTo(100,100);
    //绘制贝塞尔曲线
    path.cubicTo(300,100,200,200,300,300);
    path.cubicTo(100,300,200,200,100,100);
    path.setFillRule(fillRule);

    //对所画的形状做判断
    switch (shape) {
        //直线
        case Line:
            p.drawLine(rect.topLeft(),rect.bottomRight());
            break;
        //长方形
        case Rectangle:
            p.drawRect(rect);
            break;
        //圆角方形
        case RoundRect:
            p.drawRoundRect(rect);
            break;
        //椭圆形
        case Ellipse:
            p.drawEllipse(rect);
            break;
        //多边形
        case Polygon:
            p.drawPolygon(points,4);
            break;
        //多边线
        case Polyline:
            p.drawPolyline(points,4);
            break;
        //点
        case Points:
            p.drawPoints(points,4);
            break;
        //弧
        case Arc:
            p.drawArc(rect,startAngle,spanAngle);
            break;
        //路径
        case Path:
            p.drawPath(path);
            break;
        //文字
        case Text:
            p.drawText(rect,Qt::AlignCenter,tr("Hello Qt!"));
            break;
        //图片
        case Pixmap:
            p.drawPixmap(150,150,QPixmap(":/images/butterfly.png"));
            break;
    }
}
