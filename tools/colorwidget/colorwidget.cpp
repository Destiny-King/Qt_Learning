#include "colorwidget.h"

#include <QApplication>
#include <QFont>
#include <QMouseEvent>
#include <QMutex>
#include <QMutexLocker>
#include <QPixmap>
#include <QScreen>
#include <QTimer>

ColorWidget* ColorWidget::instance = 0;
ColorWidget* ColorWidget::Instance() {
    if (!instance) {
        static QMutex mutex;          //创建线程互斥对象
        QMutexLocker locker(&mutex);  //创建互斥锁对象
        if (!instance) {
            instance = new ColorWidget;  //创建一个新的取色窗体
        }
    }
    return instance;
}

ColorWidget::ColorWidget(QWidget* parent) : QWidget(parent) {
    //初始化
    //栅格布局对象
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);                       //将垂直和水平间距设置为间距
    gridLayout->setContentsMargins(11, 11, 11, 11);  //设置布局周围的左、上、右和底边距

    //垂直布局对象
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(0);

    //显示颜色标签对象
    labColor = new QLabel(this);
    labColor->setText("+");  //设置文本
    // background-color:#ff6b6b color:#fafafa
    //设置样式颜色
    labColor->setStyleSheet("background-color:rgb(255,107,107);color:rgb(250,250,250)");
    labColor->setAlignment(Qt::AlignCenter);  //设置标签对齐方式为居中
    QFont font;
    font.setPixelSize(35);    //设置字体文本像素大小
    font.setBold(true);       //设置加粗
    labColor->setFont(font);  //设置字体

    // QSizePolicy类是一个布局属性，描述水平和垂直调整大小策略
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    //将大小策略的水平拉伸因子设置为给定的拉伸因子
    sizePolicy.setHorizontalStretch(0);
    //将大小策略的垂直拉伸因子设置为给定的拉伸因子
    sizePolicy.setVerticalStretch(0);
    //设置标志，以确定小部件的首选高度是否取决于其宽度
    sizePolicy.setHeightForWidth(labColor->sizePolicy().hasHeightForWidth());
    labColor->setSizePolicy(sizePolicy);            //设置调整大小策略
    labColor->setMinimumSize(80, 70);               //设置最小大小
    labColor->setMaximumSize(80, 70);               //设置最大大小
    labColor->setCursor(QCursor(Qt::CrossCursor));  //设置光标为准星光标
    labColor->setFrameShape(QFrame::StyledPanel);   //设置框架形状
    labColor->setFrameShadow(QFrame::Sunken);       //设置框架阴影

    verticalLayout->addWidget(labColor);  //向垂直布局添加标签

    lab = new QLabel(this);
    lab->setMinimumSize(QSize(0, 18));  //设置最小大小
    //设置样式 #000000 #c8c8c8
    lab->setStyleSheet("background-color:rgb(0,0,0);color:rgb(200,200,200);");
    lab->setAlignment(Qt::AlignCenter);

    verticalLayout->addWidget(lab);  //向垂直布局添加标签
    gridLayout->addLayout(verticalLayout, 0, 0, 3, 1);

    //创建对象，添加布局
    labHex = new QLabel(this);
    gridLayout->addWidget(labHex, 0, 1, 1, 1);

    txtHex = new QLineEdit(this);
    gridLayout->addWidget(txtHex, 0, 2, 1, 1);

    labRgb = new QLabel(this);
    gridLayout->addWidget(labRgb, 1, 1, 1, 1);

    txtRgb = new QLineEdit(this);
    gridLayout->addWidget(txtRgb, 1, 2, 1, 1);

    labPoint = new QLabel(this);
    gridLayout->addWidget(labPoint, 2, 1, 1, 1);

    txtPoint = new QLineEdit(this);
    gridLayout->addWidget(txtPoint, 2, 2, 1, 1);

    //设置文本
    lab->setText("当前颜色");
    labHex->setText("16进制值:");
    labRgb->setText("RGB值:");
    labPoint->setText("坐标值:");

    this->setLayout(gridLayout);
    this->setWindowTitle("屏幕取色器");
    this->setFixedSize(300, 100);

    //返回与剪贴板交互的对象
    cp = QApplication::clipboard();
    pressed = false;

    timer = new QTimer(this);
    timer->setInterval(100);  //设置间隔
    connect(timer, SIGNAL(timeout()), this, SLOT(showColorValue()));
    timer->start();  //启动定时器
}

ColorWidget::~ColorWidget() {}

void ColorWidget::mousePressEvent(QMouseEvent* e) {
    //鼠标按下坐标在标签矩形内
    if (labColor->rect().contains(e->pos())) {
        pressed = true;
    }
}

void ColorWidget::mouseReleaseEvent(QMouseEvent*) { pressed = false; }

void ColorWidget::showColorValue() {
    if (!pressed) {
        return;
    }
    int x = QCursor::pos().x();                          //获取光标位置的x坐标
    int y = QCursor::pos().y();                          //获取光标位置的y坐标
    txtPoint->setText(tr("x:%1   y:%2").arg(x).arg(y));  //设置文本

    QScreen* screen = qApp->primaryScreen();             //保存应用程序的主屏幕
    QPixmap pixmap = screen->grabWindow(0, x, y, 2, 2);  //创建并返回一个像素图

    int red, green, blue;
    QString strDecimalValue, strHex;
    if (pixmap.isNull()) {
        return;
    }

    QImage image = pixmap.toImage();       //将像素图转换为QImage
    if (image.valid(0, 0)) {               //如果pos是图像中的有效坐标对
        QColor color = image.pixel(0, 0);  //返回给定位置像素的颜色
        red = color.red();                 //返回此颜色的红色组件
        green = color.green();             //返回此颜色的绿色组件
        blue = color.blue();               //返回此颜色的蓝色组件
        QString strRed = tr("%1").arg(red & 0xFF, 2, 16, QChar('0'));
        QString strGreen = tr("%1").arg(green & 0xFF, 2, 16, QChar('0'));
        QString strBlue = tr("%1").arg(blue & 0xFF, 2, 16, QChar('0'));

        strDecimalValue = tr("%1,%2,%3").arg(red).arg(green).arg(blue);  //设置RGB值
        //设置16进制值
        strHex = tr("%1%2%3").arg(strRed.toUpper()).arg(strGreen.toUpper()).arg(strBlue.toUpper());
    }

    //根据背景色自动计算合适的前景色
    QColor color(red, green, blue);
    //灰度 = 红×0.299 + 绿×0.587 + 蓝×0.114
    double gray = (0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue()) / 255;
    QColor textColor = gray > 0.5 ? Qt::black : Qt::white;
    QString str = tr("background:rgb(%1);color:%2").arg(strDecimalValue).arg(textColor.name());
    labColor->setStyleSheet(str);
    txtRgb->setText(strDecimalValue);
    txtHex->setText(strHex);
}
