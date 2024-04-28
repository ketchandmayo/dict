#include "./ScaleWidget.hpp"
#include <QPainter>
#include <QMouseEvent>
#include <math.h>

ScaleWidget::ScaleWidget(QWidget* parent) : QWidget(parent)
{
    m_isMinimize = false;
    m_mouseButtonDown = false;

    m_position = TopLeft;

	setFont(QFont("Monospace", 12, QFont::Bold));
	setMouseTracking(true);

    setMinimumSize(210, 50);

    setMaximumSize(MT_VIEW_RECT.width()+10, MT_VIEW_RECT.height()+50);

    setGeometry(0, 0, MT_VIEW_RECT.width()+10, MT_VIEW_RECT.height()+50);

    m_sceneRect = QRect(5, 5,  MT_VIEW_RECT.width(), MT_VIEW_RECT.height());
	m_viewRect = QRectF(0, 0, 50, 50);
	m_viewRect.moveCenter(m_sceneRect.center());

    m_buttonsRect = QRect(5, MT_VIEW_RECT.height()+10, MT_VIEW_RECT.width(), 35);
    m_scaleTextPos = QPoint(10, MT_VIEW_RECT.height()+35);


    m_scalePlusButton.setNormalButtonRect(MT_VIEW_RECT.width()-110, MT_VIEW_RECT.height()+15, 25, 25);
    m_scalePlusButton.setMinimizeButtonRect(90, 15, 25, 25);

    m_scaleMinusButton.setNormalButtonRect(MT_VIEW_RECT.width()-70, MT_VIEW_RECT.height()+15, 25, 25);
    m_scaleMinusButton.setMinimizeButtonRect(130, 15, 25, 25);

    m_changePosButton.setNormalButtonRect(MT_VIEW_RECT.width()-10, MT_VIEW_RECT.height()+15, 10, 10);
    m_changePosButton.setMinimizeButtonRect(190, 15, 10, 10);

    m_minimizeButton.setNormalButtonRect(MT_VIEW_RECT.width()-30, MT_VIEW_RECT.height()+15, 10, 10);
    m_minimizeButton.setMinimizeButtonRect(170, 15, 10, 10);

	m_scale = 3200.0;
}

ScaleWidget::~ScaleWidget()
{
//    qDebug() << "destroy ScaleWidget";
}

void ScaleWidget::drawGruppObjects(QPainter& painter)
{
    foreach(SceneObject* object, m_sceneObjects)
    {
        if(object) {

            QTransform transform = MapScene::transformFromScene(m_sceneRect);

            if(object->type == SceneObject::Icon)
            {
                QPointF coord = transform.map( object->coord );

                qreal course = object->rotation;

                painter.save();

                painter.translate(coord);

                painter.rotate(course);

                painter.scale(0.4, 0.4);

                Icons::instance()->icon(object->iconType).paint(&painter);

                painter.restore();
            }
            else
            {
                QPolygonF polyline = transform.map(object->polyline);

                painter.setPen(QPen(QBrush(object->color), 0, Qt::SolidLine));

                painter.drawPolyline(polyline);
            }
        }
    }
}

void ScaleWidget::paintEvent ( QPaintEvent * event )
{
	Q_UNUSED( event );

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, false);
    painter.fillRect(rect(), QColor(0, 0, 0));

	painter.setPen(QPen(QBrush(Qt::white), 0, Qt::SolidLine));
	painter.setBrush(Qt::NoBrush);
	painter.drawRect(1, 1, size().width()-2, size().height()-2);

	//------- Сцена----------------------------------------------

	if(!m_isMinimize)
	{
		painter.setPen(QPen(QBrush(Qt::white), 0, Qt::SolidLine));
        painter.setBrush(QBrush( QColor(0, 0, 0), Qt::SolidPattern));
		painter.drawRect(m_sceneRect);

        drawGruppObjects(painter);

			//сетка
        painter.setPen(QPen(QBrush(QColor(196, 196, 196)), 0, Qt::SolidLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(5, 5, MT_VIEW_RECT.width(), MT_VIEW_RECT.height());

        //стрелки компаса
		QPolygon nord, sud;
		nord << QPoint(20, 30) << QPoint(25, 10) << QPoint(30, 30);
		sud << QPoint(20, 30) << QPoint(25, 50) << QPoint(30, 30);
		painter.setBrush(QBrush(QColor(0, 0, 128), Qt::SolidPattern));
		painter.drawPolygon(nord);
		painter.setBrush(QBrush(QColor(128, 0, 0), Qt::SolidPattern));
		painter.drawPolygon(sud);
		painter.setBrush(Qt::NoBrush);

		painter.setPen(QPen(QBrush(Qt::gray), 0, Qt::SolidLine));
        painter.drawText(QPoint(MT_VIEW_RECT.width()/2, 20), QObject::tr("С"));
        painter.drawText(QPoint(5, MT_VIEW_RECT.height()/2 + 10), QObject::tr("З"));
        painter.drawText(QPoint(MT_VIEW_RECT.width()-5, MT_VIEW_RECT.height()/2 + 10), QObject::tr("В"));
        painter.drawText(QPoint(MT_VIEW_RECT.width()/2, MT_VIEW_RECT.height()), QObject::tr("Ю"));

		painter.setPen(QPen(QBrush(Qt::white), 0, Qt::SolidLine));
		painter.setBrush(Qt::NoBrush);
		painter.drawRect(m_viewRect);
	}

	//-------------Кнопки-----------------------------------------

	painter.setRenderHint(QPainter::Antialiasing, true);
	QPointF p_centr = m_scalePlusButton.buttonRect().center();
	QPointF m_centr = m_scaleMinusButton.buttonRect().center();

	painter.setPen(QPen(QBrush(Qt::white), 0, Qt::SolidLine));
	painter.setBrush(QBrush(QColor(0, 8, 0), Qt::SolidPattern));
	painter.drawRect(m_buttonsRect);
	painter.setBrush(Qt::NoBrush);

		// кнопка +(увеличить масштаб)
	painter.setPen(m_scalePlusButton.pen());
	painter.setBrush(m_scalePlusButton.brush());

	painter.drawLine(p_centr, m_scalePlusButton.buttonRect().bottomRight());
	painter.drawEllipse(m_scalePlusButton.buttonRect());

	painter.drawLine(p_centr.x()-5, p_centr.y(), p_centr.x()+5, p_centr.y());
	painter.drawLine(p_centr.x(), p_centr.y()-5, p_centr.x(), p_centr.y()+5);

		// кнопка -(уменьшить масштаб)
	painter.setPen(m_scaleMinusButton.pen());
	painter.setBrush(m_scaleMinusButton.brush());

	painter.drawLine(m_centr, m_scaleMinusButton.buttonRect().bottomRight());
	painter.drawEllipse(m_scaleMinusButton.buttonRect());
	painter.drawLine(m_centr.x()-5, m_centr.y(), m_centr.x()+5, m_centr.y());

    // кнопка изменить положение на экране
    painter.setPen(m_changePosButton.pen());
    QPen pen1 = m_changePosButton.pen();
    QPen pen2 = m_changePosButton.pen();
    pen1.setWidth(4);
    pen2.setWidth(8);


    if(m_position == BottomLeft)
        painter.setPen(pen2);
    else
        painter.setPen(pen1);

    painter.drawPoint( m_changePosButton.buttonRect().topLeft() );


    if(m_position == TopLeft)
        painter.setPen(pen2);
    else
        painter.setPen(pen1);

    painter.drawPoint( m_changePosButton.buttonRect().topRight() );


    if(m_position == TopRight)
        painter.setPen(pen2);
    else
        painter.setPen(pen1);

    painter.drawPoint( m_changePosButton.buttonRect().bottomRight() );


    if(m_position == BottomRight)
        painter.setPen(pen2);
    else
        painter.setPen(pen1);

    painter.drawPoint( m_changePosButton.buttonRect().bottomLeft() );


		// кнопка свернуть
	painter.setPen(m_minimizeButton.pen());
	if(m_isMinimize)
		painter.drawRect(m_minimizeButton.buttonRect());
	else
		painter.drawLine(m_minimizeButton.buttonRect().topLeft(), m_minimizeButton.buttonRect().topRight());

		// масштаб
	painter.setPen(QPen(QBrush(Qt::white), 3, Qt::SolidLine));
    painter.drawText(m_scaleTextPos, QObject::tr("М:")+QString::number(m_scale));

    QWidget::paintEvent(event);
}

void ScaleWidget::zoomIn()
{
    if(m_scale > 100.0)
        m_scale /= 2.0;
    emit sigScalePlus(m_scale);
}

void ScaleWidget::zoomOut()
{
    if(m_scale < 3200.0)
        m_scale *= 2.0;
    emit sigScaleMinus(m_scale);
}

void ScaleWidget::mousePressEvent ( QMouseEvent * event )
{
    QPointF mousePosF = event->pos();
    if(m_scalePlusButton.isSelected())
	{
        zoomIn();
	}
    else if(m_scaleMinusButton.isSelected())
	{
        zoomOut();
	}

	if(!m_isMinimize)
	{
		if(m_viewRect.contains(mousePosF))
		{
			m_mouseButtonDown = true;
			m_bufMousePosPointF = QPointF(mousePosF -  m_viewRect.topLeft());
			setCursor(Qt::ClosedHandCursor);
		}
		else if(m_sceneRect.contains(mousePosF))
		{
			m_mouseButtonDown = true;
			setCursor(Qt::ClosedHandCursor);
			setSceneVisibleRectCenter(mousePosF, false);
			m_bufMousePosPointF = QPointF(mousePosF -  m_viewRect.topLeft());
		}
	}

	if(m_minimizeButton.isSelected())
		setMinimizeState(!m_isMinimize);

	if(m_changePosButton.isSelected())
        changePosition();
        //this->hide();

	update();

	QWidget::mousePressEvent(event);
}

void ScaleWidget::mouseMoveEvent ( QMouseEvent * event )
{
    QPointF mousePosF = event->pos();
	m_scalePlusButton.setSelected( m_scalePlusButton.buttonRect().contains(mousePosF) );
	m_scaleMinusButton.setSelected( m_scaleMinusButton.buttonRect().contains(mousePosF) );
	m_changePosButton.setSelected( m_changePosButton.buttonRect().contains(mousePosF) );
	m_minimizeButton.setSelected( m_minimizeButton.buttonRect().contains(mousePosF) );

	if(!m_isMinimize)
	{
		if(m_mouseButtonDown)
			setSceneVisibleRectCenter(mousePosF, true);
	}

	if(!m_isMinimize)
	{
		if(m_viewRect.contains(mousePosF) && !m_mouseButtonDown)
			setCursor(Qt::OpenHandCursor);
		else if(m_sceneRect.contains(mousePosF) && !m_mouseButtonDown)
			setCursor(Qt::PointingHandCursor);
		else if(!m_mouseButtonDown)
			setCursor(Qt::ArrowCursor);
	}

	update();
	QWidget::mouseMoveEvent(event);
}

void ScaleWidget::mouseReleaseEvent ( QMouseEvent * event )
{
	if(!m_isMinimize && m_mouseButtonDown)
	{
		m_mouseButtonDown = false;
		setCursor(Qt::OpenHandCursor);
	} else
		setCursor(Qt::ArrowCursor);

	QWidget::mouseReleaseEvent(event);
}

void ScaleWidget::slotSceneVisibleRect( const QRectF& grSceneRect )
{
	QTransform transform = MapScene::transformFromScene(m_sceneRect);

	QPointF topLeft = transform.map( grSceneRect.topLeft() );
	QPointF bottomRight = transform.map( grSceneRect.bottomRight() );

	if( topLeft.x() < m_sceneRect.x())
		topLeft.setX(m_sceneRect.x());
	if( topLeft.y() < m_sceneRect.y())
		topLeft.setY(m_sceneRect.y());

	if( bottomRight.x() > m_sceneRect.bottomRight().x())
		bottomRight.setX(m_sceneRect.bottomRight().x());
	if( bottomRight.y() > m_sceneRect.bottomRight().y())
		bottomRight.setY(m_sceneRect.bottomRight().y());

	m_viewRect = QRectF( topLeft, bottomRight );

	m_viewRect.moveCenter( transform.map( grSceneRect.center() ) );

	update();
}

void ScaleWidget::setSceneVisibleRectCenter(const QPointF& mousePosF, bool move)
{
    QTransform transform = MapScene::transformToScene(m_sceneRect);

    qreal nx =  mousePosF.x() - ( move ? m_bufMousePosPointF.x() : m_viewRect.width()/2.0 );
    qreal ny =  mousePosF.y() - ( move ? m_bufMousePosPointF.y() : m_viewRect.height()/2.0 );

    qreal nw = m_viewRect.width();
    qreal nh = m_viewRect.height();

	if( nx < m_sceneRect.x() ) nx = m_sceneRect.left();
	if( ny < m_sceneRect.y() ) ny = m_sceneRect.top();
	if( nx+nw >= m_sceneRect.right() ) nx = m_sceneRect.right() - nw;
	if( ny+nh >= m_sceneRect.bottom() ) ny = m_sceneRect.bottom() - nh;

    m_viewRect.moveTo( nx, ny );

    QPointF centr = transform.map( QPointF( m_viewRect.center().x()-5.0, m_viewRect.center().y()-5.0 ) );

	emit sigSetSceneVisibleRectCenter(centr);
}

void ScaleWidget::setMinimizeState(bool state)
{
	m_isMinimize = state;
	if(m_isMinimize)
	{
        QRect parentGeometry = parentWidget()->rect();
//        qDebug() << parentGeometry;
        QPoint newPos = pos();
        if(m_position == TopRight || m_position == BottomRight)
        {
            int x = parentGeometry.right() - 210;
            newPos.setX(x);
        }
        if(m_position == BottomLeft || m_position == BottomRight)
        {
            int y = parentGeometry.bottom() - 50;
            newPos.setY(y);
        }
        m_buttonsRect = QRect(5, 10, 200, 35);
		m_scaleTextPos = QPoint(10, 35);
        setGeometry( newPos.x(), newPos.y(), 210, 50 );
	}
	else
	{
        QRect parentGeometry = parentWidget()->rect();
        QPoint newPos = pos();
        if(m_position == TopRight || m_position == BottomRight)
        {
            int x = parentGeometry.right() - (MT_VIEW_RECT.width() + 10);
            newPos.setX(x);
        }
        if(m_position == BottomLeft || m_position ==BottomRight)
        {
            int y = parentGeometry.bottom() - (MT_VIEW_RECT.height() + 50);
            newPos.setY(y);
        }
        m_buttonsRect = QRect( 5, MT_VIEW_RECT.height() + 10, MT_VIEW_RECT.width(), 35 );
        m_scaleTextPos = QPoint( 10, MT_VIEW_RECT.height() + 35 );
        setGeometry( newPos.x(), newPos.y(), MT_VIEW_RECT.width()+10, MT_VIEW_RECT.height() + 50 );
	}

	m_scalePlusButton.setMinimizeState(m_isMinimize);
	m_scaleMinusButton.setMinimizeState(m_isMinimize);
	m_changePosButton.setMinimizeState(m_isMinimize);
	m_minimizeButton.setMinimizeState(m_isMinimize);
}

void ScaleWidget::changePosition()
{
    if(!parentWidget()) return;

    switch(m_position)
    {
        case TopLeft:
        {
            QRect parentGeometry = parentWidget()->rect();
            QPoint newPos = QPoint(parentGeometry.topRight().x() - size().width(), 0);
            move(newPos);
            m_position = TopRight;
        }
        break;

        case TopRight:
        {
            QRect parentGeometry = parentWidget()->rect();
            QPoint newPos = QPoint(parentGeometry.bottomRight().x() - size().width(),
                                    parentGeometry.bottomRight().y()-size().height());
            move(newPos);
            m_position = BottomRight;
        }
        break;

        case BottomRight:
        {
            QRect parentGeometry = parentWidget()->rect();
            QPoint newPos = QPoint(0, parentGeometry.bottomRight().y()-size().height());
            move(newPos);
            m_position = BottomLeft;
        }
        break;

        case BottomLeft:
        {
            QPoint newPos = QPoint(0, 0);
            move(newPos);
            m_position = TopLeft;
        }
        break;

        default: break;
    }
}

void ScaleWidget::addSceneObject(SceneObject* object)
{
    m_sceneObjects.append(object);
    update();
}


