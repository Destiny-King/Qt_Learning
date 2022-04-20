#ifndef DEVICEBUTTON_H
#define DEVICEBUTTON_H

#include <QWidget>
#include <QTimer>

class DeviceButton : public QWidget
{
    Q_OBJECT
public:
    //设备按钮样式
    enum ButtonStyle{
        ButtonStyle_Circle = 0,      //圆形
        ButtonStyle_Police = 1,      //警察
        ButtonStyle_Bubble = 2,      //气泡
        ButtonStyle_Bubble2 = 3,     //气泡2
        ButtonStyle_Msg = 4,         //消息
        ButtonStyle_Msg2 = 5,        //消息2
    };

    //设置按钮颜色
    enum ButtonColor{
        ButtonColor_Green = 0,       //绿色 激活状态
        ButtonColor_Blue = 1,        //蓝色 在线状态
        ButtonColor_Red = 2,         //红色 报警状态
        ButtonColor_Gray = 3,        //灰色 离线状态
        ButtonColor_Black = 4,       //黑色 故障状态
        ButtonColor_Purple = 5,      //紫色 其他状态
        ButtonColor_Yellow = 6,      //黄色 其他状态
    };

    explicit DeviceButton(QWidget *parent = 0);
    ~DeviceButton();

protected:
    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject *watched,QEvent *event);

private:
    bool canMove;                //是否可移动
    QString text;                //显示文字
    ButtonStyle buttonStyle;     //按钮样式
    ButtonColor buttonColor;     //按钮颜色

    QString type;                //图片末尾类型
    QString imgName;             //背景图片名称
    bool isDark;                 //是否加深报警
    QTimer *timer;               //报警闪烁定时器

private slots:
    //切换报警状态
    void checkAlarm();

public:
    bool getCanMove()              const;
    QString getText()              const;
    ButtonStyle getButtonStyle()   const;
    ButtonColor getButtonColor()   const;

    QSize sizeHint()               const;
    QSize minimumSizeHint()        const;

public slots:
    //设置可移动
    void setCanMove(bool canMove);
    //设置显示文字
    void setText(const QString &text);
    //设置样式
    void setButtonStyle(const ButtonStyle &buttonStyle);
    //设置颜色
    void setButtonColor(const ButtonColor &buttonColor);

signals:
    void clicked();
    void doubleClicked();

};

#endif // DEVICEBUTTON_H
