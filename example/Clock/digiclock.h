#ifndef DIGICLOCK_H
#define DIGICLOCK_H

#include <QLCDNumber>
#include <QPoint>

class DigiClock : public QLCDNumber
{
    Q_OBJECT
public:
    DigiClock(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private slots:
    //显示当前时间
    void showTime();

private:
    //保存鼠标点相对电子时钟窗体左上角的偏移值
    QPoint dragPosition;
    //用于显示时间时是否显示“:”
    bool showColon;

};

#endif // DIGICLOCK_H
