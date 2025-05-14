#include "BezierCurve.h"
#include <qvectornd.h>

BezierCurve::BezierCurve() {}


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
