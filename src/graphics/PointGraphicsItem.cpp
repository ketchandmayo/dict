#include "./PointGraphicsItem.hpp"
#include <QPainter>
#include <QDebug>
#include <QObject>
#include "./MapScene.hpp"
#include <QMenu>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include "../widgets/GraphicsScene_PopupMenu.h"

PointGraphicsItem::PointGraphicsItem ( QGraphicsItem* parent )
    : QGraphicsObject ( parent )
{
    m_pointId = -1;

    m_active = false;

    setZValue ( 1.0 );

    setFlag ( QGraphicsItem::ItemIgnoresTransformations, true );
}

PointGraphicsItem::~PointGraphicsItem()
{

}

QRectF PointGraphicsItem::boundingRect () const
{
    return QRectF (-10.0, -10.0, 20.0, 20.0);
}

void PointGraphicsItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    Q_UNUSED (option);
    Q_UNUSED (widget);

    QColor penColor;

    penColor.setRgb ( 255, 255, 0 );

    painter->setPen ( QPen (QBrush ( QColor ( 255, 255, 0 ) ), 0 ) );

    if(m_active)
        painter->setBrush ( QBrush ( Qt::yellow ) );
    else
        painter->setBrush ( Qt::NoBrush );

    painter->drawRect (boundingRect());
}

void PointGraphicsItem::setPosition ( const QPointF& pos )
{
    m_position = pos;

    setPos (m_position);
}

const QPointF& PointGraphicsItem::position () const
{
    return m_position;
}

void PointGraphicsItem::setPointId ( int id )
{
    m_pointId = id;
}

int PointGraphicsItem::pointID () const
{
    return m_pointId;
}

void PointGraphicsItem::setTimeLabel ( Time time )
{
    m_timeLabel = time;
}

Time PointGraphicsItem::timeLabel () const
{
    return m_timeLabel;
}

void PointGraphicsItem::setActivate ( bool active )
{
    m_active = active;        
}

bool PointGraphicsItem::isActivate () const
{
    return m_active;
}

//void PointGraphicsItem::setTrassType ( TrassType type )
//{
//    m_trassType = type;
//}

//TrassType PointGraphicsItem::trassType () const
//{
//    return m_trassType;
//}

void PointGraphicsItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
    if ( m_active )
    {
        setPosition ( event->scenePos() );
        emit sigUpdateTrass();
    }
}

void PointGraphicsItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    if ( event->button() == Qt::LeftButton )
        m_active = true;
}

void PointGraphicsItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    m_active = false;
}

void PointGraphicsItem::contextMenuEvent ( QGraphicsSceneContextMenuEvent * event )
{
    GraphicsScenePopupMenu::instance()->showMenu ( GraphicsScenePopupMenu::TrassPointMenu, event->screenPos(), m_pointId );
}
