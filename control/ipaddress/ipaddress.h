#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class IPAddress : public QWidget
{
    Q_OBJECT
public:
    explicit IPAddress(QWidget *parent = nullptr);

    //获取IP
    QString getIP()     const;

public slots:
    //设置IP地址
    void setIP(const QString &ip);
    //清空
    void clear();
    //设置背景颜色
    void setBgColor(const QString &bgColor);
    //设置边框颜色
    void setBorderColor(const QString &borderColor);
    //设置圆角角度
    void setBorderRadius(int borderRadius);

protected:
    bool eventFilter(QObject *watched,QEvent *event);

private:
    QLabel *labDot1;     //第一个小圆点
    QLabel *labDot2;     //第二个小圆点
    QLabel *labDot3;     //第三个小圆点

    QLineEdit *txtIP1;   //IP地址网段输入框1
    QLineEdit *txtIP2;   //IP地址网段输入框2
    QLineEdit *txtIP3;   //IP地址网段输入框3
    QLineEdit *txtIP4;   //IP地址网段输入框4

    QString ip;          //IP地址
    QString bgColor;     //背景颜色
    QString borderColor; //边框颜色
    int borderRadius;    //边框圆角角度

private slots:
    void textChanged(const QString &text);

signals:

};

#endif // IPADDRESS_H
