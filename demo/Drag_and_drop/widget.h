#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

protected:
    void dragEnterEvent(QDragEnterEvent* event);  //拖动进入事件
    void dropEvent(QDropEvent* event);            //放下事件

private:
    Ui::Widget* ui;

    QLabel* label;  //标签，用于显示拖入的图片
};
#endif  // WIDGET_H
