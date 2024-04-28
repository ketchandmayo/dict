#ifndef FN_MATH_H_
#define FN_MATH_H_

#include <QtGlobal>
#include <math.h>
#include <QPointF>
#include <QRectF>
#include <QPolygonF>
#include <QPainterPath>
#include <QTime>
//#include "../uns/uns.hpp"

typedef qreal Time;
typedef qint16 INT;

static const qreal G    = 9.8;        // ускорение свободного падения 9.8 м/с^2
static const qreal PI2  = M_PI * 2.0; // два пи,
static const qreal PI   = M_PI;       // пи,
static const qreal PI_2 = M_PI/2.0;   // пи пополам,

enum LengthMeasure
{
    Meter = 0,
    Km = 1
};

enum AngleMeasure
{
    Radian = 0,
    Gradus = 1
};

enum SpeedMeasure
{
    Mps = 0,
    KmpMin = 1
};

/*!
 * @enum PathTracing
 * @brief Обход для маневра по курсу
 */
enum CourseChange
{
    Left        = -1,  //!< Слева
    Right       =  1   //!< Справа
};

namespace MathFunctions
{
        typedef LengthMeasure LengthM;
        typedef LengthMeasure CoordM;
        typedef AngleMeasure AngleM;
        typedef SpeedMeasure SpeedM;

        inline qreal sqr(qreal value) { return value*value; }

        /*!
         * @brief Kilometer (км) Переводит значение расстояния из метров в километры
         * @param metr - скорость в метрах
         */
        inline qreal meterToKm(qreal metr) { return metr/1000.0; }

        /*!
         * @brief Meter (м) Переводит значение расстояния из километров в метры
         * @param kmetr - скорость в километрах
         */
        inline qreal kmToMeter(qreal kmetr) { return kmetr*1000.0; }

        /*!
         * @brief Coordinate in Kilometer (Координаты точки в км)
         *       Переводит значение координат точки из метров в километры
         * @param coordm - координаты точки в метрах
         */
        inline const QPointF coordMeterToKm(const QPointF& coordm) { return coordm/1000.0; }

        /*!
         * @brief Coordinate in Kilometer (Координаты точки в км)
         *       Переводит значение координат точки из метров в километры
         * @param xm - координата x точки в метрах
         * @param ym - координата y точки в метрах
         */
        inline const QPointF coordMeterToKm(qreal xm, qreal ym) { return QPointF(meterToKm(xm), meterToKm(ym)); }

        /*!
         * @brief Coordinate in meter (Координаты точки в м)
         *       Переводит значение координат точки из километров в метры
         * @param coordkm - координаты точки в километрах
         */
        inline const QPointF coordKmToMeter(const QPointF& coordkm) { return coordkm*1000.0; }

        /*!
         * @brief Coordinate in meter (Координаты точки в м)
         *       Переводит значение координат точки из километров в метры
         * @param xkm - координата x точки в метрах
         * @param ykm - координата y точки в метрах
         */
        inline const QPointF coordKmToMeter(qreal xkm, qreal ykm) { return QPointF(kmToMeter(xkm), kmToMeter(ykm)); }

        /*!
         * @brief Radian Переводит значение угла из градусов в радианы
         * @param gradus - угол в градусах
         */
        inline qreal degreeToRadian(qreal degree) { return degree/180.0*M_PI; }

        /*!
         * @brief Gradus Переводит значение угла из радиан в градусы
         * @param radian - угол в радианах
         */
        inline qreal radianToDegree(qreal radian) { return radian*180.0/M_PI; }
        /*!
         * @brief normalizeDegree нормализует значение угла
         * @param radian - угол в градусах
         */
        qreal normalizeDegree(qreal degree);

        /*!
         * @brief Kilometer per min (kmpmin) Переводит значение скорости из м/с в км/мин
         * @param kmphToMps - скорость м/с
         */
        inline qreal mpsToKmpMin(qreal mps) { return mps*0.06; }

        /*!
         * @brief Meter per second (mps) Переводит значение скорости из км/мин в м/с
         * @param mpsToKmpMin - скорость км/мин
         */
        inline qreal kmpMinToMps(qreal kmph) { return kmph/0.06; }

        /*!
         * @brief Catet(катет) находит неизвестный катет прямоугольного треугольника
         * @param hypot - гиппотенуза
         * @param cat1 - известный катет
         */
        inline qreal catet(qreal hypot, qreal cat1);

        /*!
         * @brief acceleration (ускорения) находит ускорение
         * @param startSpeed - началная скорость участка
         * @param endSpeed - конечная скорость участка
         * @param time -время участка
         * @details [ a = (V1 - V0) / t ];
         */
        qreal acceleration(qreal startSpeed, qreal endSpeed, qreal time);

        /*!
         * @brief timeDistance (веремя участка) находит время участка
         * @param startSpeed - началная скорость участка
         * @param endSpeed - конечная скорость участка
         * @param length - длина участка
         * @details [ S = V0 * t + ( a * t^2 ) / 2 ] => [ t = 2 * S / ( V0 + V1 ) ];
         */
        qreal timeDistance(qreal startSpeed, qreal endSpeed, qreal distance);

        /*!
         * @brief distance (расстояние) находит расстояние участка
         * @param startSpeed - началная скорость участка
         * @param endSpeed - конечная скорость участка
         * @param time -время участка
         * @details [ S = V0 * t + ( a * t^2 ) / 2 ] => [ t = 2 * S / ( V0 + V1 ) ] => [ S = t * ( V0 + V1 ) / 2 ];
         */
        qreal distance(qreal startSpeed, qreal endSpeed, qreal time);


        /*!
         *@brief Находит центр окружности, на которой лежит дуга маневра по курсу
         * @param radius - радиус окружности (метры)
         * @param startPoint - точка начала маневра по курсу (координаты в метрах)
         * @param course - курс движения в радианах
         * @param sign положения окружности (Clockwise - по часовой, AntiClockwise - против часовой)
         * @return координаты центра окружности
         */
        const QPointF findCenterCircle(const QPointF &startPoint, qreal radius, qreal course, CourseChange sign);

        /*!
         *@brief Находит точку конца дуги
         * @param startPoint - точка начала дуги
         * @param center_c центр окружности, на которой лежит дуга
         * @param angle угол дуги (радиан)
         * @return точка конца дуги
         */
        QPointF findEndArc(const QPointF &startPoint, const QPointF &centerCircle, qreal angle, CourseChange sign);

        /*!
         * @brief Находит точку после движения по прямой заданного растояния
         * @param startPoint начальная точка
         * @param length длинна линии
         * @param course направление линии (радиан)
         * @return конечная точка линии
         */
        QPointF findEndLine(const QPointF &startPoint, qreal length, qreal course);

        /*!
         * @brief Находит угол дуги
         */
        qreal findArcAngle(qreal startCourse, qreal endCourse, CourseChange sign);

        /*!
         * \brief findOptimalSign
         */
        CourseChange findOptimalSign(qreal startCourse, qreal endCourse);

        /*!
         *@brief Находит точки для построения дуги и записывает их в QPolygonF
         * @param rect охватывающий прямоугольник
         * @param polygon полигон точек, в который записываются найденные точки
         * @param p точка косания окружности (начало вектора)
         * @param angle угол дуги
         * @param r радиус
         * @param sc курс движения (направление вектора) в радианах
         * @param _sign положения окружности (true - слева, false - справа)
         */
        QPolygonF createArcPolygonF(const QPointF& startPoint, qreal startCourse, qreal endCourse, qreal radius, CourseChange sign);

        /*!
         *@brief Возвращает true, если точка-point в окружность с центром-centr и радиусом-radius
         * @param point точка для проверки вхождения
         * @param centerCircle точка центра окружности
         * @param radius радиус окружности
         */
        bool circleContainPoint(const QPointF& point, const QPointF& centerCircle, qreal radius );

        /*!
         * @brief Преобразует секунды во время QTime формата "часы:минуты:секунды"
         * @param sec секунды
         * @return время формата "часы:минуты:секунды"
         */
        QTime timeFromSec(Time sec);

        Time timeToSec(const QTime& time);

        qreal pomexa(qreal dxx, uint addValue);

        qreal azimuth(const QPointF& coord, AngleM angleM = Gradus);

        /*!
         *  @brief overload(qreal startSpeed, qreal endSpeed, qreal radius)
         *  @details P = SQRT( ( MAX_SPEED^4 / R^2 * G^2 ) + 1 );
         */
        qreal overload (qreal startSpeed, qreal endSpeed, qreal radius);

        qreal validatorPI (qreal alfa);

        qreal validator2PI (qreal alfa);

        QPointF vector (const QPointF& startPoint, const QPointF& endPoint);

        /*!
         * \brief lineShape
         * \param startPoint
         * \param endPoint
         * \param width
         * \return
         */
        QPainterPath lineShape(const QPointF& startPoint, const QPointF& endPoint, qreal width = 5.0);

        QPainterPath polylineShape(const QPolygonF& polyline, qreal width = 5.0);

        /*!
         * \brief vectorLength
         * \param vector
         * \return
         */
        qreal vectorLength (const QPointF& vector);


        /*!
         * \brief arcBetweenLines - получает дугу между двумя пересекающимися пямыми
         * \param startPoint - точка начала первой прямой
         * \param middlePoint - точка пересечения двух прямых
         * \param endPoint - точка начала второй прямой
         * \param radius - радиус окружности, на которой лежит дуга
         * \return массив точек
         */
        QPolygonF arcBetweenLines (const QPointF& startPoint, const QPointF& middlePoint, const QPointF& endPoint, qreal radius );

        /*!
         * \brief overload коэффициент перегрузки при разворте(вираже летательного аппарата)
         * \param speed - горизонтальная скорость
         * \param radius - радиус разворота(виража)
         * \return коэффициент перегрузки
         */
        qreal overload (qreal speed, qreal radius);

        /*!
         * \brief turnRadius радиус разворота летательного аппарата
         * \param speed - горизонтальная скорость
         * \param overload - максимальный коэффициент перегрузки
         * \return радиус разворота (м)
         */
        qreal turnRadius (qreal speed, qreal overload);
}

using namespace MathFunctions;

#endif /* TRANAG_MATH_H_ */
