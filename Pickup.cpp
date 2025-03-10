#include "Pickup.h"

void Pickup::Init()
{
    Vertex LeftBottomBack{-1.0f,   -1.0f,  -1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex RightBottomBack{1.0f,   -1.0f,  -1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex LeftTopBack{-1.0f,   1.0f,  -1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex RightTopBack{1.0f,   1.0f,  -1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex LeftBottomFront{-1.0f,   -1.0f,  1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex RightBottomFront{1.0f,   -1.0f,  1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex LeftTopFront{-1.0f,   1.0f,  1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex RightTopFront{1.0f,   1.0f,  1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};

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

Pickup::Pickup(IOverlapHandler* listner) : AbstractInteractObject(listner, "pickup", {0, 0, 0, 0, 0, 0, 0, 0}, 1.f) {
    Init();
}

Pickup::Pickup(IOverlapHandler* listner, float x, float y, float z, std::string name) : AbstractInteractObject(listner, name, {0, 0, 0, 0, 0, 0, 0, 0}, 1.f)
{
    bDisplay = 0;
    Init();
    move(x, y, z);
    bDisplay = 1;
}

void Pickup::Tick(float deltaTime)
{
    VisualObject::rotate(deltaTime*100, 0.f, 1.f, 0.f);
}

void Pickup::Interact(IPlayer *interactor)
{
    interactor->AddPoint(1);
    Deactivate();
}
