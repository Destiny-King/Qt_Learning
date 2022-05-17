#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class Generate : public QThread {
    Q_OBJECT
public:
    Generate(QObject* parent = 0);

public slots:
    void receiveNum(int num);

protected:
    void run() override;

private:
    int m_num;

signals:
    void sendArray(QVector<int> num);
};

#endif  // MYTHREAD_H
