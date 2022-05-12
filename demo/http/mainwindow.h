#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTextCodec>
#include <QFile>
#include <QUrl>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //请求链接
    void startRequest(QUrl url);

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    //存储网络地址
    QUrl url;
    //文件指针
    QFile *file;

private slots:
    //下载按钮的单击事件槽函数
    void on_pushButton_clicked();
    //完成下载后的处理
    void httpFinished();
    //接收到数据时的处理
    void httpReadyRead();
    //更新进度条
    void updateDataReadProgress(qint64,qint64);
};
#endif // MAINWINDOW_H
