#include "Enemy.h"

#include <math.h>

Enemy::Enemy(InfoOverlapHandler* listner, std::string name, Vertex ControlPoints[]) : AbstractObjectInteract(listner, name, {0, 0, 0, 0, 0, 0, 0, 0}, 1)
{
    bDisplay=0;
    Init();
    VisualObject::mName = name;

    Enemy::ControlPoints[0] = ControlPoints[0];
    Enemy::ControlPoints[1] = ControlPoints[1];
    Enemy::ControlPoints[2] = ControlPoints[2];

    Vertex StartPoint = ControlPoints[0];
    move(StartPoint.x, StartPoint.y, StartPoint.z);
    bDisplay=1;
}

void Enemy::Init()
{
    Vertex vA{ -0.5f, 0.0f, 0.0f,   0.8f, 0.2f, 0.3f,       0.0f, 0.0f };   //A
    Vertex vB{ 0.5f, 0.5f, 0.0f,    0.7f, 0.1f, 0.15f,      0.0f, 0.0f };   //B
    Vertex vC{ 0.5f, -0.5f, 0.0f,   0.8f, 0.8f, 0.7f,       0.0f, 0.0f };   //C
    Vertex vD{ 1.5f, 0.0f, 0.0f,    0.85f, 0.25f, 0.4f,     0.0f, 0.0f };   //D
    Vertex vE{ -1.5f, 0.5f, 0.0f,   0.8f, 0.2f, 0.3f,       0.0f, 0.0f };   //E
    Vertex vF{ -1.5f, -0.5f, 0.0f,  0.7f, 0.8f, 0.75f,      0.0f, 0.0f };   //F
    Vertex vG{ 0.5f, 0.0f, 0.5f,    0.8f, 0.2f, 0.3f,       0.0f, 0.0f };   //G
    Vertex vH{ 0.5f, 0.0f, -0.5f,   0.8f, 0.2f, 0.3f,       0.0f, 0.0f };   //H
    Vertex vI{ -1.25f, 0.0f, 0.0f,  0.85f, 0.25f, 0.4f,     0.0f, 0.0f };   //I



    mVertices.push_back(vA);
    mVertices.push_back(vB);
    mVertices.push_back(vG);

    mVertices.push_back(vA);
    mVertices.push_back(vB);
    mVertices.push_back(vH);

    mVertices.push_back(vD);
    mVertices.push_back(vB);
    mVertices.push_back(vG);

    mVertices.push_back(vD);
    mVertices.push_back(vB);
    mVertices.push_back(vH);
    //
    mVertices.push_back(vA);
    mVertices.push_back(vG);
    mVertices.push_back(vC);

    mVertices.push_back(vA);
    mVertices.push_back(vH);
    mVertices.push_back(vC);

    mVertices.push_back(vD);
    mVertices.push_back(vG);
    mVertices.push_back(vC);

    mVertices.push_back(vD);
    mVertices.push_back(vH);
    mVertices.push_back(vC);
    //
    mVertices.push_back(vE);
    mVertices.push_back(vI);
    mVertices.push_back(vA);

    mVertices.push_back(vF);
    mVertices.push_back(vA);
    mVertices.push_back(vI);
}

void Enemy::Tick(float deltaTime)
{
    lifeTime+=deltaTime;
    UpdateT(deltaTime);

    Vertex deltaCoordinates = CalculateVectorToTPoint();

    move(deltaCoordinates.x, deltaCoordinates.y, deltaCoordinates.z);
}



Vertex Enemy::CalculateTPoint()
{
    float x = (1 - t) * (1 - t) * ControlPoints[0].x + 2 * (1 - t) * t * ControlPoints[1].x + t * t * ControlPoints[2].x;
    float y = (1 - t) * (1 - t) * ControlPoints[0].y + 2 * (1 - t) * t * ControlPoints[1].y + t * t * ControlPoints[2].y;
    float z = (1 - t) * (1 - t) * ControlPoints[0].z + 2 * (1 - t) * t * ControlPoints[1].z + t * t * ControlPoints[2].z;

    return {x, y, z, 0.f, 0.f, 0.f, 0.f, 0.f};
}

void Enemy::UpdateT(float deltaTime)
{
    float amplitude=0.5;
    t = (2 * amplitude / M_PI) * std::asin(std::sin(2 * (M_PI / patrolTime) * lifeTime)) + amplitude;
}

void Enemy::Interact(PlayerStat *interactor)
{
    interactor->Damage();
}



Vertex Enemy::CalculateVectorToTPoint()
{
    Vertex TPoint = CalculateTPoint();

    float deltaX = TPoint.x-OverlapCenter.x;
    float deltaY = TPoint.y-OverlapCenter.y;
    float deltaZ = TPoint.z-OverlapCenter.z;
    return {deltaX, deltaY, deltaZ, 0, 0, 0, 0, 0};
}
