#include "Triangle.h"
#include "Vertex.h"
#include "VisualObject.h"

Triangle::Triangle() : VisualObject()
{
    //toggleTexture(false);
    mVertices.push_back(Vertex{-0.5f,  -0.275f,  0.0f,   1.0f, 0.5f, 0.5f,   0.0f, 0.0f});
    mVertices.push_back(Vertex{ 0.0f,   0.5f,    0.0f,   0.5f, 0.5f, 1.0f,   1.0f, 0.0f});
    mVertices.push_back(Vertex{ 0.5f,  -0.275f,  0.0f,   0.5f, 1.0f, 0.5f,   0.0f, 1.0f});

	//Temporary positioning
    //mMatrix.translate(-0.25f, 0, 0);
}
