#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include "maneuver_gritem.h"

//namespace trainer {

ManeuverGraphicsItem::ManeuverGraphicsItem(QGraphicsItem * parent) : QAbstractGraphicsShapeItem(parent)
{
    m_editMode = false;
    setZValue(0.1);
}

ManeuverGraphicsItem::~ManeuverGraphicsItem()
{
    cleanScene();
}

QRectF ManeuverGraphicsItem::boundingRect () const
{
      return m_boundingRect;
}

//void ManeuverGraphicsItem::setLinear(const QPointF& startPoint, const QPointF& endPoint)
//{
//      m_polygon.clear();
//      m_polygon.reserve(2);
//      m_polygon.append(startPoint);
//      m_polygon.append(endPoint);
//      m_boundingRect.setTopLeft(startPoint);
//      m_boundingRect.setBottomRight(endPoint);
//      m_boundingRect.normalized();
//      prepareGeometryChange();
//}

void ManeuverGraphicsItem::addLinear(const QPointF& startPoint, const QPointF& endPoint)
{
    QRectF boundRect;
    m_polygon.append(startPoint);
    m_polygon.append(endPoint);
//    qDebug() << m_polygon;
    boundRect.setTopLeft(startPoint);
    boundRect.setBottomRight(endPoint);
    m_boundingRect |= boundRect;
    m_boundingRect.normalized();
    prepareGeometryChange();
}

void ManeuverGraphicsItem::addArc(const QPointF& startPoint, const QPointF& centrCircle, qreal startCourse, qreal endCourse, qreal radius,
                                                                      CourseChange sign)
{
    m_polygon += createArcPolygonF ( startPoint, startCourse, endCourse, radius, sign );
    m_boundingRect |= QRectF ( centrCircle.x() - radius, centrCircle.y() - radius, 2.0 * radius, 2.0 * radius );
    prepareGeometryChange();
}

//void ManeuverGraphicsItem::setArc(const QPointF& startPoint, const QPointF& centrCircle, qreal startCourse, qreal endCourse, qreal radius, CourseChange sign)
//{
//      m_polygon.clear();
//      m_polygon = createArcPolygonF(startPoint, startCourse, endCourse, radius, sign);
//      m_boundingRect = QRectF(centrCircle.x()-radius, centrCircle.y()-radius, 2.0*radius, 2.0*radius);
//      prepareGeometryChange();
//}

void ManeuverGraphicsItem::clearItem()
{
    m_polygon.clear();
    m_boundingRect = QRectF();
}

void ManeuverGraphicsItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * , QWidget * )
{
      if(!painter) return;

      painter->setRenderHint(QPainter::Antialiasing, false);
      painter->setPen( QPen( QBrush( QColor(128, 128, 128) ), 0, Qt::SolidLine ) );
      painter->setBrush(Qt::NoBrush);
      painter->drawPolyline(m_polygon);
      if(m_editMode)
      {
        painter->setPen( QPen( QBrush( QColor(196, 196, 0) ), 0, Qt::SolidLine ) );
        painter->drawRect( boundingRect() );
      }
}

bool ManeuverGraphicsItem::cleanScene()
{
    QGraphicsScene* itemScene = scene();
    if(itemScene)
    {
        itemScene->removeItem ( this );

        itemScene->update();
//        qDebug () << "Maneuver clean Scene";
        return true;
    }
    return false;
}

//} // namespace trainer
