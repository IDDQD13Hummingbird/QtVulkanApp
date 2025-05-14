#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <qvectornd.h>
class BezierCurve
{
public:
    BezierCurve();
    QVector3D evaluateBezier(QVector3D a, QVector3D b, QVector3D c, QVector3D d, float t);
};

#endif // BEZIERCURVE_H
