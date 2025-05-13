#include "VisualObject.h"

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();
}

void VisualObject::move(float x, float y, float z)
{
    QVector3D add;
    add.setX(x); add.setY(y); add.setZ(z);
    mMatrix.translate(x, y, z);
    mPosition+=add;
}

void VisualObject::scale(float s)
{
    mMatrix.scale(s);
}

void VisualObject::scale2(float x, float y)
{
    mMatrix.scale(x, y);
}

void VisualObject::scale3(float x, float y, float z)
{
    mMatrix.scale(x, y, z);
}

void VisualObject::rotate(float t, float x, float y, float z)
{
    mMatrix.rotate(t, x, y, z);
}

QVector3D VisualObject::getPosition()
{
    float x = mMatrix(0, 3); // Position in the x-axis
    float y = mMatrix(1, 3); // Position in the y-axis
    float z = mMatrix(2, 3); // Position in the z-axis
    return QVector3D(x, y, z);
}

void VisualObject::setPosition(float x, float y, float z)
{
    mMatrix(0, 3) = x; // Position in the x-axis
    mMatrix(1, 3) = y; // Position in the y-axis
    mMatrix(2, 3) = z; // Position in the z-axis
}

void VisualObject::setPositionbyVector(const QVector3D &newPosition)
{
    mPosition = newPosition;
    mMatrix.setToIdentity();
    mMatrix.translate(newPosition);
}




bool VisualObject::isColliding(QVector3D Position, float Radius)
{
    QVector3D VectorDist = /*other->*/mPosition - Position;
    float Dist = VectorDist.length();
    float minDist = /*other->*/mRadius+Radius;
    if (Dist < minDist) {
        return true;
    }

    else { return false; };
}

bool VisualObject::isWithinRange(QVector3D Position, float Range)
{
    QVector3D VectorDist = /*other->*/mPosition - Position;
    float Dist = VectorDist.length();
    qDebug()<< "distance:" << Dist;
    float spotDist = /*other->*/mRadius+Range;
    if (Dist < spotDist) {
        //qDebug("object is colliding");
        return true;
    }

    else { return false; };
}
