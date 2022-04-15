#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //用于初始化
    QAudioFormat format;
    format.setSampleRate(44100);//采样率
    format.setChannelCount(2);//通道
    format.setSampleSize(16);//样本长度
    format.setByteOrder(QAudioFormat::LittleEndian);//设置端字节序：小端序
    format.setSampleType(QAudioFormat::UnSignedInt);//存储样本数据类型
    format.setCodec("audio/pcm");//这个用来设置编码器为audio/pcm，该编码器为所有平台支持

    //监测当前设置是否支持format设置的格式
    QAudioDeviceInfo infodev = QAudioDeviceInfo::defaultInputDevice();
    if(!infodev.isFormatSupported(format))
    {//不支持打印一下
        qDebug()<<"format";
    }

    //设置录音对象的格式
    input = new QAudioInput(format,this);

    //设置播放音频对象格式,关联状态槽函数，当状态改变后将触发该槽函数
    /*
            当播放音频时，状态改变就会发出一个stateChanged信号，一共有五种状态
             enum State { ActiveState,   //运行状态
                          SuspendedState, // 挂起状态
                          StoppedState, //停止状态
                          IdleState,    //空闲状态
                          InterruptedState //中断状态
              };
        */
    output = new QAudioOutput(format,this);
    connect(output,&QAudioOutput::stateChanged,this,&MainWindow::changed);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changed(QAudio::State state)
{
    if(state == QAudio::IdleState){
        SaveFile.close();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();//获取保存的文件名，默认路径在当前目录
    if(name.isEmpty())
    {
        name="my.raw";
    }

    OpenFile.setFileName(name);
    OpenFile.open(QIODevice::ReadWrite);

    qDebug()<<name;
    //开始录音并且给一个文件路径
    input->start(&OpenFile);
}

void MainWindow::on_pushButton_2_clicked()
{
    //停止录音，关闭文件，不关闭数据不会真正写入文件
    input->stop();
    OpenFile.close();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName();//弹出文件对话框获取文件路径与名称
    ui->lineEdit->setText(fileName);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString name = ui->lineEdit->text();
    SaveFile.setFileName(name);
    SaveFile.open(QFileDevice::ReadOnly);   //打开音频文件只读
    output->start(&SaveFile);

}

