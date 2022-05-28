#include "widget.h"

#include <QDragEnterEvent>
#include <QFileInfo>
#include <QImageReader>
#include <QMimeData>  //QMimeData类为记录其MIME类型信息的数据提供了一个容器
#include <QVBoxLayout>

#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    //标签实例化对象
    label = new QLabel(this);
    //垂直布局
    QVBoxLayout* vBoxLayout = new QVBoxLayout(this);
    //向布局中添加控件
    vBoxLayout->addWidget(label);
    //设置布局
    this->setLayout(vBoxLayout);
    //设置大小
    this->resize(600, 400);
    //设置接收drop事件
    this->setAcceptDrops(true);
}

Widget::~Widget() { delete ui; }

//拖动事件
void Widget::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasUrls()) {  //数据中是否包含URL
        event->acceptProposedAction();   //如果是则接收
    } else {
        event->ignore();  //否则忽略该事件
    }
}

//放下事件
void Widget::dropEvent(QDropEvent* event) {
    //获取拖放事件的URL
    QList<QUrl> urlList = event->mimeData()->urls();
    //将其中第一个URL表示为本地路径
    QString filePath = urlList.at(0).toLocalFile();
    //构造QFileInfo
    QFileInfo fileInfo(filePath);
    //判断当前路径是否为文件
    if (fileInfo.isFile()) {
        //获取文件后缀名
        QString suffix = fileInfo.suffix();
        //获取QT支持的图片类型
        QList<QByteArray> imageList = QImageReader::supportedImageFormats();
        //判断文件类型是否是支持的图片类型
        if (imageList.contains(suffix.toUtf8())) {
            //获取图片
            QPixmap pixmap;
            //加载图片
            pixmap.load(filePath);
            //用QLabel显示图片
            label->setPixmap(pixmap);
            //设置QLabel大小
            label->resize(pixmap.width(), pixmap.height());
            //根据Label的支持调整大小
            this->adjustSize();
        }
    }
}
