#include "WorldAxis.h"

WorldAxis::WorldAxis()
{
	drawType = 1; // 0 = fill, 1 = line

    mVertices.push_back(Vertex{ -100.f, 0.f, 0.f,       1.f, 0.f, 0.f,    0.f, 0.f, true}); //x-axis
    mVertices.push_back(Vertex{ 100.f, 0.f, 0.f,     1.f, 0.f, 0.f,    0.f, 0.f, true });
    mVertices.push_back(Vertex{ 0.f, -100.f, 0.f,       0.f, 1.f, 0.f,    0.f, 0.f, true }); //y-axis
    mVertices.push_back(Vertex{ 0.f, 100.f, 0.f,     0.f, 1.f, 0.f,    0.f, 0.f, true });
    mVertices.push_back(Vertex{ 0.f, 0.f, -100.f,       0.f, 0.f, 1.f,    0.f, 0.f, true }); //z-axis
    mVertices.push_back(Vertex{ 0.f, 0.f, 100.f,     0.f, 0.f, 1.f,    0.f, 0.f, true });

    mMatrix.setToIdentity();
}

