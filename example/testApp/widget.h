#ifndef WIDGET_H
#define WIDGET_H

#include "choicequestion.h"
#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void createQuestion();

private slots:
    void makeChoice(int);
    void endTest();
    void displayTime();

private:
    QLabel *lb_name;
    QLCDNumber *lcd_time;
    //装所有题目显示板的容器
    QVector<choiceQuestion *> questions;
    //装所有答题信息的容器
    QVector<int> questionAnswer;
    QProgressBar *pb_progress;
    QPushButton *bt_over;

    QTimer *timer;

};
#endif // WIDGET_H
