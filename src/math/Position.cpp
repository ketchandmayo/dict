#include "./Position.hpp"

Position::Position()
{
    init();
}

Position::Position(qreal x, qreal z, CoordM cd)
{
    m_height = 0.0;
    m_course = 0.0;
    m_speed = 0.0;
    m_changedValues = NoChange;
    setCoord(x, z, cd);
}

Position::Position(const QPointF& coord, CoordM cd)
{
    m_height = 0.0;
    m_course = 0.0;
    m_speed = 0.0;
    m_changedValues = NoChange;
    setCoord(coord, cd);
}

Position::Position(qreal x, qreal z, qreal height, CoordM cd)
{
    m_course = 0.0;
    m_speed = 0.0;
    m_changedValues = NoChange;
    setCoord(x, z, cd);
    setHeight(height, cd);
}

Position::Position(const QPointF& coord, qreal height, CoordM cd)
{
    m_course = 0.0;
    m_speed = 0.0;
    m_changedValues = NoChange;
    setCoord(coord, cd);
    setHeight(height, cd);
}

Position::Position(qreal x, qreal z, qreal height, qreal course, qreal speed,
                           CoordM cd, AngleM ad, SpeedM sd)
{
    m_changedValues = NoChange;
    setCoord(x, z, cd);
    setHeight(height, cd);
    setCourse(course, ad);
    setSpeed(speed, sd);
}

Position::Position(const QPointF& pos, qreal height, qreal course, qreal speed,
                           CoordM cd, AngleM ad, SpeedM sd)
{
    m_changedValues = NoChange;
    setCoord(pos, cd);
    setHeight(height, cd);
    setCourse(course, ad);
    setSpeed(speed, sd);
}

void Position::init()
{
    m_coord = QPointF();
    m_height = 0.0;
    m_course = 0.0;
    m_speed = 0.0;
    m_changedValues = NoChange;
}

INT Position::compare(const Position& startPos, const Position& endPos)
{
    INT  diffValue = 0;

    qreal startX = startPos.x();
    qreal endX = endPos.x();

    qreal startZ = startPos.z();
    qreal endZ = endPos.z();

    qreal startCourse = startPos.course();
    qreal endCourse = endPos.course();

    qreal startHeight = startPos.height();
    qreal endHeight = endPos.height();

    qreal startSpeed = startPos.speed();
    qreal endSpeed = endPos.speed();

    qreal xDifference = endX - startX;
    qreal zDifference = endZ - startZ;
    qreal courseDifference = endCourse - startCourse;
    qreal heightDifference = endHeight - startHeight;
    qreal speedDifference = endSpeed - startSpeed;

    if( qAbs(courseDifference) > 0.01 )
        diffValue |= 1;

    if( qAbs(heightDifference) > 0.01 )
        diffValue |= 2;

    if( qAbs(speedDifference) > 0.01 )
        diffValue |= 4;

    if( qAbs(xDifference) > 0.01 )
        diffValue |= 8;

    if( qAbs(zDifference) > 0.01 )
         diffValue |= 16;

    return diffValue;
}

void Position::setOnlyDifferenceValues(const Position& position)
{    
    INT diffValue = compare(*this, position);

    if(diffValue & 1)
        setCourse(position.course(Radian), Radian);

    if(diffValue & 2)
        setHeight(position.height(Meter), Meter);

    if(diffValue & 4)
        setSpeed(position.speed(Mps));

    if(diffValue & 8)
        setX(position.x(Meter), Meter);

    if(diffValue & 16)
        setZ(position.z(Meter), Meter);
}

void Position::setOnlyChangedValues(const Position& position)
{
    if(position.m_changedValues == AllChange)
    {
        setCoord(position.coord());
        setHeight(position.height());
        setCourse(position.course());
        setSpeed(position.speed());
        return;
    }

    if((position.m_changedValues & CoordChange) == CoordChange)
        setCoord(position.coord());

    else if(position.m_changedValues & XChange)
        setX(position.x());

    else if(position.m_changedValues & ZChange)
        setZ(position.z());

    if(position.m_changedValues & HeightChange)
        setHeight(position.height());

    if(position.m_changedValues & CourseChange)
        setCourse(position.course());

    if(position.m_changedValues & SpeedChange)
        setSpeed(position.speed());
}

void Position::setCoord(qreal x, qreal z, CoordM cd)
{
    m_coord = (cd == Meter) ? QPointF(x, z) : coordKmToMeter(x, z);

    m_changedValues |= CoordChange;
}

void Position::setCoord(const QPointF& coord, CoordM cd)
{
    m_coord = (cd == Meter) ? coord : coordKmToMeter(coord);
    m_changedValues |= CoordChange;
}

void Position::setX(qreal x, CoordM cd)
{
    m_coord.setX( (cd == Meter) ? x : kmToMeter(x) );
    m_changedValues |= XChange;

}

void Position::setZ(qreal z, CoordM cd)
{
    m_coord.setY( (cd == Meter) ? z : kmToMeter(z) );
    m_changedValues |= ZChange;
}

void Position::setHeight(qreal h, CoordM cd)
{
    qreal val = (cd == Meter) ? h : kmToMeter(h);

    m_height = heightValidator(val);

    m_changedValues |= HeightChange;
}

QPointF Position::coord(CoordM cd) const
{
    return (cd == Meter) ? m_coord : coordMeterToKm(m_coord);
}

qreal Position::x(CoordM cd) const
{
    return (cd == Meter) ? m_coord.x() : meterToKm(m_coord.x());
}

qreal Position::z(CoordM cd) const
{
    return (cd == Meter) ? m_coord.y() : meterToKm(m_coord.y());
}

qreal Position::height(CoordM cd) const
{
    return (cd == Meter) ? m_height : meterToKm(m_height);
}

qreal Position::course(AngleM ad) const
{
    return (ad == Radian) ? m_course : radianToDegree(m_course);
}

qreal Position::speed(SpeedM sd) const
{
    return (sd == Mps) ? m_speed : mpsToKmpMin(m_speed);
}

void Position::setCourse(qreal q, AngleM ad)
{
    qreal val = (ad == Radian) ? q : degreeToRadian(q);
    m_course = courseValidator(val);
    m_changedValues |= CourseChange;
}

void Position::setSpeed(qreal v, SpeedM sd)
{

    qreal val = (sd==Mps) ? v : kmpMinToMps(v);

    m_speed = speedValidator(val);

    m_changedValues |= SpeedChange;
}

void Position::changedClear()
{
    m_changedValues = NoChange;
}

void Position::addChange(ChangePosition mask)
{
    m_changedValues |= mask;
}

qreal Position::heightValidator(qreal in) const
{
    qreal out = in;
    if(in < 0.0)
        out = 0.0;

    return out;
}

qreal Position::speedValidator(qreal in) const
{
    qreal out = in;

    if(in < 0.0)
        out = 0.0;

    if(in > 2777.5)
        out = 2777.5;

    return out;
}

qreal Position::courseValidator(qreal in) const
{
    return validator2PI(in);
}

//void Position::printDebug() const
//{
//    qDebug() << "Coord =" << coord(Km);
//    qDebug() << "Height =" << height(Km);
//    qDebug() << "Speed =" << speed(KmpMin);
//    qDebug() << "Course =" << course(Gradus);
//    qDebug() << "";
//}
