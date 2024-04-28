#ifndef GRSCENE_AREAWIDGET_H_
#define GRSCENE_AREAWIDGET_H_

#include <QWidget>
#include <QPen>
#include <QBrush>
#include "../graphics/MapScene.hpp"
#include "../graphics/Icons.hpp"

class Button
{
public:
    Button() { m_isSelected = false;  m_isMinimized = false; }

	QPen pen() const
	{
		QPen pen;
		if(m_isSelected)
			pen = QPen(QBrush(Qt::white), 2, Qt::SolidLine);
		else
			pen = QPen(QBrush(Qt::gray), 3, Qt::SolidLine);

		return pen;
	}

	QBrush brush() const
	{
		QBrush brush;
		if(m_isSelected)
			brush = QBrush(QColor(0, 0, 255), Qt::SolidPattern);
		else
			brush = QBrush(QColor(0, 0, 128), Qt::SolidPattern);

		return brush;
	}

    inline bool isSelected() const { return m_isSelected; }

    inline void setSelected(bool select) { m_isSelected = select; }

    inline void setMinimizeState(bool state) { m_isMinimized = state; }

    inline void setNormalButtonRect(int x, int y, int w, int h) { m_normalButtonRect = QRect(x, y, w, h); }

    inline void setMinimizeButtonRect(int x, int y, int w, int h) { m_minimizeButtonRect = QRect(x, y, w, h); }

    inline const QRectF& buttonRect() const { return m_isMinimized ? m_minimizeButtonRect : m_normalButtonRect; }

private:
	bool m_isSelected;
	bool m_isMinimized;
	QRectF m_normalButtonRect;
	QRectF m_minimizeButtonRect;
};

struct SceneObject
{
    enum TypeObject
    {
        Icon,
        Polyline
    };

    QPointF         coord;      //!< Координаты объекта в км
    QColor          color;      //!< Цвет объекта
    Icon::IconType  iconType;   //!< Тип Иконки
    QPolygonF       polyline;   //!< Полилиния
    qreal           rotation;   //!< Курс (радиан)
    TypeObject      type;       //!< Тип объекта

    SceneObject()
    {
        rotation = 0.0;
        type = Icon;
        iconType = Icon::IconUnknown;
    }
};

/**
 * @brief The ScaleWidget class класс виджета для управления масштабом сцены
 */
class ScaleWidget: public QWidget
{
	Q_OBJECT

public:

    enum WidgetPosition
    {
        TopLeft     = 0,
        TopRight    = 1,
        BottomRight = 2,
        BottomLeft  = 3
    };

    explicit ScaleWidget(QWidget *parent = 0);
	virtual ~ScaleWidget();

    void zoomIn();
    void zoomOut();

    const QRectF& viewRect() const { return m_viewRect; }

    void setSceneVisibleRectCenter(const QPointF&, bool );

    void addSceneObject(SceneObject* object);


signals:
	void sigScalePlus(qreal);
	void sigScaleMinus(qreal);

	void sigSetSceneVisibleRectCenter(const QPointF&);

public slots:
	void slotSceneVisibleRect(const QRectF&);

protected:
	/*!
	 * @brief Событие перерисования виджета
	 * @details см. справку Qt
	 */
    virtual void paintEvent ( QPaintEvent * event );

    /*!
	 * @brief Событие перетаскивания мыши
     * @details см. справку Qt    void setSceneVisibleRectCenter(const QPointF&, bool );
	 */
    virtual void mouseMoveEvent ( QMouseEvent * event );
    /*!
	 * @brief Событие зажатия нопки мыши
	 * @details см. справку Qt
	 */
    virtual void mousePressEvent ( QMouseEvent * event );

    /*!
	 * @brief Событие отпускания кнопки мыши
	 * @details см. справку Qt
	 */
    virtual void mouseReleaseEvent ( QMouseEvent * event );

private:

    bool m_isMinimize;
    qreal m_scale;
    bool m_mouseButtonDown;

    QRectF m_sceneRect;
    QRectF m_viewRect;
    QRectF m_buttonsRect;
    QPointF m_scaleTextPos;
    QPointF m_bufMousePosPointF;

    Button m_scalePlusButton;
    Button m_scaleMinusButton;
    Button m_changePosButton;
    Button m_minimizeButton;

    WidgetPosition m_position;

    QVector<SceneObject*> m_sceneObjects;

    void setMinimizeState(bool);
    void drawGruppObjects(QPainter& painter);
    void changePosition();
};

#endif /* GRSCENE_AREAWIDGET_H_ */
