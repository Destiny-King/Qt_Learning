#ifndef CHOICEQUESTION_H
#define CHOICEQUESTION_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QRadioButton>

class choiceQuestion : public QWidget
{
    Q_OBJECT
public:
    explicit choiceQuestion(QWidget *parent = nullptr);

public slots:
    //选项点击了
    void choiceClicked(bool);
    //设置题目内容
    void setQuestion(QString Question);
    //添加一个选项
    void addChoice(QString Choice);
    //添加一个图片提示
    void setPix(QString filename);

private:
    QGroupBox *gb;
    QVBoxLayout *gb_vbox;
    QLabel *lb_pix;
    QVector<QRadioButton *>choice;

signals:
    void chosed(int index);

};

#endif // CHOICEQUESTION_H
