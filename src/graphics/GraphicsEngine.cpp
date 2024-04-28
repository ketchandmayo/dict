#include "./GraphicsEngine.hpp"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "./MapScene.hpp"
#include <QFile>
#include <QTextCodec>

//#include "../uns/grupp.hpp"
//#include "../uns/Dictionary.hpp"

#include "./PointGraphicsItem.hpp"

GraphicsEngine::GraphicsEngine(QObject* parent) : QObject(parent)
{
    m_grScene = new GraphicsScene();
    m_grView = NULL;
    m_scaleWidget = new ScaleWidget();
    m_mousePressInPoint = false;
    m_mousePress = false;
    m_trass = new AirObjectRouteGraphicsObject();
    slotAddNewGraphicsItemToScene(m_trass);
    m_scale = 3200;

    connect ( m_scaleWidget, SIGNAL( sigScalePlus ( qreal ) ), this, SLOT( slotScalePlus ( qreal ) ) );
    connect ( m_scaleWidget, SIGNAL( sigScaleMinus ( qreal ) ), this, SLOT( slotScaleMinus ( qreal ) ) ) ;
    connect ( this,          SIGNAL( sigSceneVisibleRect( const QRectF& ) ), m_scaleWidget, SLOT ( slotSceneVisibleRect( const QRectF& ) ) );
    connect ( m_scaleWidget, SIGNAL( sigSetSceneVisibleRectCenter( const QPointF& ) ), this, SLOT( slotSetSceneVisibleRectCenter( const QPointF& ) ) );
    connect ( m_grScene, SIGNAL ( sigSceneMouseRelease(const QPointF&, Qt::MouseButton) ), this, SLOT ( slotSceneMouseRelease ( const QPointF&, Qt::MouseButton ) ) );
    connect ( m_grScene, SIGNAL ( sigSceneMouseDoubleClick()), this, SLOT(slotSceneMouseDoubleClicked()));
    connect ( m_grScene, SIGNAL ( sigSceneMousePress ( const QPointF&, Qt::MouseButton ) ), this, SLOT ( slotSceneMousePress ( const QPointF&, Qt::MouseButton ) ) );
    connect ( m_grScene, SIGNAL ( sigSceneMouseMove ( const QPointF& ) ), this, SLOT(slotSceneMouseMove(const QPointF&)));
    connect ( m_trass, SIGNAL ( sigAddPointToScene ( QGraphicsItem *) ), this, SLOT ( slotAddNewGraphicsItemToScene ( QGraphicsItem *) ) );
    connect ( m_trass, SIGNAL ( sigDelPointFromScene ( QGraphicsItem *) ), this, SLOT ( slotDeleteGraphicsItemFromScene( QGraphicsItem * ) ) );
}

GraphicsEngine::~GraphicsEngine ()
{
     MapScene::cleanup();
}

GraphicsScene* const GraphicsEngine::grScene () const
{
    return m_grScene;
}

void GraphicsEngine::setGraphicsView (QGraphicsView* view)
{
    m_grView = view;
    m_grView->scale(0.2, 0.2);
    m_grView->rotate(-90.0);
    m_grView->setScene(grScene());

    m_scaleWidget->setParent(m_grView);

    MapScene::instance()->setGraphicsView(m_grView);
}

void GraphicsEngine::slotAddNewGraphicsItemToScene (QGraphicsItem * item)
{
    if(!m_grScene) return;

    qDebug() << "slotAddNewGraphicsItemToScene";

    if(!m_grScene->items().contains(item))
        m_grScene->addItem(item);

    m_grScene->update();
}

bool GraphicsEngine::slotDeleteGraphicsItemFromScene (QGraphicsItem * item)
{
    if(!m_grScene) return false;

    bool remove = false;

    if(m_grScene->items().contains(item))
    {
        m_grScene->removeItem(item);
        remove = true;
    }

    m_grScene->update();

    return remove;
}


void GraphicsEngine::slotGraphicsUpdate (const QGraphicsItem* centerItem)
{
    if(m_grView)
    {
        if(centerItem)
        {
            m_grView->centerOn(centerItem);
            emit sigSceneVisibleRect(MapScene::sceneViewRect(m_grView));
        }
        m_grView->update();
    }
    if(m_grScene)
        m_grScene->update();
}

void GraphicsEngine::slotScalePlus (qreal scale)
{
    if (m_scale < 50) return;
    m_scale = scale;
    QRectF rect = MapScene::sceneViewRect(m_grView);
    qreal bound = qMin( qAbs( rect.width() ), qAbs( rect.height() ) );
    qreal scale_inc = bound/m_scale;
    if (m_grView)
        m_grView->scale(scale_inc, scale_inc);
    if (m_grScene)
        m_grScene->setScale(m_scale);
    slotUpdateScaleWidgetViewRect();
}

void GraphicsEngine::slotScaleMinus (qreal scale)
{
    if (m_scale > 3200) return;
    m_scale = scale;
    QRectF rect = MapScene::sceneViewRect(m_grView);
    qreal bound = qMin(qAbs(rect.width()), qAbs(rect.height()));
    qreal scale_inc = bound/m_scale;
    if (m_grView)
        m_grView->scale(scale_inc, scale_inc);
    if (m_grScene)
        m_grScene->setScale(m_scale);
    slotUpdateScaleWidgetViewRect();
}

void GraphicsEngine::slotUpdateScaleWidgetViewRect ()
{
     emit sigSceneVisibleRect ( MapScene::sceneViewRect (m_grView));
}

void GraphicsEngine::slotSetSceneVisibleRectCenter (const QPointF& centr)
{
    if (!m_grView) return;

    m_grView->centerOn (centr);
    slotGraphicsUpdate ();
}

void GraphicsEngine::slotSetMaximumRadius (double radius)
{
    if(m_trass)
        m_trass->setMaximumRadius (radius);
}

void GraphicsEngine::slotSceneMousePress (const QPointF& pos, Qt::MouseButton mouseButton)
{
    m_mousePress = true;
    m_mousePressInPoint = false;
    slotGraphicsUpdate();
}

void GraphicsEngine::slotSceneMouseRelease (const QPointF& pos, Qt::MouseButton mouseButton)
{
    if (m_trass->isCreate())
    {
        if (!m_mousePressInPoint && mouseButton == Qt::LeftButton)
            m_trass->addPosition(pos);
    }
    else
        if (!m_mousePressInPoint
            && mouseButton == Qt::RightButton
            && m_trass->shape().contains(pos))
            m_trass->insertPosition(pos);

    slotGraphicsUpdate();
}

void GraphicsEngine::slotSceneMouseMove (const QPointF& pos)
{

}

void GraphicsEngine::slotSceneMouseDoubleClicked ()
{
    if (m_trass)
        m_trass->setCreate(false);
}


