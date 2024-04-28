#ifndef POINT_GRAPHICSITEM_H
#define POINT_GRAPHICSITEM_H

#include <QGraphicsObject>
#include <QTransform>
#include "../math/Position.hpp"

class PointGraphicsItem : public QGraphicsObject
{

    Q_OBJECT

public:

    explicit PointGraphicsItem ( QGraphicsItem* parent = 0 );

    virtual ~PointGraphicsItem();

    virtual QRectF boundingRect () const;

    virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    void setPosition (const QPointF& pos);

    const QPointF& position () const;

    void setPointId ( int id );

    int pointID () const;

    void setTimeLabel (Time time);

    Time timeLabel() const;

    void setActivate (bool active);

    bool isActivate () const;

signals:
    void sigUpdateTrass();

    void sigDeletePoint(int idPoint);

public slots:

protected:

    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );

    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );

    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );

    virtual void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event );

private:

    QPointF     m_position;
    int         m_pointId;
    Time        m_timeLabel;
    bool        m_active;

};

#endif // POINT_GRAPHICSITEM_H
