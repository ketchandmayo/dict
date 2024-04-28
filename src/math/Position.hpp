#ifndef POSITION_H_
#define POSITION_H_

#include <QPointF>
#include "./FnMath.hpp"

/*!
 *      @class Position
 *      @brief Класс, описывающий пространственное положение объекта
 *      @details Описывает:
 *      - плоскостные координаты X, Z (в метрах)
 *      - высоту объекта (в метрах)
 */

class Position
{

public:

    /*!
     * \brief The ChangePosition enum
     * \details Список возможных изменений.
     *          Используется для регистрации изменений
     *          от начала жизни объекта данного класса.
     */
    enum ChangePosition
    {
        NoChange        =   0,  //!< нет изменений
        XChange         =   1,  //!< изменения по X
        ZChange         =   2,  //!< изменения по Z
        CoordChange     =   3,  //!< изменения координат
        HeightChange    =   4,  //!< изменения по высоте
        SpeedChange     =   8,  //!< изменения по скорости
        CourseChange    =   16, //!< изменения по курсу
        AllChange       =   31  //!< изменения всех значений
    };

    Position();

    Position (qreal x, qreal z, CoordM cd = Meter);

    Position (const QPointF& coord, CoordM cd = Meter);

    Position (qreal x, qreal z, qreal height, CoordM cd = Meter);

    Position (const QPointF& coord, qreal height, CoordM cd = Meter);

    Position (qreal x, qreal z, qreal height, qreal course, qreal speed,
                               CoordM cd = Meter, AngleM ad = Radian, SpeedM sd = Mps);

    Position (const QPointF& coord, qreal height, qreal course, qreal speed,
                               CoordM cd = Meter, AngleM ad = Radian, SpeedM sd = Mps);

    void init();

    static INT compare (const Position& startPos, const Position& endPos);

    /*!
     * \brief setDifferenceValues
     * \param position
     */
    void setOnlyDifferenceValues (const Position& position);

    /*!
     * \fn void setOnlyChangedValues(const Position& position)
     * \brief Присваивает только те значения position, которые были изменены.
     * \details
     * \param position
     */
    void setOnlyChangedValues (const Position& position);

    void setCoord (qreal x, qreal z, CoordM cd = Meter);

    void setCoord (const QPointF& coord, CoordM cd = Meter);

    void setX (qreal x, CoordM cd = Meter);

    void setZ (qreal z, CoordM cd = Meter);

    void setHeight (qreal h, CoordM cd = Meter);

    QPointF coord (CoordM cd = Meter) const;

    qreal x (CoordM cd = Meter) const;

    qreal z (CoordM cd = Meter) const;

    qreal height (CoordM cd = Meter) const;

    qreal course (AngleM ad = Radian) const;

    qreal speed (SpeedM sd = Mps) const;

    void setCourse (qreal q, AngleM ad = Radian);

    void setSpeed (qreal v, SpeedM sd = Mps);

    void changedClear ();

    void addChange (ChangePosition mask);

    INT changedValues () const { return m_changedValues; }

//    void printDebug() const;

private:

    QPointF     m_coord;   //!< координаты (м) ( QPointF::x()->x, QPointF::y()->z )
    qreal       m_height;  //!< высота (м)
    qreal       m_course;  //!< курс (радиан)
    qreal       m_speed;   //!< скорость (м/с)
    INT         m_changedValues; //!< измененные значения

    qreal heightValidator (qreal in) const;
    qreal speedValidator (qreal in) const;
    qreal courseValidator (qreal in) const;
};

#endif /* POSITION_H_ */
