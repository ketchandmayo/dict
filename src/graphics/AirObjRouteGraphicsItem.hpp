#pragma once

#include <QObject>
#include <QTimer>
#include <QGraphicsObject>
#include "../math/Position.hpp"
#include "PointGraphicsItem.hpp"

class AirObjectRouteGraphicsObject : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit AirObjectRouteGraphicsObject (QGraphicsItem *parent = 0);
    virtual QRectF boundingRect () const;
    virtual QPainterPath shape() const;
    virtual void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void setMaximumRadius (double radius);
    void setTrassId (uint trassID);
    uint trassId () const;
    void setBold (bool bold);
    const QVector< PointGraphicsItem* >& points () { return m_points; }
    void setCreate(bool create) { m_create = create; }
    bool isCreate() const { return m_create; }

signals:
    void sigAddPointToScene (QGraphicsItem *);
    void sigDelPointFromScene (QGraphicsItem *);

public slots:
    void addPosition (const QPointF& coord);
    void insertPosition (const QPointF& pos);
    void deletePosition (int pointId = -1);
    void updateTrass ();

protected:
    virtual void contextMenuEvent (QGraphicsSceneContextMenuEvent * event);

private:
    uint                m_trassId;
    QString             m_name;
    bool                m_bold;
    qreal               m_maxRadius;
    QPolygonF           m_trassImage;
    bool                m_create;
    QPainterPath        m_shape;
    QVector<PointGraphicsItem*> m_points;
};
