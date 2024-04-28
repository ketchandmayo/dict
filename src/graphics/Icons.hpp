#ifndef ICONS_H_
#define ICONS_H_

#include <QMap>
#include <QVector>
#include <QPainter>
#include <QXmlDefaultHandler>

/**
 * @brief The Element class
 */

class Element
{
public:

        enum ElementType
        {
            ElementUnkonown,
            ElementPolyline,    //!< Ломаная линия
            ElementRect,        //!< Прямоугольник
            ElementEllipse,     //!< Эллипс
            ElementPolygon      //!< Многоугольник
        };

        Element() { m_type = ElementUnkonown; }

        Element(ElementType type) { m_type = type; }

        ~Element() { }

        inline void addPointToPolygon(const QPointF& point) { m_polygon.append(point); }

        void setRectPos(qreal x, qreal y);

        void setRectSize(qreal w, qreal h);

        inline const QPolygonF& polygon() const { return m_polygon; }

        inline const QRectF& rect() const { return m_rect; }

        inline void setType(ElementType type) { m_type = type; }

        inline ElementType type() const { return m_type; }

        inline void setPen(const QPen& pen) { m_pen = pen; }

        inline const QPen& pen() const { return m_pen; }

        inline void setBrush(const QBrush& brush) { m_brush = brush; }

        inline const QBrush& brush() const { return m_brush; }

        void clean();

private:
        QPolygonF m_polygon;    //!< массив точек для построения примитивов: ломаная линия и многоугольник
        QRectF  m_rect;         //!< прямоугольник для построения примитивов: прямоугольник и эллипс
        ElementType m_type;     //!< тип примитива
        QPen m_pen;             //!< кисть для рисования примитива
        QBrush m_brush;         //!< заливка для рисования примитива
};

/**
 * @brief The Icon class
 */

class Icon
{
public:

      enum IconType
      {
          IconUnknown           = 0,
          IconExtAbonent        = 1,
          IconAirportOwnFund    = 2,
          IconAirportOwnSpare   = 3,
          IconAirportNeighbor   = 4,
          IconAirportEnemy      = 5,
          IconAirobjectOwn      = 6,
          IconAirobjectEnemy    = 7,
          IconsGroupOwn         = 8,
          IconsGroupEnemy       = 9
      };

      Icon() { m_type = IconUnknown; }

      Icon(IconType type) { m_type = type; }

      ~Icon() {}

      inline void appendElement(const Element& element) { m_elements.append(element); }

      inline IconType type() const { return m_type; }

      void paint(QPainter* painter);

      void clean();

private:
      QVector<Element> m_elements;
      IconType m_type;

};

typedef QMap<Icon::IconType, Icon> IconMap;

class IconsParser : public QXmlDefaultHandler
{

public:
    explicit IconsParser(IconMap* iconMap);

    virtual ~IconsParser();

    bool startElement ( const QString & namespaceURI, const QString & localName,
                                                 const QString & qName, const QXmlAttributes & atts );

    bool endElement ( const QString & namespaceURI, const QString & localName, const QString & qName );

    bool fatalError ( const QXmlParseException & exception );

private:
    Element m_element;    //!<
    Icon    m_icon;       //!<
    IconMap* m_iconMap;   //!<

    Qt::PenStyle penFromStr(const QString &str);
    Qt::BrushStyle brushFromStr(const QString &str);
    Icon::IconType iconTypeFromStr(const QString &str);
    Element::ElementType elemTypeFromStr(const QString &str);

};

class Icons
{

public:
    static Icons* instance();
    static void cleanup();

    Icon icon(Icon::IconType key);

    bool load(const QString& fileName);

protected:
    Icons();
    virtual ~Icons();

private:
    static Icons* _instance;
    IconMap m_iconsMap;

};

#endif /* ICONS_H_ */
