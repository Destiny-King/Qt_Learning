#ifndef LIGHTBUTTON_H
#define LIGHTBUTTON_H

#include <QWidget>

class LightButton : public QWidget
{
    Q_OBJECT
public:
    explicit LightButton(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *);
    void drawBorderOut(QPainter *painter);
    void drawBorderIn(QPainter *painter);
    void drawBg(QPainter *painter);
    void drawText(QPainter *painter);
    void drawOverlay(QPainter *painter);

private:
    QString text;                         //文本
    QColor textColor;                     //文字颜色
    QColor alarmColor;                    //报警颜色
    QColor normalColor;                   //正常颜色

    QColor borderOutColorStart;           //外边框渐变开始颜色
    QColor borderOutColorEnd;             //外边框渐变结束颜色
    QColor borderInColorStart;            //里边框渐变开始颜色
    QColor borderInColorEnd;              //里边框渐变结束颜色
    QColor bgColor;                       //背景颜色

    bool showRect;                        //显示成矩形
    bool canMove;                         //是否能够移动
    bool showOverlay;                     //是否显示遮罩层
    QColor overlayColor;                  //遮罩层颜色

    bool isAlarm;                         //是否报警
    QTimer *timerAlarm;                   //定时器切换颜色

signals:

public slots:
    //设置背景色
    void setBgColor(const QColor &bgColor);
    //设置淡绿色
    void setLightGreen();
    //设置淡红色
    void setLightRed();
    //设置淡蓝色
    void setLightBlue();

    //设置报警闪烁
    void alarm();

};

#endif // LIGHTBUTTON_H
