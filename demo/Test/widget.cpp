#include "widget.h"

#include <QMessageBox>
#include <QTime>

#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    //实例化定时器对象
    timer = new QTimer(this);
    //设置定时器精度
    timer->setTimerType(Qt::PreciseTimer);
    //点击按钮，开始计时器
    connect(ui->loopBtn, SIGNAL(clicked(bool)), this, SLOT(startTimer()));
    //定时器每个1秒钟，显示时间
    connect(timer, SIGNAL(timeout()), this, SLOT(display()));

    m_number = 0;
    //三态复选框
    ui->wives->setTristate(true);
    connect(ui->wives, SIGNAL(clicked(bool)), this, SLOT(clickAll(bool)));
    connect(ui->jianning, SIGNAL(stateChanged(int)), this, SLOT(statusChanged(int)));
    connect(ui->longer, SIGNAL(stateChanged(int)), this, SLOT(statusChanged(int)));
    connect(ui->fangyi, SIGNAL(stateChanged(int)), this, SLOT(statusChanged(int)));
    connect(ui->zengrou, SIGNAL(stateChanged(int)), this, SLOT(statusChanged(int)));
    connect(ui->mujianping, SIGNAL(stateChanged(int)), this, SLOT(statusChanged(int)));
    connect(ui->shuanger, SIGNAL(stateChanged(int)), this, SLOT(statusChanged(int)));
    connect(ui->ake, SIGNAL(stateChanged(int)), this, SLOT(statusChanged(int)));
}

Widget::~Widget() { delete ui; }

void Widget::startTimer() {
    //如果定时器启动
    if (timer->isActive()) {
        //关闭定时器
        timer->stop();
        //将按钮显示为开始
        ui->loopBtn->setText("开始");
    } else {
        //将按钮显示为关闭
        ui->loopBtn->setText("关闭");
        //开始定时器
        timer->start(1000);
    }
}

void Widget::display() {
    //获取当前时间
    QTime time = QTime::currentTime();
    //时间格式化
    QString timeStr = time.toString("hh:mm:ss.zzz");
    //设置标签显示时间
    ui->curTime->setText(timeStr);
}

void Widget::on_pushButton_clicked() {
    QMessageBox::about(this, "Hello", "你好！");
    int ret = QMessageBox::question(this, "question", "你确定吗？", QMessageBox::Close | QMessageBox::Cancel,
                                    QMessageBox::Cancel);
    if (ret == QMessageBox::Close) {
        close();
    } else if (ret == QMessageBox::Cancel) {
    }
}

void Widget::statusChanged(int state) {
    if (state == Qt::Checked) {
        m_number++;
    } else {
        m_number--;
    }

    //判断根节点状态
    if (m_number == 7) {
        ui->wives->setCheckState(Qt::Checked);
    } else if (m_number == 0) {
        ui->wives->setCheckState(Qt::Unchecked);
    } else {
        ui->wives->setCheckState(Qt::PartiallyChecked);
    }
}

void Widget::clickAll(bool ok) {
    if (ok) {
        ui->jianning->setChecked(true);
        ui->longer->setChecked(true);
        ui->fangyi->setChecked(true);
        ui->zengrou->setChecked(true);
        ui->mujianping->setChecked(true);
        ui->shuanger->setChecked(true);
        ui->ake->setChecked(true);
    } else {
        ui->jianning->setChecked(false);
        ui->longer->setChecked(false);
        ui->fangyi->setChecked(false);
        ui->zengrou->setChecked(false);
        ui->mujianping->setChecked(false);
        ui->shuanger->setChecked(false);
        ui->ake->setChecked(false);
    }
}
