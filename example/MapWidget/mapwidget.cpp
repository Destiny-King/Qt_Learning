#include "mapwidget.h"
#include <QGraphicsScene>
#include <QSlider>
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <math.h>

MapWidget::MapWidget()
{
    readMap();

    zoom = 50;

    int width = map.width();
    int height = map.height();
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(-width / 2,-height / 2,width ,height);
    setScene(scene);
    setCacheMode(CacheBackground);

    //用于地图缩放的滑动条
    QSlider *slider = new QSlider;
    slider->setOrientation(Qt::Vertical);
    slider->setRange(1,100);
    slider->setTickInterval(10);
    slider->setValue(50);
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(slotZoom(int)));

    QLabel *zoominLabel = new QLabel;
    zoominLabel->setScaledContents(true);
    zoominLabel->setPixmap(QPixmap(":/images/zoomin.png"));

    QLabel *zoomoutLabel = new QLabel;
    zoomoutLabel->setScaledContents(true);
    zoomoutLabel->setPixmap(QPixmap(":/images/zoomout.png"));

    //坐标值显示区
    QLabel *label1 = new QLabel(tr("GraphicsView:"));
    viewGoord = new QLabel;
    QLabel *label2 = new QLabel(tr("GraphicsScene:"));
    sceneGoord = new QLabel;
    QLabel *label3 = new QLabel(tr("map:"));
    mapGoord = new QLabel;

    //坐标显示区布局
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(label1,0,0);
    gridLayout->addWidget(viewGoord,0,1);
    gridLayout->addWidget(label2,1,0);
    gridLayout->addWidget(sceneGoord,1,1);
    gridLayout->addWidget(label3,2,0);
    gridLayout->addWidget(mapGoord,2,1);
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    QFrame *coordFrame = new QFrame;
    coordFrame->setLayout(gridLayout);

    //缩放控制子布局
    QVBoxLayout *zoomLayout = new QVBoxLayout;
    zoomLayout->addWidget(zoominLabel);
    zoomLayout->addWidget(slider);
    zoomLayout->addWidget(zoomoutLabel);

    //坐标显示区域布局
    QVBoxLayout *coordLayout = new QVBoxLayout;
    coordLayout->addWidget(coordFrame);
    coordLayout->addStretch();

    //主布局
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(zoomLayout);
    mainLayout->addLayout(coordLayout);
    mainLayout->addStretch();
    mainLayout->setMargin(30);
    mainLayout->setSpacing(10);
    setLayout(mainLayout);

    setWindowTitle("Map Widget");
    setMinimumSize(600,400);
}

//读取地图信息
void MapWidget::readMap()
{
    QString mapName;
    QFile mapFile("maps.txt");
    int ok = mapFile.open(QIODevice::ReadOnly);
    if(ok){
        //分别读取地图的名称和四个经纬度信息
        QTextStream ts(&mapFile);
        if(!ts.atEnd()){
            ts >> mapName;
            ts >>x1>>y1>>x2>>y2;
        }
    }
    map.load(mapName);
}

QPointF MapWidget::mapToMap(QPointF p)
{
    QPointF latLon;
    qreal w = sceneRect().width();
    qreal h = sceneRect().height();

    qreal lat = x1 + ((w / 2 + p.x()) * abs(x1 - x2) / w);
    qreal lon = y1 - ((h / 2 + p.y()) * abs(y1 - y2) / h);
    latLon.setX(lat);
    latLon.setY(lon);

    return latLon;
}

//地图缩放
void MapWidget::slotZoom(int value)
{
    qreal s;
    if(value > zoom){
        s = pow(1.01,(value - zoom));
    }else{
        s = pow(1 / 1.01,(zoom - value));
    }
    scale(s,s);
    zoom = value;
}

void MapWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(int(sceneRect().left()),int(sceneRect().top()),map);
}

void MapWidget::mouseMoveEvent(QMouseEvent *event)
{
    //QGraphicsView 坐标
    QPoint viewPoint = event->pos();
    viewGoord->setText(QString::number(viewPoint.x()) + "," + QString::number(viewPoint.y()));

    //QGraphicsScene 坐标
    QPointF scenePoint = mapToScene(viewPoint);
    sceneGoord->setText(QString::number(scenePoint.x()) + "," + QString::number(scenePoint.y()));

    //地图坐标(经、纬度值)
    QPointF latLon = mapToMap(scenePoint);
    mapGoord->setText(QString::number(latLon.x()) + "," + QString::number(latLon.y()));
}
