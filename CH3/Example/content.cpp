#include "content.h"

Content::Content(QWidget *parent)
    : QFrame(parent)
{
    stack = new QStackedWidget(this);
    stack->setFrameStyle(QFrame::Panel | QFrame::Raised);
    baseInfo = new BaseInfo();
    contact = new Contact();
    detail = new Detail();
    stack->addWidget(baseInfo);
    stack->addWidget(contact);
    stack->addWidget(detail);

    AmendBtn = new QPushButton(tr("修改"));
    CloseBtn = new QPushButton(tr("关闭"));
    QHBoxLayout *BtnLayout = new QHBoxLayout();
    //将最小尺寸为零且拉伸因子为拉伸的可拉伸空间（QSpacerItem）添加到此水平布局的末尾
    BtnLayout->addStretch(1);
    BtnLayout->addWidget(AmendBtn);
    BtnLayout->addWidget(CloseBtn);

    QVBoxLayout *RightLayout = new QVBoxLayout(this);
    RightLayout->setMargin(10);
    RightLayout->setSpacing(6);
    RightLayout->addWidget(stack);
    RightLayout->addLayout(BtnLayout);

}
