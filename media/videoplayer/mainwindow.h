#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QVideoWidget>

//媒体信息结构体
struct MediaObjectInfo{
    //保存视频文件名
    QString fileName;
    //保存视频文件路径
    QString filePath;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //媒体播放器，播放视频
    QMediaPlayer *videoPlayer;

    //媒体列表
    QMediaPlaylist *mediaPlayerList;

    //视频显示窗口
    QVideoWidget *videoWidget;

    //视频列表
    QListWidget *listWidget;

    //播放进度条
    QSlider *durationSlider;

    //音量条
    QSlider *volumeSlider;

    //视频播放器按钮
    QPushButton *pushButton[5];

    //水平布局
    QHBoxLayout *hBoxLayout[3];

    //水平容器
    QWidget *hWidget[3];

    //标签文本
    QLabel *label[2];

    //垂直布局
    QVBoxLayout *vBoxLayout[2];

    //垂直容器
    QWidget *vWidget[2];

    //视频布局函数
    void videoLayout();

    //主窗体大小重写函数
    void resizeEvent(QResizeEvent *event);

    //媒体信息存储
    QVector<MediaObjectInfo> mediaObjectInfo;

    //扫描本地视频文件
    void scanVideoFiles();

    //媒体初始化
    void mediaPlayerInit();

private slots:
    //播放视频按钮点击
    void btn_play_clicked();

    //下一个视频按钮点击
    void btn_next_clicked();

    //音量加
    void btn_volumeup_clicked();

    //音量减
    void btn_volumedown_clicked();

    //全屏
    void btn_fullscreen_clicked();

    //媒体状态改变
    void mediaPlayerStateChanged(QMediaPlayer::State);

    //列表单击
    void listWidgetClicked(QListWidgetItem *);

    //媒体列表项改变
    void mediaPlaylistCurrentIndexChanged(int);

    //媒体总长度改变
    void mediaPlayDurationChanged(qint64);

    //媒体播放位置改变
    void mediaPlayPositionChanged(qint64);

    //播放进度条松开
    void durationSliderReleased();

    //音量条松开
    void volumeSliderReleased();
};
#endif // MAINWINDOW_H
