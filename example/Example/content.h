#ifndef CONTENT_H
#define CONTENT_H

#include <QDialog>
#include <QFrame>
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "baseinfo.h"
#include "contact.h"
#include "detail.h"

class Content : public QFrame
{
    Q_OBJECT

public:
    Content(QWidget *parent = 0);
    //堆栈窗体对象
    QStackedWidget *stack;
    QPushButton *AmendBtn;
    QPushButton *CloseBtn;

    BaseInfo *baseInfo;
    Contact *contact;
    Detail *detail;

};
#endif // CONTENT_H
