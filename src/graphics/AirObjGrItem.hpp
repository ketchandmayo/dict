#pragma once

#include <QAbstractGraphicsShapeItem>
#include "../math/FnMath.hpp"
#include "../math/Position.hpp"
#include "Icons.hpp"
#include <QDebug>

class FormularData
{

public:
    FormularData ();
    void setTrenagID (const int id) { m_trenagID = id; }
    int trenagID () const { return m_trenagID; }
    const QString trenagIDStr () const;
    void setMoviID (const int id) { m_moviID = id; }
    int moviId () const { return m_moviID; }
    const QString moviIDStr () const;
    void setPosition (const Position& pos) { m_currentPosition = pos; }
    const QString height () const;
    const QString speed () const;
    void setTla (const QString& tla) { m_tla = tla; }
    const QString tla () const { return m_tla; }
    void setIvo (const QString& ivo) { m_ivo = ivo; }
    const QString ivo () const { return m_ivo; }

private:
    int            m_trenagID;
    int            m_moviID;
    Position       m_currentPosition;
    QString        m_tla;
    QString        m_ivo;
};

class AirObjGraphicsItem : public QGraphicsItem
{

public:
    AirObjGraphicsItem (QGraphicsItem * parent = 0);

    virtual ~AirObjGraphicsItem ();
    virtual QRectF boundingRect () const;
    virtual void paint (QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    void setIconType (const Icon::IconType type);
    void setCoord (const QPointF& coord) { setPos( coord ); }
    void setCourse (const qreal course) { setRotation( course ); }
    void setEditMode (const bool mode) { m_editMode = mode; }
    void setFormularData (const FormularData& data) { m_formularData = data; }
    void setFormularType (const int formularMask) { m_formularType = formularMask; update(boundingRect()); }
    void drawFormular (QPainter* painter);
    bool cleanScene ();

private:
    Icon::IconType m_iconType;
    bool           m_editMode;
    FormularData   m_formularData;
    INT            m_formularType;

};
