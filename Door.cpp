#include "Door.h"

Door::Door() {
Vertex v1{0.0f,   -0.5f,  0.0f,   0.5f, 0.0f, 0.0f, 0.0f, 0.0f};
Vertex v2{1.0f,   -0.5f,  0.0f,   0.0f, 0.5f, 0.0f, 0.0f, 0.0f};
Vertex v3{0.0f,   0.5f,  0.0f,   0.0f, 0.0f, 0.5f, 0.0f, 0.0f};
Vertex v4{1.0f,   0.5f,  0.0f,   0.5f, 0.5f, 0.0f, 0.0f, 0.0f};

//Pushing 1st triangle,
mVertices.push_back(v1);
mVertices.push_back(v2);
mVertices.push_back(v3);
mVertices.push_back(v4);

//Indexes for the two triangles to form a quad
mIndices.push_back(0);
mIndices.push_back(1);
mIndices.push_back(2);
mIndices.push_back(2);
mIndices.push_back(1);
mIndices.push_back(3);

}

//bool Door::ShallWe(QVector3D Position, float Radius/*, const VisualObject *other)*/
//{
//    QVector3D VectorDist = /*other->*/mPosition - Position;
//    float Dist = VectorDist.length();
//    float minDist = /*other->*/mRadius+Radius+5;
//    if (Dist > minDist) {
//        return false;
//    }
//
//    else { return true; };
//}

