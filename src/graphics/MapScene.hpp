#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include <QTransform>
#include <QGraphicsView>
#include "../math/FnMath.hpp"

static const QRectF MT_SCENE_RECT = QRectF(-1690.0, -1690.0, 3380.0, 3380.0);
static const QSize  MT_VIEW_RECT = QSize(200.0, 200.0);

class MapScene
{
public:

    static MapScene* instance();

    static void cleanup();

    static QTransform transformFromScene(const QRectF& zone);

    static QTransform transformToScene(const QRectF& zone);

    static qreal azimuth(const QPointF& coord);

    static QRectF sceneViewRect(QGraphicsView* grView);

    void setGraphicsView(QGraphicsView* view);

    QPointF mapToScene(const QPoint& point);

    QRectF mapToScene(const QRect& rect);

    QPoint mapFromScene(const QPointF& point);

protected:

    MapScene();
    ~MapScene();

private:
    static MapScene* _instance;

    QGraphicsView*  m_graphicsView;
};

#endif // MAP_SCENE_H
