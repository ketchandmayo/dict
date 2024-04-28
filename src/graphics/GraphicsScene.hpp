#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include "./AirObjRouteGraphicsItem.hpp"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:

   GraphicsScene(QObject* parent = 0);

   virtual ~GraphicsScene();

   void setScale(qreal scale) { m_scale = scale; }

   qreal scale() const { return m_scale; }

   void setSceneVisibleRect(const QRectF& rect) { m_sceneVisibleRect = rect; }

   const QRectF& sceneVisibleRect() const { return m_sceneVisibleRect; }

signals:

   void sigSceneMousePress(const QPointF& pos, Qt::MouseButton);

   void sigSceneMouseRelease(const QPointF& pos, Qt::MouseButton);

   void sigSceneMouseMove(const QPointF& pos);

   void sigSceneMouseDoubleClick();

   void sigUpdateScaleWidgetViewRect();

public slots:

protected:

    virtual void drawBackground( QPainter * painter, const QRectF & rect );

    virtual void drawForeground ( QPainter * painter, const QRectF & rect );

    virtual bool event ( QEvent * event );


private:
    QRectF      m_sceneVisibleRect;
    qreal       m_scale;
    bool        m_vizibleAzimuth;
    QPointF     m_azimuthPos;
    int         m_azimuth;

    void drawLinear(QPainter* painter);
    void drawAzimuthGrid(QPainter* painter);
    void drawCoordGrid(QPainter* painter);

    QSizeF sceneSizeInSm() const;

};

#endif // GRAPHICS_SCENE_H
