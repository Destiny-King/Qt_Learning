#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>

Drawer::Drawer(QWidget *parent,Qt::WindowFlags f)
{
    setWindowTitle(tr("My QQ"));

    toolBtn1_1 = new QToolButton;
    toolBtn1_1->setText(tr("张三"));
    QPixmap pixmap1(":/images/1.png");
    toolBtn1_1->setIcon(pixmap1);
    toolBtn1_1->setIconSize(pixmap1.size());
    toolBtn1_1->setAutoRaise(true);
    toolBtn1_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_2 = new QToolButton;
    toolBtn1_2->setText(tr("李四"));
    QPixmap pixmap2(":/images/2.png");
    toolBtn1_2->setIcon(pixmap2);
    toolBtn1_2->setIconSize(pixmap2.size());
    toolBtn1_2->setAutoRaise(true);
    toolBtn1_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_3 = new QToolButton;
    toolBtn1_3->setText(tr("王五"));
    QPixmap pixmap3(":/images/3.png");
    toolBtn1_3->setIcon(pixmap3);
    toolBtn1_3->setIconSize(pixmap3.size());
    toolBtn1_3->setAutoRaise(true);
    toolBtn1_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_4 = new QToolButton;
    toolBtn1_4->setText(tr("小赵"));
    QPixmap pixmap4(":/images/4.png");
    toolBtn1_4->setIcon(pixmap4);
    toolBtn1_4->setIconSize(pixmap4.size());
    toolBtn1_4->setAutoRaise(true);
    toolBtn1_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn1_5 = new QToolButton;
    toolBtn1_5->setText(tr("小孙"));
    QPixmap pixmap5(":/images/5.png");
    toolBtn1_5->setIcon(pixmap5);
    toolBtn1_5->setIconSize(pixmap5.size());
    toolBtn1_5->setAutoRaise(true);
    toolBtn1_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox1 = new QGroupBox;
    QVBoxLayout *layout1 = new QVBoxLayout(groupBox1);
    layout1->setMargin(10);
    layout1->setAlignment(Qt::AlignHCenter);
    layout1->addWidget(toolBtn1_1);
    layout1->addWidget(toolBtn1_2);
    layout1->addWidget(toolBtn1_3);
    layout1->addWidget(toolBtn1_4);
    layout1->addWidget(toolBtn1_5);
    layout1->addStretch();

    toolBtn2_1 = new QToolButton;
    toolBtn2_1->setText(tr("小王"));
    QPixmap pixmap6(":/images/6.png");
    toolBtn2_1->setIcon(pixmap6);
    toolBtn2_1->setIconSize(pixmap6.size());
    toolBtn2_1->setAutoRaise(true);
    toolBtn2_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn2_2 = new QToolButton;
    toolBtn2_2->setText(tr("小张"));
    QPixmap pixmap7(":/images/7.png");
    toolBtn2_2->setIcon(pixmap7);
    toolBtn2_2->setIconSize(pixmap7.size());
    toolBtn2_2->setAutoRaise(true);
    toolBtn2_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox2 = new QGroupBox;
    QVBoxLayout *layout2 = new QVBoxLayout(groupBox2);
    layout2->setMargin(10);
    layout2->setAlignment(Qt::AlignHCenter);
    layout2->addWidget(toolBtn2_1);
    layout2->addWidget(toolBtn2_2);

    toolBtn3_1 = new QToolButton;
    toolBtn3_1->setText(tr("小陈"));
    QPixmap pixmap8(":/images/8.png");
    toolBtn3_1->setIcon(pixmap8);
    toolBtn3_1->setIconSize(pixmap8.size());
    toolBtn3_1->setAutoRaise(true);
    toolBtn3_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    toolBtn3_2 = new QToolButton;
    toolBtn3_2->setText(tr("小李"));
    QPixmap pixmap9(":/images/9.png");
    toolBtn3_2->setIcon(pixmap9);
    toolBtn3_2->setIconSize(pixmap9.size());
    toolBtn3_2->setAutoRaise(true);
    toolBtn3_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QGroupBox *groupBox3 = new QGroupBox;
    QVBoxLayout *layout3 = new QVBoxLayout(groupBox3);
    layout3->setMargin(10);
    layout3->setAlignment(Qt::AlignHCenter);
    layout3->addWidget(toolBtn3_1);
    layout3->addWidget(toolBtn3_2);

    this->addItem(groupBox1,tr("我的好友"));
    this->addItem(groupBox2,tr("陌生人"));
    this->addItem(groupBox3,tr("黑名单"));
}
