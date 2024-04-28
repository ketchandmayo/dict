#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <QObject>
#include <QTableWidget>
#include <QSharedPointer>
#include "GraphicsScene.hpp"
#include "../widgets/ScaleWidget.hpp"
#include "./MapScene.hpp"

#include "./FrontierGrItem.hpp"
#include "./AirportGrItem.hpp"
#include "./ExtabonentGrItem.hpp"
#include "./AirObjRouteGraphicsItem.hpp"
#include "./PointGraphicsItem.hpp"

struct GRUPP1;
struct GRUPP3;

class GraphicsEngine: public QObject
{
    Q_OBJECT

public:
    explicit GraphicsEngine(QObject* parent = 0);
    virtual ~GraphicsEngine();
    GraphicsScene * const grScene() const;
    void setGraphicsView(QGraphicsView* view);

public slots:
    void slotSetMaximumRadius(double radius);
    void slotGraphicsUpdate(const QGraphicsItem* centerItem = NULL);

    void slotAddNewGraphicsItemToScene(QGraphicsItem * item);

    bool slotDeleteGraphicsItemFromScene(QGraphicsItem * item);

    void slotScalePlus(qreal);

    void slotScaleMinus(qreal);

    void slotSetSceneVisibleRectCenter(const QPointF&);

    void slotUpdateScaleWidgetViewRect();

    void slotSceneMousePress (const QPointF& pos, Qt::MouseButton);

    void slotSceneMouseRelease (const QPointF& pos, Qt::MouseButton mouseButton);

    void slotSceneMouseMove(const QPointF& pos);
    void slotSceneMouseDoubleClicked();

signals:
    void sigSceneVisibleRect(const QRectF&);

protected:

private:
    qreal                   m_scale;
    ScaleWidget*            m_scaleWidget;
    GraphicsScene*          m_grScene;
    QGraphicsView*          m_grView;
    bool                    m_mousePress;
    bool                    m_mousePressInPoint;
    AirObjectRouteGraphicsObject*      m_trass;
};

#endif // GRAPHICS_ENGINE_H
