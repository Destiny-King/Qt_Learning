#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QFile>
#include <QtDebug>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    //状态改变时的槽函数
    void changed(QAudio::State state);

private slots:
    //录音
    void on_pushButton_clicked();

    //停止录音
    void on_pushButton_2_clicked();

    //获取文件路径
    void on_pushButton_3_clicked();

    //播放音频
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QAudioInput *input;
    QAudioOutput *output;
    QFile SaveFile;
    QFile OpenFile;
};
#endif // MAINWINDOW_H
