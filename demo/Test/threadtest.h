#ifndef THREADTEST_H
#define THREADTEST_H

#include <QWidget>

#include "mythread.h"

namespace Ui {
    class threadTest;
}

class threadTest : public QWidget {
    Q_OBJECT

public:
    explicit threadTest(QWidget* parent = nullptr);
    ~threadTest();

public slots:
    void receiveArray(QVector<int> list);

private:
    Ui::threadTest* ui;

    Generate* generate;

private slots:
    void display();

signals:
    void starting(int num);
};

#endif  // THREADTEST_H
