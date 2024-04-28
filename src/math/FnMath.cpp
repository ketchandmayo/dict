#include "./FnMath.hpp"
#include <QDebug>

qreal MathFunctions::normalizeDegree(qreal degree)
{
    while (degree > 360.0)
        degree -= 360.0;

    while (degree < 0.0)
        degree += 360.0;

    return degree;
}

qreal MathFunctions::acceleration (qreal startSpeed, qreal endSpeed, qreal time)
{
    // [ a = (V1 - V0) / t ]
    return (endSpeed - startSpeed) / time;
}

qreal MathFunctions::timeDistance (qreal startSpeed, qreal endSpeed, qreal distance)
{
    // [ t = 2 * S / ( V0 + V1 ) ]
    return 2.0 * distance / ( startSpeed + endSpeed );
}

qreal MathFunctions::distance (qreal startSpeed, qreal endSpeed, qreal time)
{
    // [ S = t * ( V0 + V1 ) / 2 ]
    return time * ( startSpeed + endSpeed ) / 2.0;
}

qreal MathFunctions::catet(qreal hypot, qreal cat1)
{
  if (hypot <= cat1)
      return 0.0;

  return sqrt (hypot * hypot - cat1 * cat1);
}

const QPointF MathFunctions::findCenterCircle (const QPointF &startPoint, qreal radius, qreal course, CourseChange sign )
{
    const int msign = static_cast<int> (sign);

    const qreal x = startPoint.x() - msign * radius * sin (course);
    const qreal y = startPoint.y() + msign * radius * cos (course);

    return QPointF( x, y );
}

QPointF MathFunctions::findEndArc (const QPointF &startPoint, const QPointF &centerCircle, qreal angle, CourseChange sign)
{
    const qreal msign = static_cast<qreal> (sign);
    const qreal cosd = cos (msign * angle);
    const qreal sind = sin (msign * angle);

    const QPointF bp = QPointF (startPoint.x() - centerCircle.x(), startPoint.y() - centerCircle.y());

    const qreal x = bp.x() * cosd - bp.y() * sind + centerCircle.x();
    const qreal y = bp.x() * sind + bp.y() * cosd + centerCircle.y();

    return QPointF(x, y);
}

QPointF MathFunctions::findEndLine (const QPointF &startPoint, qreal length, qreal course)
{
    const qreal x = startPoint.x() + length*cos(course);
    const qreal y = startPoint.y() + length*sin(course);

    return QPointF(x, y);
}

qreal MathFunctions::findArcAngle (qreal startCourse, qreal endCourse, CourseChange sign)
{
    qreal angleRadian = 0.0;

    const qreal dCourse = qAbs ( endCourse - startCourse );

    // если конечный курс больше начального
    if ( endCourse > startCourse)
      angleRadian = (sign == Right) ? dCourse : 2.0 * M_PI - dCourse;
    else
      angleRadian = (sign == Right) ? 2.0 * M_PI - dCourse : dCourse;

    return angleRadian;
}

CourseChange MathFunctions::findOptimalSign (qreal startCourse, qreal endCourse)
{
    const qreal rightChangeAngle = findArcAngle (startCourse, endCourse, Right);
    const qreal leftChangeAngle = findArcAngle (startCourse, endCourse, Left);

    if (rightChangeAngle < leftChangeAngle)
        return Right;

    return Left;
}

QPolygonF MathFunctions::createArcPolygonF (const QPointF& startPoint, qreal startCourse, qreal endCourse, qreal radius, CourseChange sign)
{
    QPolygonF polygon;
    const QPointF pointCenter = findCenterCircle (startPoint, radius, startCourse, sign); // точка центра окружности на которой лежит дуга
    const qreal angleDegree = radianToDegree (findArcAngle(startCourse, endCourse, sign));
    qreal currentAngle = 0.0;
    const qreal sectorAngle = 5.0;
    polygon.reserve ( static_cast<int>(angleDegree) + 1 );

    int i = 0;
    
    while (currentAngle < angleDegree)
    {
        if(i > 0)
          currentAngle += (angleDegree - currentAngle >= sectorAngle) ? sectorAngle : (angleDegree - currentAngle);
        polygon.append( findEndArc ( startPoint, pointCenter, degreeToRadian( currentAngle ), sign ) );
        ++i;
    }

    return polygon;
}

bool MathFunctions::circleContainPoint (const QPointF& point, const QPointF& centerCircle, qreal radius )
{
    const QPointF bpoint = point - centerCircle; // точка относительно центра окружности
    const qreal length = sqrt( bpoint.x() * bpoint.x() + bpoint.y() * bpoint.y() );

    return ( length <= radius ) ? true : false;
}

QTime MathFunctions::timeFromSec (Time sec)
{
    int i_sec = static_cast<int>(sec);
    int h = i_sec / 3600;
    int m = (i_sec % 3600) / 60;
    int s = (i_sec % 3600) % 60;

    return QTime (h, m, s);
}

Time MathFunctions::timeToSec (const QTime& time)
{
    Time timeSec = static_cast<Time> ( time.hour() * 3600 + time.minute() * 60 + time.second() );

    return timeSec;
}

qreal MathFunctions::pomexa (qreal dxx, uint addValue)
{
    qreal sum = 0.0;

    for( int i = 0; i < 8; i++ )
    {
        const uint seed = QDateTime::currentDateTime ().toTime_t () - addValue + i * 2;
        qsrand (seed);

        sum += static_cast<qreal>( 1 + qrand() % 200 ) / 100.0 - 1.0;
    }

    sum /= 8.0;

    return (dxx * sum);
}

qreal MathFunctions::azimuth(const QPointF& coord, AngleM angleM)
{
        qreal x = coord.x();
        qreal y = coord.y();
        qreal c = sqrt( x*x + y*y );

        qreal angle = 0.0;

    angle = radianToDegree ( acos( x/c ) );

    if(y < 0.0)
        angle = 360.0 - radianToDegree ( acos( x/c ) );

    return (angleM == Gradus) ? angle : degreeToRadian(angle);
}

qreal MathFunctions::overload (qreal startSpeed, qreal endSpeed, qreal radius)
{
    qreal maxSpeed = qMax(startSpeed, endSpeed);

    return radius >= 1.0 ? sqrt ( maxSpeed * maxSpeed * maxSpeed * maxSpeed / (radius * radius * G * G) + 1.0 )  : 1.0;
}

qreal MathFunctions::validatorPI (qreal alfa)
{
  while (alfa < (-PI))
      alfa += PI2;

  while (alfa > PI)
      alfa -= PI2;

  return alfa;
}

qreal MathFunctions::validator2PI (qreal alfa)
{
    while (alfa < 0.0)
        alfa += PI2;

    while (alfa > PI2)
        alfa -= PI2;

    return alfa;
}

QPointF MathFunctions::vector (const QPointF& startPoint, const QPointF& endPoint)
{
    return endPoint - startPoint;
}

qreal MathFunctions::vectorLength (const QPointF& vector)
{
    return sqrt ( vector.x() * vector.x() + vector.y() * vector.y() );
}

QPainterPath MathFunctions::lineShape(const QPointF& startPoint, const QPointF& endPoint, qreal width)
{
    QPointF vec = vector(startPoint, endPoint);
    QPointF reverseVec = vector(endPoint, startPoint);

    qreal course = azimuth(vec, Radian);
    qreal reverseCourse = azimuth(reverseVec, Radian);

    QPolygonF polygon;

    polygon.append( findCenterCircle( startPoint, width, course, Right) );
    polygon.append( findCenterCircle( endPoint,   width, course, Right) );
    polygon.append( findCenterCircle( endPoint,   width, reverseCourse, Right) );
    polygon.append( findCenterCircle( startPoint, width, reverseCourse, Right) );

    QPainterPath path;

    path.addPolygon(polygon);

    return path;
}

QPainterPath  MathFunctions::polylineShape (const QPolygonF& polyline, qreal width)
{
    QPolygonF polygon;
    QPainterPath path;

    if (polyline.count () >= 2)
    {
        int count = 1;

        for (int i = 0; i < polyline.count () - 1; ++i)
        {
            QPointF startPoint = polyline [i];
            QPointF endPoint = polyline [i+1];

            qreal course = azimuth ( vector(startPoint, endPoint ), Radian );

            polygon.append( findCenterCircle( startPoint, width, course, Right) );
            polygon.append( findCenterCircle( endPoint,   width, course, Right) );

            count++;
        }

        for (int i = polyline.count () - 1; i > 0; --i)
        {
            QPointF startPoint = polyline [i];
            QPointF endPoint = polyline [i-1];

            qreal course = azimuth ( vector(startPoint, endPoint ), Radian );

            polygon.append(findCenterCircle( startPoint, width, course, Right));
            polygon.append(findCenterCircle( endPoint,   width, course, Right));

            count++;
        }

        if(!polygon.isEmpty())
            polygon.append( polygon.first() );
    }

    path.addPolygon(polygon);

    return path;
}

QPolygonF MathFunctions::arcBetweenLines (const QPointF& startPoint, const QPointF& middlePoint, const QPointF& endPoint, qreal radius)
{
    QPointF vec1 = vector (startPoint, middlePoint);
    QPointF vec2 = vector (middlePoint, endPoint);

    qreal length1 = vectorLength (vec1);
    qreal length2 = vectorLength (vec2);

    qreal az1 = degreeToRadian (azimuth (vec1));
    qreal az2 = degreeToRadian (azimuth (vec2));

    CourseChange ch = findOptimalSign (az1, az2);
    qreal angleAlpha = findArcAngle (az1, az2, ch);
    qreal betaAngle = degreeToRadian (90.0) - angleAlpha / 2.0;
    qreal lengthAC = 2.0 * radius * cos(betaAngle) / 2.0;
    qreal length = lengthAC / sin(betaAngle);
    qreal minLength = qMin(length1, length2) / 2.0;

    if (length > minLength)
    {
        QPointF start = findEndLine (middlePoint, -minLength, az1);
        QPointF end = findEndLine (middlePoint, minLength, az2);
        qreal vecLength = vectorLength (vector(start, end)) / 2.0;
        radius = vecLength / cos(betaAngle);
        length = minLength;
    }

    QPointF startArc = findEndLine (middlePoint, -length, az1);

    return createArcPolygonF (startArc, az1, az2, radius, ch);
}

qreal MathFunctions::overload (const qreal speed, const qreal radius)
{
    const qreal rollAngle = atan(sqr(speed)/radius*G);
    return (1.0/cos(rollAngle));
}

qreal MathFunctions::turnRadius (const qreal speed, const qreal overload)
{
    const qreal rollAngle = acos(1.0/overload);
    return (sqr(speed)/(tan(rollAngle)*G));
}
