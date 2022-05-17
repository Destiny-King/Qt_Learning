#include "threadtest.h"

#include "ui_threadtest.h"

threadTest::threadTest(QWidget* parent) : QWidget(parent), ui(new Ui::threadTest) {
    ui->setupUi(this);
    //创建子线程对象
    generate = new Generate;
    connect(this, SIGNAL(starting(int)), generate, SLOT(receiveNum(int)));
    //启动子线程
    connect(ui->startBtn, SIGNAL(clicked(bool)), this, SLOT(display()));
    connect(generate, SIGNAL(sendArray(QVector<int>)), this, SLOT(receiveArray(QVector<int>)));
}

threadTest::~threadTest() { delete ui; }

void threadTest::display() {
    //发送信号给子线程
    emit starting(1000);
    //开始子线程
    generate->start();
}

void threadTest::receiveArray(QVector<int> list) {
    for (int i = 0; i < list.size(); ++i) {
        ui->randList->addItem(QString::number(list.at(i)));
    }
}
