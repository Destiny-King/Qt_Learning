#ifndef DEVICESIZETABLE_H
#define DEVICESIZETABLE_H

#include <QTableWidget>
#include <QProcess>

class DeviceSizeTable : public QTableWidget
{
    Q_OBJECT
public:
    DeviceSizeTable(QWidget *parent = 0);

private:
    QColor bgColor;                 //背景颜色
    QColor chunkColor1;             //进度颜色1
    QColor chunkColor2;             //进度颜色2
    QColor chunkColor3;             //进度颜色3
    QColor textColor1;              //文字颜色1
    QColor textColor2;              //文字颜色2
    QColor textColor3;              //文字颜色3

    QProcess *process;              //执行命令进程

private slots:
    void readData();
    void checkSize(const QString &result,const QString &name);
    void insertSize(const QString &name,const QString &use,const QString &free,const QString &all,int percent);

public slots:
    //载入容量
    void load();

signals:
    void udiskReceive(const QString &udiskName);

};

#endif // DEVICESIZETABLE_H
