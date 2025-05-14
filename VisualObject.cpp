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

void VisualObject::setPositionby2DVector(QVector2D &newPosition)
{
    mPosition = {newPosition.x(), mPosition.y(), newPosition.y()};
    mMatrix.setToIdentity();
    mMatrix.translate({newPosition.x(), mPosition.y(), newPosition.y()});
}


QVector3D VisualObject::evaluateBezier(QVector3D a, QVector3D b, QVector3D c, QVector3D d, float t)
{
    if(t>-0.1||t<4.1){
        QVector3D P = (1-t)*a + t*b;
        QVector3D Q = (1-t)*b + t*c;
        QVector3D R = (1-t)*c + t*d;

        QVector3D PQ = (1-t)*P + t*Q;
        QVector3D QR = (1-t)*Q + t*R;

        QVector3D PQR = (1-t)*PQ + t*QR;

        return PQR;
    }
    else{
        qDebug()<<"Failed to Beizer, gave you a 0.";
        return {0, 0, 0};
    }
}

QVector3D VisualObject::followTarget(QVector3D target, float time)
{
        QVector3D path = (1-time)*mPosition + time*target;
        return path;
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
    //qDebug()<< "distance:" << Dist;
    float spotDist = /*other->*/mRadius+Range;
    if (Dist < spotDist) {
        //qDebug("object is colliding");
        return true;
    }

    else { return false; };
}
