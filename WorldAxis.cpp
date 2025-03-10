#include "WorldAxis.h"

WorldAxis::WorldAxis()
{
    //drawType = 1; // 0 = fill, 1 = line

    //mVertices.push_back(Vertex{ 0.f, 0.f, 0.f,       1.f, 0.f, 0.f,    0.f, 0.f }); //x-axis
    //mVertices.push_back(Vertex{ 100.f, 0.f, 0.f,     1.f, 0.f, 0.f,    0.f, 0.f });
    //mVertices.push_back(Vertex{ 0.f, 0.f, 0.f,       0.f, 1.f, 0.f,    0.f, 0.f }); //y-axis
    //mVertices.push_back(Vertex{ 0.f, 100.f, 0.f,     0.f, 1.f, 0.f,    0.f, 0.f });
    //mVertices.push_back(Vertex{ 0.f, 0.f, 0.f,       0.f, 0.f, 1.f,    0.f, 0.f }); //z-axis
    //mVertices.push_back(Vertex{ 0.f, 0.f, 100.f,     0.f, 0.f, 1.f,    0.f, 0.f });

    //mMatrix.setToIdentity();

    //mVertices.push_back(Vertex{ 0.f, 0.f, 0.f,       1.f, 0.f, 0.f,    0.f, 0.f }); //x-axis
    //mVertices.push_back(Vertex{ 100.f, 0.f, 0.f,     1.f, 0.f, 0.f,    0.f, 0.f });
    //mVertices.push_back(Vertex{ 0.f, 0.f, 0.f,       0.f, 1.f, 0.f,    0.f, 0.f }); //y-axis
    //mVertices.push_back(Vertex{ 0.f, 100.f, 0.f,     0.f, 1.f, 0.f,    0.f, 0.f });
    //mVertices.push_back(Vertex{ 0.f, 0.f, 0.f,       0.f, 0.f, 1.f,    0.f, 0.f }); //z-axis
    //mVertices.push_back(Vertex{ 0.f, 0.f, 100.f,     0.f, 0.f, 1.f,    0.f, 0.f });

    drawType = 0; // 0 = fill, 1 = line

    //x-axis
    mVertices.push_back(Vertex{ 20.f, -5.f, -5.f,     1.f, 0.75f, 0.75f,    0.f, 0.f });
    //y-axis
    mVertices.push_back(Vertex{ 0.f, 20.f, -5.f,     0.75f, 1.f, 0.75f,    0.f, 0.f });
    //z-axis
    mVertices.push_back(Vertex{ -20.f, -20.f, -5.f,     0.75f, 0.75f, 1.f,    0.f, 0.f });

}

