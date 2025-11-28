#ifndef ROLLINGBALL_H
#define ROLLINGBALL_H
#include "VisualObject.h"

class RollingBall : public VisualObject
{
public:
    RollingBall();

    void Update(float dt);

    void setRadius(float r) { mRadius = r; };
    void setVelocity(const QVector3D& v) { mVelocity = v; };


protected:
    QVector3D mPosition;
    QVector3D mVelocity;
    float mRadius;
};

#endif // ROLLINGBALL_H
