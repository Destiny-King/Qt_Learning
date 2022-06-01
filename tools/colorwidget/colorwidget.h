#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

class ColorWidget : public QWidget {
    Q_OBJECT
public:
    static ColorWidget* Instance();
    explicit ColorWidget(QWidget* parent = nullptr);
    ~ColorWidget();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

private:
    static ColorWidget* instance;  //实例
    QClipboard* cp;                //剪贴板对象
    bool pressed;                  //是否按下
    QTimer* timer;                 //定时器对象

    QGridLayout* gridLayout;      //栅格布局对象
    QVBoxLayout* verticalLayout;  //垂直布局对象
    QLabel* labColor;             //显示颜色标签
    QLabel* lab;                  //显示当前颜色文本
    QLabel* labHex;               // 16进制值
    QLineEdit* txtHex;            // 16进制编辑框
    QLabel* labRgb;               // RGB值
    QLineEdit* txtRgb;            // RGB编辑框
    QLabel* labPoint;             //坐标值
    QLineEdit* txtPoint;          //坐标编辑框

private slots:
    void showColorValue();  //显示颜色值槽函数
};

#endif  // COLORWIDGET_H
