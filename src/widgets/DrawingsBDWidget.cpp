#include "./DrawingsBDWidget.hpp"
#include "../graphics/GraphicsScene.hpp"
#include <QFileDialog>

DrawingsBDWidget::DrawingsBDWidget(QWidget *parent) :
    QWidget(parent)
{
    init();
}

void DrawingsBDWidget::connectSigSlot()
{
    connect(ui.doubleSpinBoxMaxRadius, SIGNAL(valueChanged(double)), m_graphicsEngine, SLOT(slotSetMaximumRadius(double)));
}

void DrawingsBDWidget::init()
{
    ui.setupUi(this);

    m_graphicsEngine = new GraphicsEngine(this);

    m_graphicsEngine->setGraphicsView(ui.graphicsView);

    Icons::instance()->load(":xml/icons.xml");

    connectSigSlot();
}

DrawingsBDWidget::~DrawingsBDWidget()
{

}

