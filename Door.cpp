#include "Door.h"


void Door::ToggleOpen()
{
    isOpen = !isOpen;
    rotate(90, 0, 0, 1);
}

void Door::Init()
{
    Vertex LeftBottomBack{  -0.5f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex RightBottomBack{  0.5f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex LeftTopBack{     -0.5f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex RightTopBack{     0.5f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex LeftBottomFront{ -0.5f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex RightBottomFront{ 0.5f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex LeftTopFront{    -0.5f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex RightTopFront{    0.5f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f};

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

Door::Door(IScene *scene, float x, float y, float z, std::string name) : AbstractInteractObject(scene->GetOverlapHandler(), name, {0, 0, 0, 0, 0, 0, 0, 0}, 6)
{
    bDisplay=0;

    sceneSwapper = new SceneSwapper(scene, mName);
    Init();
    move(x, y, z);

    bDisplay=1;
}

void Door::Tick(float deltaTime)
{
    AbstractInteractObject::Tick(deltaTime);
    sceneSwapper->Tick(deltaTime);
    //VisualObject::rotate(deltaTime*100, 0.f, 1.f, 0.f);
}

void Door::Interact(IPlayer *interactor)
{
    float xDirection = interactor->GetPosition().x() - OverlapCenter.x;
    float yDirection = interactor->GetPosition().y() - OverlapCenter.y;
    float zDirection = interactor->GetPosition().z() - OverlapCenter.z;

    QVector3D vectorToPlayer = QVector3D(xDirection, yDirection, zDirection);
    float distance = vectorToPlayer.length();

    if
        (
            ( distance < (radius - 1) )
            &&
            ( !isOpen )
        )
    {
        ToggleOpen();
        return;
    }

    if
        (
            ( distance >= (radius - 1) )
            &&
            ( isOpen )
        )
    {
        ToggleOpen();
        return;
    }
}

void Door::move(float x, float y, float z)
{
    OverlapObject::move(x, y, z);
    sceneSwapper->move(x, y, z);
}

void Door::ToggleCanOverlap()
{
    OverlapObject::ToggleCanOverlap();
    sceneSwapper->ToggleCanOverlap();
}
