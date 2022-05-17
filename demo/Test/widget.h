#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = 0);
    ~Widget();

private slots:
    void startTimer();
    void display();

    void on_pushButton_clicked();
    void statusChanged(int state);
    void clickAll(bool ok);

private:
    Ui::Widget* ui;

    QTimer* timer;
    int m_number;
};
#endif  // WIDGET_H
