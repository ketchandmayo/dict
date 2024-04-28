#ifndef MANEUVER_GRITEM_H_
#define MANEUVER_GRITEM_H_

#include <QAbstractGraphicsShapeItem>
#include <QPolygonF>
#include "../math/FnMath.hpp"

//namespace trainer {

class ManeuverGraphicsItem : public QAbstractGraphicsShapeItem
{
public:

      ManeuverGraphicsItem(QGraphicsItem * parent = 0);

      virtual ~ManeuverGraphicsItem();

      virtual QRectF boundingRect () const;

      virtual void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

      void addLinear(const QPointF& startPoint, const QPointF& endPoint);

      void addArc(const QPointF& startPoint, const QPointF& centrCircle, qreal startCourse, qreal endCourse, qreal radius,
                                                                            CourseChange sign = Right);

      void setEditMode(bool mode) { m_editMode = mode; }

      void clearItem();

      bool cleanScene();

private:
      bool m_editMode;
      QPolygonF m_polygon;
      QRectF m_boundingRect;
};

#endif /* MANEUVER_GRITEM_H_ */
