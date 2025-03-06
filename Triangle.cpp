#include "Triangle.h"
#include "Vertex.h"
#include "VisualObject.h"

VkTriangle::VkTriangle() : VisualObject()
{
    //Vertex v1{-0.5f,   0.0f,  0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    //Vertex v2{-0.5f,   -0.5f,  0.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    //Vertex v3{0.0f,   0.0f,  0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
    Vertex vA{ -1.0f, 0.0f, 0.0f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };    //A
    Vertex vB{ 0.0f, 0.5f, 0.0f, 0.1f, 0.1f, 0.7f, 0.0f, 0.0f };     //B
    Vertex vC{ 0.0f, -0.5f, 0.0f, 0.8f, 0.8f, 0.7f, 0.0f, 0.0f };    //C
    Vertex vD{ 1.0f, 0.0f, 0.0f, 0.25f, 0.25f, 0.85f, 0.0f, 0.0f };  //D
    Vertex vE{ -2.0f, 0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };    //E
    Vertex vF{ -2.0f, -0.5f, 0.0f, 0.8f, 0.8f, 0.7f, 0.0f, 0.0f };   //F
    Vertex vG{ 0.0f, 0.0f, 0.5f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };     //G
    Vertex vH{ 0.0f, 0.0f, -0.5f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };    //H
    Vertex vI{ -1.75f, 0.0f, 0.0f, 0.25f, 0.25f, 0.85f, 0.0f, 0.0f };//I

    //Vertex v0{ 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };


    Subdivide(vA, vB, vG, 3);
    Subdivide(vA, vB, vH, 3);
    Subdivide(vD, vB, vG, 3);
    Subdivide(vD, vB, vH, 3);
    Subdivide(vA, vC, vG, 3);
    Subdivide(vA, vC, vH, 3);
    Subdivide(vD, vC, vG, 3);
    Subdivide(vD, vC, vH, 3);

    Subdivide(vF, vA, vI, 0);
    Subdivide(vE, vA, vI, 0);

    mMatrix.translate(-0.25f, 0, 0); // fra startNextFrame

    /*
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
    */
}
