#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QGraphicsView>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>

class MapWidget : public QGraphicsView
{
    Q_OBJECT
public:
    MapWidget();

    //读取地图信息
    void readMap();
    //用于实现场景坐标系与地图坐标之间的映射，以获得某点的经纬度值
    QPointF mapToMap(QPointF);

public slots:
    void slotZoom(int);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);            //完成地图显示的功能
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPixmap map;
    qreal zoom;
    QLabel *viewGoord;
    QLabel *sceneGoord;
    QLabel *mapGoord;
    double x1,y1;
    double x2,y2;
};

#endif // MAPWIDGET_H
