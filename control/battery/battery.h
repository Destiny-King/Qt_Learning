#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>

class Battery : public QWidget
{
    Q_OBJECT
public:
    explicit Battery(QWidget *parent = 0);
    ~Battery();

protected:
    void paintEvent(QPaintEvent *);
    //绘制边框
    void drawBorder(QPainter *painter);
    //绘制背景
    void drawBg(QPainter *painter);
    //绘制头部
    void drawHead(QPainter *painter);

private slots:
    void updateValue();

private:
    //最小值
    double minValue;
    //最大值
    double maxValue;
    //目标电量
    double value;
    //电池电量警戒值
    double alarmValue;
    //每次移动的步长
    double step;

    //边框粗细
    int borderWidth;
    //边框圆角角度
    int borderRadius;
    //背景进度圆角角度
    int bgRadius;
    //头部圆角角度
    int headRadius;

    //边框渐变开始颜色
    QColor borderColorStart;
    //边框渐变结束颜色
    QColor borderColorEnd;

    //电池低电量时的渐变开始颜色
    QColor alarmColorStart;
    //电池低电量时的渐变结束颜色
    QColor alarmColorEnd;

    //电池正常电量时的渐变开始颜色
    QColor normalColorStart;
    //电池正常电量时的渐变结束颜色
    QColor normalColorEnd;

    //是否前移
    bool isForward;
    //当前电量
    double currentValue;
    //电池主体区域
    QRectF batteryRect;
    //绘制定时器
    QTimer *timer;

public slots:
    //设置电池电量值
    void setValue(int value);
    void setValue(double value);

signals:
    void valueChanged(double value);

};

#endif // BATTERY_H
