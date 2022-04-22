#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void num_clicked();
    void expr_clicked();
    void point_clicked();
    void chop_clicked();
    void clear_clicked();
    void eql_clicked();

private:
    Ui::Widget *ui;

    //1.申请界面上元素
    QPushButton *pb[18];
    QLineEdit *le;

    double num1,num2,num;
    char expr;
};
#endif // WIDGET_H
