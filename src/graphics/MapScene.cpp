#include "./MapScene.hpp"

MapScene* MapScene::_instance = NULL;

MapScene* MapScene::instance()
{
    if(_instance == NULL)
        _instance = new MapScene;

    return _instance;
}

void MapScene::cleanup()
{
    if(_instance != NULL)
    {
        delete _instance;
        _instance = NULL;
    }
}

MapScene::MapScene()
{
    m_graphicsView = NULL;
}

MapScene::~MapScene()
{
     m_graphicsView = NULL;
}

QTransform MapScene::transformFromScene(const QRectF& zone)
{
    qreal xscale = zone.width() / MT_SCENE_RECT.width();
    qreal yscale = zone.height() / MT_SCENE_RECT.height();

    QTransform transform;
    transform.translate( zone.center().x(),  zone.center().y() );
    transform.scale(xscale, yscale);
    transform.rotate(-90.0);

    return transform;
}

QTransform MapScene::transformToScene(const QRectF& zone)
{
    qreal xscale = MT_SCENE_RECT.width() / zone.width();
    qreal yscale = MT_SCENE_RECT.height() / zone.height();

    QTransform transform;
    transform.rotate(90.0);
    transform.scale(xscale, yscale);
    transform.translate( -zone.width()/2,  -zone.height()/2 );

    return transform;
}


QRectF MapScene::sceneViewRect(QGraphicsView* grView)
{
    if( !grView && !grView->scene() ) return QRectF();

    QRect rect = grView->rect();

    QPointF point1 = grView->mapToScene( rect.topLeft() );
    QPointF point2 = grView->mapToScene( rect.bottomRight() );

    return QRectF(point1, point2);
}

qreal MapScene::azimuth(const QPointF& coord)
{
    qreal x = coord.x();
    qreal y = coord.y();
    qreal c = sqrt(x*x+y*y);

    qreal angle = 0.0;

    angle = MathFunctions::radianToDegree(acos(x/c));

    if(y < 0.0)
        angle = 360.0 - MathFunctions::radianToDegree(acos(x/c));

    return angle;
}

void MapScene::setGraphicsView(QGraphicsView* view)
{
    m_graphicsView = view;
}

QPointF MapScene::mapToScene(const QPoint& point)
{
    if(!m_graphicsView) return QPointF();

    return m_graphicsView->mapToScene(point);
}

QRectF MapScene::mapToScene(const QRect& rect)
{
    if(!m_graphicsView) return QRectF();

    QPointF point1 = m_graphicsView->mapToScene( rect.topLeft() );
    QPointF point2 = m_graphicsView->mapToScene( rect.bottomRight() );

    return QRectF(point1, point2).normalized();
}

QPoint MapScene::mapFromScene(const QPointF& point)
{
    if(!m_graphicsView) return QPoint();

    return m_graphicsView->mapFromScene(point);
}
