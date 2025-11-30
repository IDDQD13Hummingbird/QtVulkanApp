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
////////////////

class Mesh;
class Terrain;

class BSplineCurve
{
public:
    // Determines how many control points influence each segment and
    // how smooth the curve is
    // f. ex. d = 3 would mean a cubic B-spline.
    int degree = 3;
    std::vector<float> t = {0, 0, 0, 1, 2, 2, 2}; // knot vector, the length of t should be n + d + 2
    std::vector<QVector3D> controlPoints = {QVector3D(0, 0, 0), QVector3D(0.0f, -0.2f,  1.0f), QVector3D(1, -0.5, 0), QVector3D(1, -0.4,  1)};
    //controlPoints = {};

private:
    float findKnotInterval(float x)
    {
        if(x == 1.5){
            return 3;
        }
        else if(x == 2){
            return 2;
        }
        else{
            /*qDebug() << x;
        int my = sizeof(controlPoints) - 1; // indekstilsistekontrollpunkt

        while (x < t[my])
        {
            my--;
        }

        return my;*/
            return 3;
        }
    }

public:
    QVector3D EvaluateBSplineSimple(float x)
    {
        int my = findKnotInterval(x);
        std::vector<QVector3D> a;

        a.resize(degree+1);

        for (int i = 0; i <= degree; i++)
        {
            a[degree-i] = controlPoints[my-i];
        }

        for (int k = degree; k > 0; k--)
        {
            int j = my - k;

            for (int i = 0; i < k; i++)
            {
                j++;

                float w = (x - t[j])/(t[j+k] - t[j]);

                a[i] = a[i] * (1-w) + a[i+1] * w;
            }
        }

        return a[0];
    }
};
/*
class RollingBall : public TriangleSurface
{
public:
    RollingBall();
    void Init();
    void Update();
    float t1 = 1.5;
    float t2 = 2.5;
    BSplineCurve curve;
    float mass = 0.05;
    glm::vec3 velocity;
    glm::vec3 gravity = glm::vec3(0, -0.98, 0);
    glm::vec3 updateVelocity(float tan){
        return glm::vec3(
            mass * curve.EvaluateBSplineSimple(tan).x,
            mass * gravity.y * curve.EvaluateBSplineSimple(tan).y,
            mass * curve.EvaluateBSplineSimple(tan).z); };*//*

    glm::vec3 updateVelocity(float tan){
        return glm::vec3(
            mass * tan,
            mass * tan * gravity.y,
            mass * tan); };
*//*
    Terrain* terrainMesh;
    Mesh* ballMesh;
};
*/
};

#endif // ROLLINGBALL_H
