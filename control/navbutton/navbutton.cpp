#include "navbutton.h"
#include <QPainter>
#include <QDebug>

NavButton::NavButton(QWidget *parent) : QPushButton(parent)
{
    //文字间隔
    paddingLeft = 20;
    paddingRight = 5;
    paddingTop = 5;
    paddingBottom = 5;
    textAlign = TextAlign_Left;

    //倒三角
    showTriangle = false;
    triangleLen = 5;
    trianglePosition = TrianglePosition_Right;
    //255,255,255->#ffffff->白色
    triangleColor = QColor(255,255,255);

    //图标
    showIcon = false;
    iconSpace = 10;
    iconSize = QSize(16,16);
    iconNormal = QPixmap();
    iconHover = QPixmap();
    iconCheck = QPixmap();

    //线条
    showLine = true;
    lineSpace = 0;
    lineWidth = 5;
    linePosition = LinePosition_Left;
    lineColor = QColor(0, 187, 158);

    //背景文字颜色
    normalBgColor = QColor(230, 230, 230);
    hoverBgColor = QColor(130, 130, 130);
    checkBgColor = QColor(80, 80, 80);
    normalTextColor = QColor(100, 100, 100);
    hoverTextColor = QColor(255, 255, 255);
    checkTextColor = QColor(255, 255, 255);

    //背景画刷
    normalBgBrush = Qt::NoBrush;
    hoverBgBrush = Qt::NoBrush;
    checkBgBrush = Qt::NoBrush;

    hover = false;
    setCheckable(true);
    setText("导航按钮");
}

void NavButton::enterEvent(QEvent *)
{
    hover = true;
    this->update();
}

void NavButton::leaveEvent(QEvent *)
{
    hover = false;
    this->update();
}

void NavButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作，启动反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
    //绘制图标
    drawIcon(&painter);
    //绘制边框线条
    drawLine(&painter);
    //绘制倒三角
    drawTriangle(&painter);
}

void NavButton::drawBg(QPainter *painter)
{
    painter->save();
    //设置画笔
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();

    //背景矩形
    QRect bgRect;
    if(linePosition == LinePosition_Left){
        bgRect = QRect(lineSpace,0,width - lineSpace,height);
    }else if(linePosition == LinePosition_Right){
        bgRect = QRect(0,0,width - lineSpace,height);
    }else if(linePosition == LinePosition_Top){
        bgRect = QRect(0,lineSpace,width,height - lineSpace);
    }else if(linePosition == LinePosition_Bottom){
        bgRect = QRect(0,0,width,height - lineSpace);
    }

    //如果画刷存在就取画刷
    QBrush bgBrush;
    if(isChecked()){
        bgBrush = checkBgBrush;
    }else if(hover){
        bgBrush = hoverBgBrush;
    }else{
        bgBrush = normalBgBrush;
    }

    if(bgBrush != Qt::NoBrush){
        painter->setBrush(bgBrush);
    }else{
        //根据当前状态选择对应颜色
        QColor bgColor;
        if(isChecked()){
            bgColor = checkBgColor;
        }else if(hover){
            bgColor = hoverBgColor;
        }else{
            bgColor = normalBgColor;
        }
        painter->setBrush(bgColor);
    }
    //绘画
    painter->drawRect(bgRect);
    //保存状态
    painter->restore();
}

void NavButton::drawText(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //根据当前状态选择对应颜色
    QColor textColor;
    if(isChecked()){
        textColor = checkTextColor;
    }else if(hover){
        textColor = hoverTextColor;
    }else{
        textColor = normalTextColor;
    }

    //文本矩形
    QRect textRect = QRect(paddingLeft,paddingTop,width() - paddingLeft - paddingRight,height() - paddingTop - paddingBottom);
    painter->setPen(textColor);
    //在提供的矩形内绘制给定的文本
    painter->drawText(textRect,textAlign | Qt::AlignVCenter,text());
    //保存状态
    painter->restore();
}

void NavButton::drawIcon(QPainter *painter)
{
    //判断是否显示图标
    if(!showIcon){
        return;
    }
    painter->save();

    QPixmap pix;
    if(isChecked()){
        pix = iconCheck;
    }else if(hover){
        pix = iconHover;
    }else{
        pix = iconNormal;
    }

    if(!pix.isNull()){
        //等比例平滑缩放图标
        pix = pix.scaled(iconSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        //绘图
        painter->drawPixmap(iconSpace,(height() - iconSize.height()) / 2,pix);
    }
    //保存状态
    painter->restore();
}

void NavButton::drawLine(QPainter *painter)
{
    if(!showLine){
        return;
    }

    if(!isChecked()){
        return;
    }

    painter->save();

    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    //根据线条位置设置线条坐标
    QPoint pointStart,pointEnd;
    if(linePosition == LinePosition_Left){
        pointStart = QPoint(0,0);
        pointEnd = QPoint(0,height());
    }else if(linePosition == LinePosition_Right){
        pointStart = QPoint(width(),0);
        pointEnd = QPoint(width(),height());
    }else if(linePosition == LinePosition_Top){
        pointStart = QPoint(0,0);
        pointEnd = QPoint(width(),0);
    }else if (linePosition == LinePosition_Bottom) {
        pointStart = QPoint(0, height());
        pointEnd = QPoint(width(), height());
    }
    //画线
    painter->drawLine(pointStart,pointEnd);
    //保存状态
    painter->restore();
}

void NavButton::drawTriangle(QPainter *painter)
{
    if(!showTriangle){
        return;
    }
    //选中或者悬停显示
    if(!hover && !isChecked()){
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(triangleColor);

    //绘制在右侧中间，根据设定的倒三角的边长设定三个点位置
    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;

    //QPolygon类提供了一个使用整数精度的点向量
    QPolygon pts;
    if(trianglePosition == TrianglePosition_Left){
        pts.setPoints(3,triangleLen,midHeight,0,midHeight - triangleLen,0,midHeight + triangleLen);
    }else if(trianglePosition == TrianglePosition_Right){
        pts.setPoints(3,width - triangleLen,midHeight,width,midHeight - triangleLen,width,midHeight + triangleLen);
    }else if(trianglePosition == TrianglePosition_Top){
        pts.setPoints(3,midWidth,triangleLen,midWidth - triangleLen,0,midWidth + triangleLen,0);
    }else if(trianglePosition == TrianglePosition_Bottom){
        pts.setPoints(3,midWidth,height - triangleLen,midWidth - triangleLen,height,midWidth + triangleLen,height);
    }

    //使用当前钢笔和画笔绘制由数组点中的第一个pointCount点定义的多边形
    painter->drawPolygon(pts);
    //保存状态
    painter->restore();
}

//左边距间隔
void NavButton::setPaddingLeft(int paddingLeft)
{
    if(this->paddingLeft != paddingLeft){
        this->paddingLeft = paddingLeft;
        this->update();
    }
}

//右边距间隔
void NavButton::setPaddingRight(int paddingRight)
{
    if (this->paddingRight != paddingRight) {
        this->paddingRight = paddingRight;
        this->update();
    }
}

void NavButton::setPaddingTop(int paddingTop)
{
    if (this->paddingTop != paddingTop) {
        this->paddingTop = paddingTop;
        this->update();
    }
}

void NavButton::setpaddingBottom(int paddingBottom)
{
    if (this->paddingBottom != paddingBottom) {
        this->paddingBottom = paddingBottom;
        this->update();
    }
}

void NavButton::setPadding(int padding)
{
    setPadding(padding,padding,padding,padding);
}

void NavButton::setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom)
{
    this->paddingLeft = paddingLeft;
    this->paddingRight = paddingRight;
    this->paddingTop = paddingTop;
    this->paddingBottom = paddingBottom;
    this->update();
}

void NavButton::setTextAlign(const TextAlign &textAlign)
{
    if (this->textAlign != textAlign) {
        this->textAlign = textAlign;
        this->update();
    }
}

//设置显示倒三角
void NavButton::setShowTriangle(bool showTriangle)
{
    if (this->showTriangle != showTriangle) {
        this->showTriangle = showTriangle;
        this->update();
    }
}

void NavButton::setTriangleLen(int triangleLen)
{
    if (this->triangleLen != triangleLen) {
        this->triangleLen = triangleLen;
        this->update();
    }
}

void NavButton::setTrianglePosition(const TrianglePosition &trianglePosition)
{
    if (this->trianglePosition != trianglePosition) {
        this->trianglePosition = trianglePosition;
        this->update();
    }
}

void NavButton::setTriangleColor(const QColor &triangleColor)
{
    if (this->triangleColor != triangleColor) {
        this->triangleColor = triangleColor;
        this->update();
    }
}

void NavButton::setShowIcon(bool showIcon)
{
    if (this->showIcon != showIcon) {
        this->showIcon = showIcon;
        this->update();
    }
}

void NavButton::setIconSpace(int iconSpace)
{
    if (this->iconSpace != iconSpace) {
        this->iconSpace = iconSpace;
        this->update();
    }
}

void NavButton::setIconSize(const QSize &iconSize)
{
    if (this->iconSize != iconSize) {
        this->iconSize = iconSize;
        this->update();
    }
}

void NavButton::setIconNormal(const QPixmap &iconNormal)
{
    this->iconNormal = iconNormal;
    this->update();
}

void NavButton::setIconHover(const QPixmap &iconHover)
{
    this->iconHover = iconHover;
    this->update();
}

void NavButton::setIconCheck(const QPixmap &iconCheck)
{
    this->iconCheck = iconCheck;
    this->update();
}

void NavButton::setShowLine(bool showLine)
{
    if (this->showLine != showLine) {
        this->showLine = showLine;
        this->update();
    }
}

void NavButton::setLineSpace(int lineSpace)
{
    if (this->lineSpace != lineSpace) {
        this->lineSpace = lineSpace;
        this->update();
    }
}

//设置线条宽度
void NavButton::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void NavButton::setLinePosition(const NavButton::LinePosition &linePosition)
{
    if (this->linePosition != linePosition) {
        this->linePosition = linePosition;
        this->update();
    }
}

//设置线条颜色
void NavButton::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void NavButton::setNormalBgColor(const QColor &normalBgColor)
{
    if (this->normalBgColor != normalBgColor) {
        this->normalBgColor = normalBgColor;
        this->update();
    }
}

void NavButton::setHoverBgColor(const QColor &hoverBgColor)
{
    if (this->hoverBgColor != hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        this->update();
    }
}

void NavButton::setCheckBgColor(const QColor &checkBgColor)
{
    if (this->checkBgColor != checkBgColor) {
        this->checkBgColor = checkBgColor;
        this->update();
    }
}

void NavButton::setNormalTextColor(const QColor &normalTextColor)
{
    if (this->normalTextColor != normalTextColor) {
        this->normalTextColor = normalTextColor;
        this->update();
    }
}

void NavButton::setHoverTextColor(const QColor &hoverTextColor)
{
    if (this->hoverTextColor != hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        this->update();
    }
}

void NavButton::setCheckTextColor(const QColor &checkTextColor)
{
    if (this->checkTextColor != checkTextColor) {
        this->checkTextColor = checkTextColor;
        this->update();
    }
}

void NavButton::setNormalBgBrush(const QBrush &normalBgBrush)
{
    if (this->normalBgBrush != normalBgBrush) {
        this->normalBgBrush = normalBgBrush;
        this->update();
    }
}

void NavButton::setHoverBgBrush(const QBrush &hoverBgBrush)
{
    if (this->hoverBgBrush != hoverBgBrush) {
        this->hoverBgBrush = hoverBgBrush;
        this->update();
    }
}

void NavButton::setCheckBgBrush(const QBrush &checkBgBrush)
{
    if (this->checkBgBrush != checkBgBrush) {
        this->checkBgBrush = checkBgBrush;
        this->update();
    }
}
