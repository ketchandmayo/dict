#include "./Icons.hpp"
#include <QMessageBox>


void Element::setRectPos(qreal x, qreal y)
{
    m_rect.setX(x);
    m_rect.setY(y);
}

void Element::setRectSize(qreal w, qreal h)
{
    m_rect.setWidth(w);
    m_rect.setHeight(h);
}

void Element::clean()
{
    m_polygon.clear();
    m_rect = QRect();
    m_type = ElementUnkonown;
    m_pen = QPen();
    m_brush = QBrush();
}

//==============-Функции Класса Icon-=============================================

void Icon::paint(QPainter* painter)
{
  if(!painter) return;

  foreach(Element elem, m_elements)
  {

      switch( elem.type() )
      {
        case Element::ElementUnkonown:
        break;
        case Element::ElementPolyline:
            painter->setPen( elem.pen() );
            painter->drawPolyline( elem.polygon() );
        break;
        case Element::ElementRect:
            painter->setPen( elem.pen() );
            painter->setBrush( elem.brush() );
            painter->drawRect( elem.rect() );
        break;
        case Element::ElementEllipse:
            painter->setPen( elem.pen() );
            painter->setBrush( elem.brush() );
            painter->drawEllipse( elem.rect() );
        break;
        case Element::ElementPolygon:
            painter->setPen( elem.pen() );
            painter->setBrush( elem.brush() );
            painter->drawPolygon( elem.polygon() );
        break;
        default:
        break;
      }

  }
}

void Icon::clean()
{
  m_elements.clear();
  m_type = IconUnknown;
}

//==============-Функции Класса IconParser-=============================================

Qt::PenStyle IconsParser::penFromStr(const QString &str)
{
    Qt::PenStyle pen = Qt::SolidLine;
    if(str=="NoPen")
        pen = Qt::NoPen;
    else if(str=="SolidLine")
        pen = Qt::SolidLine;
    else if(str=="DashLine")
        pen = Qt::DashLine;
    else if(str=="DotLine")
        pen = Qt::DotLine;
    else if(str=="DashDotLine")
        pen = Qt::DashDotLine;
    else if(str=="DashDotDotLine")
        pen = Qt::DashDotDotLine;

    return pen;
}

Qt::BrushStyle IconsParser::brushFromStr(const QString &str)
{
    Qt::BrushStyle brush = Qt::SolidPattern;

    if(str=="NoBrush")
        brush=Qt::NoBrush;
    else if(str=="SolidPattern")
        brush=Qt::SolidPattern;
    else if(str=="Dense1Pattern")
        brush=Qt::Dense1Pattern;
    else if(str=="Dense2Pattern")
        brush=Qt::Dense2Pattern;
    else if(str=="Dense3Pattern")
        brush=Qt::Dense3Pattern;
    else if(str=="Dense4Pattern")
        brush=Qt::Dense4Pattern;
    else if(str=="Dense5Pattern")
        brush=Qt::Dense5Pattern;
    else if(str=="Dense6Pattern")
        brush=Qt::Dense6Pattern;
    else if(str=="Dense7Pattern")
        brush=Qt::Dense7Pattern;
    else if(str=="HorPattern")
        brush=Qt::HorPattern;
    else if(str=="VerPattern")
        brush=Qt::VerPattern;
    else if(str=="CrossPattern")
        brush=Qt::CrossPattern;
    else if(str=="BDiagPattern")
        brush=Qt::BDiagPattern;
    else if(str=="FDiagPattern")
        brush=Qt::FDiagPattern;
    else if(str=="DiagCrossPattern")
        brush=Qt::DiagCrossPattern;
    else if(str=="LinearGradientPattern")
        brush=Qt::LinearGradientPattern;
    else if(str=="ConicalGradientPattern")
        brush=Qt::ConicalGradientPattern;
    else if(str=="RadialGradientPattern")
        brush=Qt::RadialGradientPattern;

    return brush;
}

Icon::IconType IconsParser::iconTypeFromStr(const QString &str)
{
  Icon::IconType type = Icon::IconUnknown;

  if( str == "EXT_ABONENT" )
      type = Icon::IconExtAbonent;
  else if( str == "AIRDROM_SVOJ_OSNOV" )
      type = Icon::IconAirportOwnFund;
  else if( str == "AIRDROM_SVOJ_ZAPAS" )
      type = Icon::IconAirportOwnSpare ;
  else if( str == "AIRDROM_SOSED" )
      type = Icon::IconAirportNeighbor;
  else if( str == "AIRDROM_ENEMY" )
      type = Icon::IconAirportEnemy;
  else if( str == "AIROBJECT_SVOJ" )
      type = Icon::IconAirobjectOwn;
  else if( str == "AIROBJECT_ENEMY" )
      type = Icon::IconAirobjectEnemy;
  else if( str == "GROUP_OWN" )
      type = Icon::IconsGroupOwn;
  else if( str == "GROUP_ENEMY" )
      type = Icon::IconsGroupEnemy;

  return type;
}

Element::ElementType IconsParser::elemTypeFromStr(const QString &str)
{
  Element::ElementType type = Element::ElementUnkonown;
  if(str == "polyline")
    type = Element::ElementPolyline;
  else if(str == "rect")
    type = Element::ElementRect;
  else if(str == "ellipse")
    type = Element::ElementEllipse;
  else if(str == "polygon")
    type = Element::ElementPolygon;

  return type;
}

IconsParser::IconsParser(IconMap* iconMap)
{
    m_iconMap = iconMap;
};

IconsParser::~IconsParser()
{

};

bool IconsParser::startElement ( const QString & namespaceURI, const QString & localName,
                                             const QString & qName, const QXmlAttributes & atts )
{
    Q_UNUSED(namespaceURI);
    Q_UNUSED(localName);

    if(qName == "icon")
    {
        QString type = atts.value("name");

        m_icon = Icon( iconTypeFromStr(type) );
    }
    else if(qName == "element")
    {
        QString type = atts.value("type");

        m_element = Element( elemTypeFromStr(type) );
    }
    else if(qName == "pen")
    {
        QString str_pen_style = atts.value("style");
        QString str_pen_widht = atts.value("width");
        int red = atts.value("color_red").toInt();
        int green = atts.value("color_green").toInt();
        int blue = atts.value("color_blue").toInt();
        int penWidth = str_pen_widht.toInt();

        m_element.setPen( QPen( QBrush( QColor(red, green, blue)), penWidth , penFromStr(str_pen_style) ) );
    }
    else if(qName == "brush")
    {
        int red = atts.value("color_red").toInt();
        int green = atts.value("color_green").toInt();
        int blue = atts.value("color_blue").toInt();
        QString str_brush_style = atts.value("style");

        m_element.setBrush(QBrush(QColor(red, green, blue), brushFromStr(str_brush_style)));
    }
    else if(qName == "point")
    {
        qreal x = atts.value("x").toDouble();
        qreal y = atts.value("y").toDouble();

        switch( m_element.type() )
        {
          case Element::ElementPolyline: case Element::ElementPolygon:
                m_element.addPointToPolygon( QPointF(x, y) );
             break;
          case Element::ElementRect: case Element::ElementEllipse:
                m_element.setRectPos(x, y);
             break;
          default:
             break;
        }
    }
    else if(qName == "size")
    {
        qreal w = atts.value("w").toDouble();
        qreal h = atts.value("h").toDouble();

        m_element.setRectSize(w, h);
    }

    return true;
}

bool IconsParser::endElement ( const QString & namespaceURI, const QString & localName, const QString & qName )
{
  Q_UNUSED(namespaceURI);
  Q_UNUSED(localName);

  if(qName == "element")
  {
    m_icon.appendElement(m_element);
    m_element.clean();
  }
  else if(qName == "icon")
  {
      if(m_iconMap)
        m_iconMap->insert(m_icon.type(), m_icon);
      m_icon.clean();
  }

  return true;
}


bool IconsParser::fatalError ( const QXmlParseException & exception )
{
  QMessageBox::warning(0, QObject::tr("Ошибка загрузки значков."), QObject::tr("Ошибка чтения.\nНекорректные данные строка %1, столбец %2:\n%3.").
                   arg(exception.lineNumber()).arg(exception.columnNumber()).arg(exception.message()));

  return false;
}

//==============-Функции Класса Icons-=============================================

Icons* Icons::_instance = NULL;

Icons* Icons::instance()
{
  if(_instance == NULL)
    _instance = new Icons();

  return _instance;
}

void Icons::cleanup()
{
  if(_instance != NULL)
  {
      delete _instance;
      _instance = NULL;
  }
}

Icons::Icons()
{

}

Icons::~Icons()
{
//    qDebug() << "destroy Icons";
}

Icon Icons::icon(Icon::IconType key)
{
    Icon icon;

    icon = m_iconsMap.value(key, Icon());

    return icon;
}

bool Icons::load(const QString& fileName)
{
    QXmlSimpleReader reader;
    IconsParser handler(&m_iconsMap);
    bool read = false;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    QFile file(fileName);

    if( !file.exists() )
    {
        QMessageBox::warning(0, QObject::tr("Ошибка загрузки значков."), QObject::tr("Файл %1 не найден!").arg(fileName));

    }

    if (file.exists() && file.open(QIODevice::ReadOnly))
      {
            QXmlInputSource source(&file);

            reader.parse(source);
            file.close();
            read = true;
    }

    return read;
}

