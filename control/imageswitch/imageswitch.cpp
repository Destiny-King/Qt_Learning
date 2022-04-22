#include "imageswitch.h"
#include <QPainter>

ImageSwitch::ImageSwitch(QWidget *parent) : QWidget(parent)
{
    isChecked = false;
    buttonStyle = ButtonStyle_2;

    imgOffFile = ":/images/btncheckoff2.png";
    imgOnFile = ":/images/btncheckon2.png";
    imgFile = imgOffFile;
}

void ImageSwitch::mousePressEvent(QMouseEvent *)
{
    imgFile = isChecked ? imgOffFile : imgOnFile;
    isChecked = !isChecked;
    this->update();
}

void ImageSwitch::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //指示引擎应使用平滑的pixmap变换算法
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    QImage img(imgFile);
    //KeepAspectRatio :该大小被缩放为给定矩形内尽可能大的矩形，保留纵横比
    //SmoothTransformation :生成的图像使用双线性滤波进行变换
    img = img.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    //按照比例自动居中绘制
    int pixX = rect().center().x() - img.width() / 2;
    int pixY = rect().center().y() - img.height() / 2;
    QPoint point(pixX,pixY);
    painter.drawImage(point,img);
}

void ImageSwitch::setChecked(bool isChecked)
{
    if(this->isChecked != isChecked){
        this->isChecked = isChecked;
        imgFile = isChecked ? imgOnFile : imgOffFile;
        this->update();
    }
}

void ImageSwitch::setButtonStyle(const ImageSwitch::ButtonStyle &buttonStyle)
{
    if(this->buttonStyle != buttonStyle){
        this->buttonStyle = buttonStyle;

        if(buttonStyle == ButtonStyle_1){
            imgOffFile = ":/images/btncheckoff1.png";
            imgOnFile = ":/images/btncheckon1.png";
            this->resize(87,28);
        }else if(buttonStyle == ButtonStyle_2){
            imgOffFile = ":/images/btncheckoff2.png";
            imgOnFile = ":/images/btncheckon2.png";
            this->resize(87,28);
        }else if(buttonStyle == ButtonStyle_3){
            imgOffFile = ":/images/btncheckoff3.png";
            imgOnFile = ":/images/btncheckon3.png";
            this->resize(96,38);
        }
        imgFile = isChecked ? imgOnFile : imgOffFile;
        setChecked(isChecked);
        this->update();
        //通知布局系统此小部件已更改，可能需要更改几何图形。
        updateGeometry();
    }
}
