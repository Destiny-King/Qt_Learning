#ifndef IMAGESWITCH_H
#define IMAGESWITCH_H

#include <QWidget>

class ImageSwitch : public QWidget
{
    Q_OBJECT
public:
    enum ButtonStyle{
      ButtonStyle_1 = 0,   //开关样式1
      ButtonStyle_2 = 1,   //开关样式2
      ButtonStyle_3 = 2,   //开关样式3
    };
    explicit ImageSwitch(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *event);

public slots:
    //设置是否被选中
    void setChecked(bool isChecked);
    //设置按钮样式
    void setButtonStyle(const ImageSwitch::ButtonStyle &buttonStyle);

private:
    bool isChecked;
    ButtonStyle buttonStyle;

    QString imgOffFile;
    QString imgOnFile;
    QString imgFile;

signals:

};

#endif // IMAGESWITCH_H
