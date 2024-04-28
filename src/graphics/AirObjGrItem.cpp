#include "AirObjGrItem.hpp"
#include <QCursor>
#include <QGraphicsScene>

FormularData::FormularData ()
                           : m_trenagID(0)
                           , m_moviID(0)
{

}

const QString FormularData::trenagIDStr () const
{
    return QString::number(m_trenagID);
}

const QString FormularData::moviIDStr() const
{
    return m_moviID > 0 ? QString::number(m_moviID) : "-";
}

const QString FormularData::height() const
{
    return QString::number( m_currentPosition.height(Km), 'f', 1 );
}

const QString FormularData::speed() const
{
    return QString::number( m_currentPosition.speed(KmpMin), 'f', 1 );
}

/*******************************************************************************/

AirObjGraphicsItem::AirObjGraphicsItem(QGraphicsItem * parent)
                                    : QGraphicsItem(parent)
{
  m_iconType = Icon::IconUnknown;
  m_editMode = false;
  setZValue(0.2);
  m_formularType = 1;
  setFlag(QGraphicsItem::ItemIsSelectable, true);
}

AirObjGraphicsItem::~AirObjGraphicsItem()
{
  //qDebug() << "destroy AirObjGraphicsItem";

    cleanScene();
}

QRectF AirObjGraphicsItem::boundingRect() const
{
  return QRectF(/*m_coord.x()*/-25.0, /*m_coord.y()*/-25.0, 50.0, 50.0);
}

void AirObjGraphicsItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * , QWidget *  )
{
    if(!painter) return;

    QTransform transform = painter->transform();

    painter->setRenderHint( QPainter::Antialiasing, true );
    painter->setPen( QPen( QBrush( QColor(Qt::white)), 2 , Qt::SolidLine ) );
    painter->setBrush(Qt::NoBrush);

    painter->save();
    painter->resetTransform();
    painter->translate( transform.map( QPointF(0.0, 0.0) ) );
    painter->save();
    painter->rotate( rotation() );

    if(m_editMode)
    {
        painter->drawEllipse( boundingRect() );
    }

    Icons::instance()->icon( m_iconType ).paint( painter );
    painter->restore();

    drawFormular(painter);

    painter->restore();
    painter->setRenderHint( QPainter::Antialiasing, false );
}

void AirObjGraphicsItem::drawFormular(QPainter* painter)
{
    if(!painter) return;

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(8);
    font.setBold(false);

    painter->save();
    painter->setPen( QPen( QBrush( Qt::gray), 0 ) );
    painter->setFont(font);

    qreal dx = 0.0;
    if( 25.0*cos(degreeToRadian(rotation())) < 0.0 )
        dx = qAbs( 25.0*cos(degreeToRadian(rotation()) ));

    dx += 15.0;

    QString line1;
    QString line2;

    switch(m_formularType)
    {
        case 1:
            line1 = QString("%1").arg(m_formularData.trenagIDStr());
        break;

        case 2:
            line1 = QString("%1").arg(m_formularData.trenagIDStr());
            line2 = QString("%1").arg(m_formularData.moviIDStr());
        break;

        case 3:
            line1 = QString("%1  %2 %3").arg(m_formularData.trenagIDStr()).arg(m_formularData.height()).arg(m_formularData.tla());
            line2 = QString("%1  %2 %3").arg(m_formularData.moviIDStr()).arg(m_formularData.speed()).arg(m_formularData.ivo());
        break;

    default:
        break;
    }
    painter->drawText(QPointF(-15.0, dx), line1 );
    dx += 10.0;
    painter->drawText(QPointF(-15.0, dx), line2 );

    painter->restore();
}

void AirObjGraphicsItem::setIconType(Icon::IconType type)
{
    //if( type != Icon::IconAirobjectOwn && type != Icon::IconAirobjectEnemy ) return;
    m_iconType = type;
    update( boundingRect() );
}

bool AirObjGraphicsItem::cleanScene()
{
    QGraphicsScene* itemScene = scene();
    if(itemScene)
    {
        itemScene->removeItem(this);
        return true;
    }
    return false;
}
