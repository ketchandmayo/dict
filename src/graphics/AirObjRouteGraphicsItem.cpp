#include "./AirObjRouteGraphicsItem.hpp"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QMenu>
#include <QEvent>
#include <QGraphicsSceneContextMenuEvent>
#include "../widgets/GraphicsScene_PopupMenu.h"


AirObjectRouteGraphicsObject::AirObjectRouteGraphicsObject (QGraphicsItem *parent) :
    QGraphicsObject (parent)
{
    m_trassId = 0;
    m_bold = 0;
    m_maxRadius = 50.0;
    m_create = true;

    connect(GraphicsScenePopupMenu::instance (), SIGNAL (sigDeletePoint(int)), this, SLOT(deletePosition(int)));
    connect(GraphicsScenePopupMenu::instance (), SIGNAL (sigInsertPoint(const QPointF&)), this, SLOT(insertPosition(const QPointF&)));
}

QRectF AirObjectRouteGraphicsObject::boundingRect () const
{
    qreal minX = 0.0;
    qreal minY = 0.0;
    qreal maxX = 0.0;
    qreal maxY = 0.0;

    foreach(const PointGraphicsItem* point, m_points)
    {
        minX = qMin( minX, point->position().x() );
        minY = qMin( minY, point->position().y() );

        maxX = qMax( maxX, point->position().x() );
        maxY = qMax( maxY, point->position().y() );
    }

    return QRectF( QPointF( minX, minY ), QPointF( maxX, maxY ) ).normalized();
}

QPainterPath AirObjectRouteGraphicsObject::shape() const
{
    return m_shape;
}

void AirObjectRouteGraphicsObject::paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    for (int i = 0; i < m_points.count(); i++)
    {
        if (i == 0) continue;

        QPointF nextCoord = m_points [i]->position();
        QPointF prevCoord = m_points [i-1]->position();

        painter->setPen (QPen (QBrush (Qt::white), 0, Qt::DotLine) );
        painter->drawLine (prevCoord, nextCoord);
    }

    painter->setPen (QPen (QBrush (Qt::white), 0) );
    painter->drawPolyline (m_trassImage);

    painter->setPen (QPen (QBrush (Qt::red), 0, Qt::SolidLine) );
    painter->drawPath(shape());
}

void AirObjectRouteGraphicsObject::addPosition (const QPointF& coord)
{
    if(!m_create) return;

    PointGraphicsItem* point = new PointGraphicsItem(this);
    point->setPointId( m_points.count() );
    point->setPosition(coord);
    m_points.append( point );
    connect(point, SIGNAL(sigUpdateTrass()), this, SLOT(updateTrass()));
    emit sigAddPointToScene(point);
    updateTrass ();
}

void AirObjectRouteGraphicsObject::insertPosition(const QPointF& pos)
{
    if ( m_points.count () >= 3 )
    {
        for (int i = 0; i < m_points.count () - 1; ++i)
        {
            QPointF point1 = m_points [i]->position();
            QPointF point2 = m_points [i+1]->position();
            QPainterPath path = lineShape(point1, point2);

            if( path.contains(pos) )
            {
                PointGraphicsItem* point = new PointGraphicsItem(this);
                point->setPosition(pos);
                point->setPointId(i+1);
                m_points.insert(i+1, point);
                connect(point, SIGNAL(sigUpdateTrass()), this, SLOT(updateTrass()));
                emit sigAddPointToScene(point);
                break;
            }
        }
    }

    updateTrass ();
}

void AirObjectRouteGraphicsObject::deletePosition(int pointId)
{
//    qDebug() << "deletePosition" << pointId;
    if ( pointId > -1 && pointId < m_points.count() )
    {
        PointGraphicsItem* point = m_points [ pointId ];
        m_points.remove ( pointId );
        sigDelPointFromScene ( point );
        delete point;
    }

    updateTrass ();
}

void AirObjectRouteGraphicsObject::setMaximumRadius (double radius)
{
    m_maxRadius = radius;
    updateTrass();
}

void AirObjectRouteGraphicsObject::updateTrass ()
{
    m_trassImage.clear();

    m_shape = QPainterPath();

    if ( m_points.isEmpty()) return;

    for (int i = 0; i < m_points.count(); ++i)
    {
        if ( m_points[i]->pointID() != i )
            m_points[i]->setPointId (i);
    }

    m_trassImage.append (m_points.first()->position());

    if ( m_points.count () >= 3 )
    {
        int count = 1;

        for (int i = 0; i < m_points.count () - 2; ++i)
        {
            QPointF point1 = m_points [i]->position();
            QPointF point2 = m_points [i+1]->position();
            QPointF point3 = m_points [i+2]->position();

            QPolygonF arc = arcBetweenLines ( point1, point2, point3, m_maxRadius );

            foreach ( const QPointF& point, arc )
                m_trassImage.append ( point );

            count++;
        }
    }

    m_trassImage.append ( m_points.last()->position() );

    m_shape = polylineShape ( m_trassImage, 5.0 );

    update();
}

void AirObjectRouteGraphicsObject::setTrassId ( uint trassID )
{
    m_trassId = trassID;
    m_name = QString ("N%1").arg ( m_trassId );
}

uint AirObjectRouteGraphicsObject::trassId () const
{
    return m_trassId;
}

void AirObjectRouteGraphicsObject::setBold ( bool bold )
{
    m_bold = bold;
}

void AirObjectRouteGraphicsObject::contextMenuEvent (QGraphicsSceneContextMenuEvent * event)
{
    GraphicsScenePopupMenu::instance()->showMenu(GraphicsScenePopupMenu::TrassMenu,  event->screenPos(), QVariant(event->scenePos()) );
}
