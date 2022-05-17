#include "mythread.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QVector>

Generate::Generate(QObject* parent) : QThread(parent) {}

void Generate::receiveNum(int num) { m_num = num; }

void Generate::run() {
    qDebug() << "生成随机数的线程地址" << QThread::currentThread();
    //定义整型容器
    QVector<int> list;
    //定义记录时间对象
    QElapsedTimer time;
    //启动计时器
    time.start();
    for (int i = 0; i < m_num; i++) {
        //将随机生成的数添加到容器中
        list.push_back(qrand() % 10000);
    }
    //获取时间
    int milsec = time.elapsed();
    qDebug() << "生成" << m_num << "个随机数" << milsec << "毫秒";
    //发送信号到主线程
    emit sendArray(list);
}
