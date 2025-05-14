#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <qvectornd.h>
class BezierCurve
{
public:
    BezierCurve();
    QVector3D evaluateBezier(float t);
    QVector3D c[4];
};

#endif // BEZIERCURVE_H
