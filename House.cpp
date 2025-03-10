#include "House.h"


void House::Init()
{
    Vertex LeftBottomBack{  -4.0f, -4.0f, -4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex RightBottomBack{  4.0f, -4.0f, -4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex LeftTopBack{     -4.0f,  4.0f, -4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex RightTopBack{     4.0f,  4.0f, -4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex LeftBottomFront{ -4.0f, -4.0f,  4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex RightBottomFront{ 4.0f, -4.0f,  4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex LeftTopFront{    -4.0f,  4.0f,  4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};
    Vertex RightTopFront{    4.0f,  4.0f,  4.0f,  0.4f, 0.2f, 0.0f, 0.0f, 0.0f};

    //Right
    mVertices.push_back(RightBottomFront);
    mVertices.push_back(RightBottomBack);
    mVertices.push_back(RightTopBack);

    mVertices.push_back(RightBottomFront);
    mVertices.push_back(RightTopBack);
    mVertices.push_back(RightTopFront);

    //Left
    mVertices.push_back(LeftBottomBack);
    mVertices.push_back(LeftBottomFront);
    mVertices.push_back(LeftTopBack);

    mVertices.push_back(LeftTopBack);
    mVertices.push_back(LeftBottomFront);
    mVertices.push_back(LeftTopFront);

    //Top
    mVertices.push_back(LeftTopFront);
    mVertices.push_back(RightTopFront);
    mVertices.push_back(RightTopBack);

    mVertices.push_back(LeftTopFront);
    mVertices.push_back(RightTopBack);
    mVertices.push_back(LeftTopBack);

    //Bottom
    mVertices.push_back(RightBottomBack);
    mVertices.push_back(RightBottomFront);
    mVertices.push_back(LeftBottomFront);

    mVertices.push_back(LeftBottomBack);
    mVertices.push_back(RightBottomBack);
    mVertices.push_back(LeftBottomFront);

    //Front
    mVertices.push_back(LeftBottomFront);
    mVertices.push_back(RightBottomFront);
    mVertices.push_back(RightTopFront);

    mVertices.push_back(LeftBottomFront);
    mVertices.push_back(RightTopFront);
    mVertices.push_back(LeftTopFront);

    //Back
    mVertices.push_back(RightTopBack);
    mVertices.push_back(RightBottomBack);
    mVertices.push_back(LeftBottomBack);

    mVertices.push_back(LeftBottomBack);
    mVertices.push_back(LeftTopBack);
    mVertices.push_back(RightTopBack);
}

House::House(IOverlapHandler *listner, float x, float y, float z, std::string name) : AbstractInteractObject(listner, name, {0, 0, 0, 0, 0, 0, 0, 0}, 4)
{
    bDisplay=0;

    Init();
    move(x, y, z);

    bDisplay=1;
}

void House::Interact(IPlayer *interactor)
{
    float xDirection = interactor->GetPosition().x() - OverlapCenter.x;
    float yDirection = interactor->GetPosition().y() - OverlapCenter.y;
    float zDirection = interactor->GetPosition().z() - OverlapCenter.z;

    QVector3D vectorToPlayer = QVector3D(xDirection, yDirection, zDirection);
    float pushDistance = radius + interactor->GetRadius() - vectorToPlayer.length();
    if( pushDistance < 0 ) return;

    QVector3D noramlisedVectorToPlayer = vectorToPlayer.normalized();

    QVector3D pushVector = noramlisedVectorToPlayer*pushDistance;

    interactor->PushPlayer(noramlisedVectorToPlayer*pushDistance);
}
