#ifndef WIDGET_H
#define WIDGET_H

#define PIC_RES_PATH "./res.rcc"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    //显示上一页
    void show_up();
    //显示下一页
    void show_down();
    //滚动显示
    void show_roll();


private:
    //1.申明所需元素
    QLabel *lb_pix;
    QPushButton *bt_up;
    QPushButton *bt_down;
    QPushButton *bt_roll;
    QPushButton *bt_getpicnames;

    //成员函数
    void init_form();
    void init_args();

    //成员变量
    QTimer *timer;
    //用于存放图片路径
    QStringList names;
    //标识当前显示下标
    int currentIndex;

};
#endif // WIDGET_H
