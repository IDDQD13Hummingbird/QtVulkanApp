#include "Triangle.h"
//#include "Vertex.h"

Triangle::Triangle() : VisualObject()
{
    Vertex v1 = {0.f,   0.145f,  0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v2 = {0.14f,   -0.1f,  0.0f,   0.5f, 1.0f, 0.5f, 0.0f, 0.0f};
    Vertex v3 = {-0.14f,   -0.1f,  0.0f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f};
    Vertex top = {0.f,   0.f,  0.1f,   1.0f, 1.0f, 1.0f, 0.0f, 0.0f};

    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(top);

    mVertices.push_back(v2);
    mVertices.push_back(v3);
    mVertices.push_back(top);

    mVertices.push_back(v3);
    mVertices.push_back(v1);
    mVertices.push_back(top);


    srand(time(0));
	//Temporary positioning
    float a, b;
    a = (rand() % 21);
    b = (rand() % 21);
    mMatrix.translate(a, b, 0);
    setPosition({a, b, 0});
    mRadius = 0.145f;

}
