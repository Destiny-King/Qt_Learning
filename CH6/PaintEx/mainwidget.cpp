#include "mainwidget.h"
#include <QColor>
#include <QColorDialog>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    paintArea = new PaintArea;

    //形状选择下拉框
    shapeLabel = new QLabel(tr("形状:"));
    shapeComboBox = new QComboBox;
    //addItem()函数可以仅插入文本，也可同时插入与文本相对应的具体数据
    shapeComboBox->addItem(tr("Line"),PaintArea::Line);
    shapeComboBox->addItem(tr("Rectangle"),PaintArea::Rectangle);
    shapeComboBox->addItem(tr("RoundedRect"),PaintArea::RoundRect);
    shapeComboBox->addItem(tr("Ellipse"),PaintArea::Ellipse);
    shapeComboBox->addItem(tr("Polygon"),PaintArea::Polygon);
    shapeComboBox->addItem(tr("Polyline"),PaintArea::Polyline);
    shapeComboBox->addItem(tr("Points"),PaintArea::Points);
    shapeComboBox->addItem(tr("Arc"),PaintArea::Arc);
    shapeComboBox->addItem(tr("Path"),PaintArea::Path);
    shapeComboBox->addItem(tr("Text"),PaintArea::Text);
    shapeComboBox->addItem(tr("Pixmap"),PaintArea::Pixmap);
    connect(shapeComboBox,SIGNAL(activated(int)),this,SLOT(ShowShape(int)));

    //画笔颜色选择控件
    penColorLabel =new QLabel(tr("画笔颜色："));
    penColorFrame =new QFrame;
    penColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    penColorFrame->setAutoFillBackground(true);
    penColorFrame->setPalette(QPalette(Qt::blue));
    penColorBtn =new QPushButton(tr("更改"));
    connect(penColorBtn,SIGNAL(clicked()),this,SLOT(ShowPenColor()));

    //画笔线宽选择控件
    penWidthLabel =new QLabel(tr("画笔线宽："));
    penWidthSpinBox =new QSpinBox;
    penWidthSpinBox->setRange(0,20);
    connect(penWidthSpinBox,SIGNAL(valueChanged(int)),this,SLOT (ShowPenWidth(int)));

    //画笔风格选择下拉列表框
    penStyleLabel =new QLabel(tr("画笔风格："));
    penStyleComboBox =new QComboBox;
    //选用不同的参数，对应画笔的不同风格
    penStyleComboBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("DashDotDotLine"),static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem(tr("CustomDashLine"),static_cast<int>(Qt::CustomDashLine));
    connect(penStyleComboBox,SIGNAL(activated(int)),this,SLOT (ShowPenStyle(int)));

    //画笔顶端风格选择下拉列表框
    penCapLabel =new QLabel(tr("画笔顶帽："));
    penCapComboBox =new QComboBox;
    penCapComboBox->addItem(tr("SquareCap"),Qt::SquareCap);
    penCapComboBox->addItem(tr("FlatCap"),Qt::FlatCap);
    penCapComboBox->addItem(tr("RoundCap"),Qt::RoundCap);
    connect(penCapComboBox,SIGNAL(activated(int)),this,SLOT(ShowPenCap (int)));

    //画笔连接点风格选择下拉列表框
    penJoinLabel =new QLabel(tr("画笔连接点："));
    penJoinComboBox =new QComboBox;
    penJoinComboBox->addItem(tr("BevelJoin"),Qt::BevelJoin);
    penJoinComboBox->addItem(tr("MiterJoin"),Qt::MiterJoin);
    penJoinComboBox->addItem(tr("RoundJoin"),Qt::RoundJoin);
    connect(penJoinComboBox,SIGNAL(activated(int)),this,SLOT(ShowPenJoin (int)));

    //填充模式选择下拉列表框
    fillRuleLabel =new QLabel(tr("填充模式："));
    fillRuleComboBox =new QComboBox;
    fillRuleComboBox->addItem(tr("Odd Even"),Qt::OddEvenFill);
    fillRuleComboBox->addItem(tr("Winding"),Qt::WindingFill);
    connect(fillRuleComboBox,SIGNAL(activated(int)),this,SLOT (ShowFillRule()));

    //铺展效果选择下拉列表框
    spreadLabel =new QLabel(tr("铺展效果："));
    spreadComboBox =new QComboBox;
    spreadComboBox->addItem(tr("PadSpread"),QGradient::PadSpread);
    spreadComboBox->addItem(tr("RepeatSpread"),QGradient::RepeatSpread);
    spreadComboBox->addItem(tr("ReflectSpread"),QGradient:: ReflectSpread);
    connect(spreadComboBox,SIGNAL(activated(int)),this,SLOT (ShowSpreadStyle()));

    //画刷颜色选择控件
    brushColorLabel =new QLabel(tr("画刷颜色："));
    brushColorFrame =new QFrame;
    brushColorFrame->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    brushColorFrame->setAutoFillBackground(true);
    brushColorFrame->setPalette(QPalette(Qt::green));
    brushColorBtn =new QPushButton(tr("更改"));
    connect(brushColorBtn,SIGNAL(clicked()),this,SLOT (ShowBrushColor()));

    //画刷风格选择下拉列表框
    brushStyleLabel =new QLabel(tr("画刷风格："));
    brushStyleComboBox =new QComboBox;
    brushStyleComboBox->addItem(tr("SolidPattern"),static_cast<int>(Qt::SolidPattern));
    brushStyleComboBox->addItem(tr("Dense1Pattern"),static_cast<int>(Qt::Dense1Pattern));
    brushStyleComboBox->addItem(tr("Dense2Pattern"),static_cast<int>(Qt::Dense2Pattern));
    brushStyleComboBox->addItem(tr("Dense3Pattern"),static_cast<int>(Qt::Dense3Pattern));
    brushStyleComboBox->addItem(tr("Dense4Pattern"),static_cast<int>(Qt::Dense4Pattern));
    brushStyleComboBox->addItem(tr("Dense5Pattern"),static_cast<int>(Qt::Dense5Pattern));
    brushStyleComboBox->addItem(tr("Dense6Pattern"),static_cast<int>(Qt::Dense6Pattern));
    brushStyleComboBox->addItem(tr("Dense7Pattern"),static_cast<int>(Qt::Dense7Pattern));
    brushStyleComboBox->addItem(tr("HorPattern"),static_cast<int>(Qt::HorPattern));
    brushStyleComboBox->addItem(tr("VerPattern"),static_cast<int>(Qt::VerPattern));
    brushStyleComboBox->addItem(tr("CrossPattern"),static_cast<int>(Qt::CrossPattern));
    brushStyleComboBox->addItem(tr("BDiagPattern"),static_cast<int>(Qt::BDiagPattern));
    brushStyleComboBox->addItem(tr("FDiagPattern"),static_cast<int>(Qt::FDiagPattern));
    brushStyleComboBox->addItem(tr("DiagCrossPattern"),static_cast<int>(Qt:: DiagCrossPattern));
    brushStyleComboBox->addItem(tr("LinearGradientPattern"),static_cast<int>(Qt:: LinearGradientPattern));
    brushStyleComboBox->addItem(tr("ConicalGradientPattern"),static_cast<int>(Qt:: ConicalGradientPattern));
    brushStyleComboBox->addItem(tr("RadialGradientPattern"),static_cast<int>(Qt:: RadialGradientPattern));
    brushStyleComboBox->addItem(tr("TexturePattern"),static_cast<int>(Qt::TexturePattern));
    connect(brushStyleComboBox,SIGNAL(activated(int)),this,SLOT (ShowBrush(int)));

    //控制面板的布局
    rightLayout = new QGridLayout;
    rightLayout->addWidget(shapeLabel,0,0);
    rightLayout->addWidget(shapeComboBox,0,1);
    rightLayout->addWidget(penColorLabel,1,0);
    rightLayout->addWidget(penColorFrame,1,1);
    rightLayout->addWidget(penColorBtn,1,2);
    rightLayout->addWidget(penWidthLabel,2,0);
    rightLayout->addWidget(penWidthSpinBox,2,1);
    rightLayout->addWidget(penStyleLabel,3,0);
    rightLayout->addWidget(penStyleComboBox,3,1);
    rightLayout->addWidget(penCapLabel,4,0);
    rightLayout->addWidget(penCapComboBox,4,1);
    rightLayout->addWidget(penJoinLabel,5,0);
    rightLayout->addWidget(penJoinComboBox,5,1);
    rightLayout->addWidget(fillRuleLabel,6,0);
    rightLayout->addWidget(fillRuleComboBox,6,1);
    rightLayout->addWidget(spreadLabel,7,0);
    rightLayout->addWidget(spreadComboBox,7,1);
    rightLayout->addWidget(brushColorLabel,8,0);
    rightLayout->addWidget(brushColorFrame,8,1);
    rightLayout->addWidget(brushColorBtn,8,2);
    rightLayout->addWidget(brushStyleLabel,9,0);
    rightLayout->addWidget(brushStyleComboBox,9,1);

    //整体的布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(paintArea);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(paintArea,1);
    mainLayout->setStretchFactor(rightLayout,0);

    //默认显示的图形
    ShowShape(shapeComboBox->currentIndex());
}

MainWidget::~MainWidget()
{
}

void MainWidget::ShowShape(int value)
{
    PaintArea::Shape shape = PaintArea::Shape(shapeComboBox->itemData(value,Qt::UserRole).toInt());
    paintArea->setShape(shape);
}

void MainWidget::ShowPenWidth(int value)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));
}

//获得与画笔相关的所有属性值
void MainWidget::ShowPenColor()
{
    QColor color = QColorDialog::getColor(Qt::blue);
    penColorFrame->setPalette(QPalette(color));
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(penCapComboBox->currentIndex(),Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(penJoinComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));
}

void MainWidget::ShowPenStyle(int styleValue)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(styleValue,Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(styleValue,Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(styleValue,Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));
}

void MainWidget::ShowPenCap(int capValue)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(capValue,Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(capValue,Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(capValue,Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));
}

void MainWidget::ShowPenJoin(int joinValue)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(joinValue,Qt::UserRole).toInt());
    Qt::PenCapStyle cap = Qt::PenCapStyle(penCapComboBox->itemData(joinValue,Qt::UserRole).toInt());
    Qt::PenJoinStyle join = Qt::PenJoinStyle(penJoinComboBox->itemData(joinValue,Qt::UserRole).toInt());
    paintArea->setPen(QPen(color,value,style,cap,join));
}

void MainWidget::ShowSpreadStyle()
{
    spread = QGradient::Spread(spreadComboBox->itemData(spreadComboBox->currentIndex(),Qt::UserRole).toInt());
}

void MainWidget::ShowFillRule()
{
    Qt::FillRule rule = Qt::FillRule(fillRuleComboBox->itemData(fillRuleComboBox->currentIndex(),Qt::UserRole).toInt());
    paintArea->setFillRule(rule);
}

void MainWidget::ShowBrushColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::blue));
    brushColorFrame->setPalette(QPalette(color));
    ShowBrush(brushStyleComboBox->currentIndex());
}

void MainWidget::ShowBrush(int value)
{
    QColor color = brushColorFrame->palette().color(QPalette::Window);
    Qt::BrushStyle style = Qt::BrushStyle(brushStyleComboBox->itemData(value,Qt::UserRole).toInt());
    if(style == Qt::LinearGradientPattern){
        QLinearGradient linearGradient(0,0,400,400);
        linearGradient.setColorAt(0.0,Qt::white);
        linearGradient.setColorAt(0.2,color);
        linearGradient.setColorAt(1.0,Qt::black);
        linearGradient.setSpread(spread);
        paintArea->setBrush(linearGradient);
    }else if(style == Qt::ConicalGradientPattern){
        QConicalGradient conicalGradient(200,200,30);
        conicalGradient.setColorAt(0.0,Qt::white);
        conicalGradient.setColorAt(0.2,color);
        conicalGradient.setColorAt(1.0,Qt::black);
        paintArea->setBrush(conicalGradient);
    }else if(style == Qt::TexturePattern){
        paintArea->setBrush(QBrush(QPixmap(":/images/butterfly.png")));\
    }else{
        paintArea->setBrush(QBrush(color,style));
    }
}
