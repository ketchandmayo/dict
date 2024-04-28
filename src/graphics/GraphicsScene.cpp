#include "./GraphicsScene.hpp"
#include <QPainter>
#include <QGraphicsView>
#include <QSize>
#include <QTransform>
#include <math.h>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include "./PointGraphicsItem.hpp"
#include "./MapScene.hpp"
#include <QDebug>


GraphicsScene::GraphicsScene(QObject* parent) : QGraphicsScene(parent)
{
    setSceneRect(MT_SCENE_RECT);
    m_scale = 3200.0;
    m_azimuth = 0;
    m_vizibleAzimuth = false;
}

GraphicsScene::~GraphicsScene()
{

}

void GraphicsScene::drawLinear(QPainter* painter)
{
    if(views().isEmpty()) return;

    QRectF sceneVisibleRect = MapScene::sceneViewRect(views()[0]);
    qreal xscale =  sceneVisibleRect.width() / views()[0]->rect().height();
    qreal yscale =  sceneVisibleRect.height() / views()[0]->rect().width();
    QPointF pointTopLeft = views()[0]->mapToScene(0.0, 0.0);
    QPointF pointBottomLeft = views()[0]->mapToScene(views()[0]->rect().bottomLeft());

    QTransform b_matrix;
    QRectF rectBottom, rectLeft;
    int step = (int)( m_scale / 4.0 );
    int count = 1600 / step;

    for(int i = -count; i < count; ++i)
    {
        rectBottom = QRectF(pointBottomLeft.x(), i*step, -20.0*xscale , step);
        rectLeft = QRectF(i*step, pointTopLeft.y(), step, 15.0*yscale);

        painter->setPen(QPen(QColor(192, 192, 192), 0,  Qt::SolidLine) );
        if(i%2 == 0)
            painter->setBrush(QBrush(QColor(192, 192, 192),  Qt::SolidPattern) );
        else
            painter->setBrush(QBrush(QColor(0, 0, 0),  Qt::SolidPattern) );

        painter->drawRect(rectBottom);
        painter->drawRect(rectLeft);
    }

    QFontMetrics font_metr(views()[0]->font());
    QSize text_size;
    QRect text_rect;
    qreal coord = 0.0;

    b_matrix = painter->transform();

    painter->save();
    painter->resetTransform();

    painter->setPen(QPen(QColor(192, 192, 192), 0,  Qt::SolidLine) );

    for(int i = -count; i <= count; ++i)
    {
        coord = i*step;

        text_size = font_metr.size( Qt::TextSingleLine, QString::number(coord)+"km");
        text_rect = QRect(QPoint(0, 0), text_size);

        painter->translate( b_matrix.map(QPointF(rectBottom.x()-35*xscale, coord)).toPoint());
        painter->fillRect(text_rect, Qt::black);
        painter->drawText( text_rect, Qt::AlignRight, QString::number(coord)+"km" );
        painter->resetTransform();

        painter->translate(b_matrix.map(QPointF(coord, pointTopLeft.y()-20*xscale)).toPoint());
        painter->rotate(-90);
        painter->fillRect(text_rect, Qt::black);
        painter->drawText( text_rect, Qt::AlignRight, QString::number(coord)+"km" );
        painter->resetTransform();

    }
    painter->restore();
}

void GraphicsScene::drawAzimuthGrid(QPainter* painter)
{
      int count = 1600 / (int)(m_scale/8.0);
      qreal coord = 0.0;
      for(int i = 1; i < count; ++i)
      {
          coord = m_scale / 8.0 * (qreal)i;
          painter->drawEllipse(-coord, -coord, 2.0 * coord, 2.0 * coord);
      }
      qreal grad = 0.0;
      for( qreal i = 30.0; i < 360.0; i += 30.0 )
      {
          grad = i*M_PI/180.0;
          coord = m_scale/8.0;
          painter->drawLine( QPointF(coord*cos(grad), coord*sin(grad)) , QPointF(1600*cos(grad), 1600*sin(grad)) );
      }
}

void GraphicsScene::drawCoordGrid(QPainter* painter)
{
    qreal step = m_scale/16;
    int count = 1600 / (int)step;
    qreal coord = 0.0;
    for(int i = -count; i <= count; ++i)
    {
        coord = step*i;
        if(i % 4 == 0)
            painter->setPen(QPen(QBrush(QColor(128, 128, 128)), 0, Qt::DashLine));
        else
            painter->setPen(QPen(QBrush(QColor(64, 64, 64)), 0, Qt::DotLine));
        painter->drawLine(QPointF(-1600.0, coord), QPointF(1600.0, coord));
        painter->drawLine(QPointF(coord, -1600.0), QPointF(coord, 1600.0));
    }
}

void GraphicsScene::drawBackground( QPainter * painter, const QRectF & )
{
    QRectF s_rect = QRectF(sceneRect().x()+90, sceneRect().y()+90,
                            sceneRect().width()-180, sceneRect().height()-180);

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setClipRect(sceneRect());
    painter->fillRect( sceneRect(), QColor(0, 0, 0) );
    painter->setBrush( Qt::NoBrush );
    painter->setPen( QPen ( QColor( 196, 196, 196 ), 0 ) );
    painter->drawRect( s_rect );
    painter->drawLine( QPointF( 0.0, s_rect.x() ), QPointF( 0.0, s_rect.x() + s_rect.width() ) );
    painter->drawLine( QPointF( s_rect.y(), 0.0 ), QPointF( s_rect.y() + s_rect.height(), 0.0 ) );
    painter->setPen( QPen ( QColor( 196, 196, 196 ), 0 ) );
    painter->drawEllipse( -1600.0, -1600.0, 3200.0, 3200.0 );

    painter->setPen( QPen ( QColor( 128, 128, 128 ), 0, Qt::DashLine ) );
    drawCoordGrid(painter);
}

void GraphicsScene::drawForeground ( QPainter * painter, const QRectF & )
{
    if ( views().isEmpty() ) return;

    painter->setRenderHint(QPainter::Antialiasing, false);

    if(m_vizibleAzimuth)
    {
        painter->setPen(QPen(QColor(192, 192, 192), 0,  Qt::DotLine) );
        painter->drawLine(QPointF(0.0, 0.0), m_azimuthPos);

        QTransform transform = painter->transform();
        painter->save();
        painter->resetTransform();
        QFontMetrics font_metr(views()[0]->font());
        QSize text_size;
        QRect text_rect;

        text_size = font_metr.size( Qt::TextSingleLine, "A "+QString::number( m_azimuth )+QObject::tr( "°" ) );
        text_rect = QRect( QPoint(0, 0), text_size );

        painter->translate( transform.map(m_azimuthPos).toPoint() );
        painter->fillRect(text_rect, Qt::black );
        painter->drawText( text_rect, Qt::AlignRight, "A "+QString::number( m_azimuth )+QObject::tr( "°" ) );
        painter->resetTransform();

        painter->restore();
    }
    drawLinear(painter);
}

bool GraphicsScene::event ( QEvent * event )
{
    QGraphicsSceneMouseEvent* mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);

    if(mouseEvent)
    {
        switch(event->type())
        {
            case QEvent::GraphicsSceneMousePress:
            {
                QPointF coord = mouseEvent->scenePos();
                Qt::MouseButton mouseButton = mouseEvent->button();

                emit sigSceneMousePress ( coord, mouseButton );
            }
            break;

            case QEvent::GraphicsSceneMouseMove:
            {
                QPointF coord = mouseEvent->scenePos();

                emit sigSceneMouseMove(coord);
            }
            break;

            case QEvent::GraphicsSceneMouseRelease:
            {
                QPointF coord = mouseEvent->scenePos();
                Qt::MouseButton mouseButton = mouseEvent->button();

                emit sigSceneMouseRelease(coord, mouseButton);
            }
            break;

            case QEvent::GraphicsSceneMouseDoubleClick:
               emit sigSceneMouseDoubleClick();
            break;

            default:
                break;
        }
    }

    return QGraphicsScene::event(event);
}
