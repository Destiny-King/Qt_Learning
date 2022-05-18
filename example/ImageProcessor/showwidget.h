#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QTextEdit>

class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = 0);
    QImage img;
    QLabel *imageLabel;
    QTextEdit *text;

signals:

private slots:

};

#endif // SHOWWIDGET_H
