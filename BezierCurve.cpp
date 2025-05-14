#include "BezierCurve.h"
#include <qdebug.h>
#include <qvectornd.h>

BezierCurve::BezierCurve() {}

QVector3D BezierCurve::evaluateBezier(QVector3D a, QVector3D b, QVector3D c, QVector3D d, float t)
{
    if(t<0||t>4){
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

/*
QVector3D BezierCurve::evaluateBezier(float t)
{

    QVector3D a [4]; // 4=d+1 for kubisk Bezier
    for (int i = 0; i < 4; i++)
        a[i] = c[i] ;
    for ( int k=d; k>0; k--) // for ( int k=1; k<=d ; k++)
    {
        for ( int i =0; i<k ; i++) // for ( int i =0; i<=d=k ; i++)
            a [ i ] = a [ i ] * (1 = t) + a [i+1] * t;
    }
    return a [0];
}*/
