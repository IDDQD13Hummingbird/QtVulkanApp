#include "TriangleSurface.h"
#include "Vertex.h"
#include <fstream>
#include <QDebug>



TriangleSurface::TriangleSurface() : VisualObject()
{

//    Vertex v1{0.0f,   0.0f,  0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
//    Vertex v2{1.0f,   0.0f,  0.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
//    Vertex v3{0.0f,   1.0f,  0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
//    Vertex v4{1.0f,   1.0f,  0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
//    //    Vertex v1{0.0f,   0.0f,  0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
//    //    Vertex v2{1.0f,   0.0f,  0.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
//    //    Vertex v3{0.0f,   1.0f,  0.0f,   0.0f, 0.0f, 1.0f, 0.0f, 0.0f};
//    //    Vertex v4{1.0f,   1.0f,  0.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
//    mVertices.push_back(v1);
//    mVertices.push_back(v2);
//    mVertices.push_back(v3);
//    mVertices.push_back(v3);
//    mVertices.push_back(v2);
//    mVertices.push_back(v4);

    Vertex vA{ -0.5f, 0.0f, 0.0f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };    //A
    Vertex vB{ 0.5f, 0.5f, 0.0f, 0.1f, 0.1f, 0.7f, 0.0f, 0.0f };     //B
    Vertex vC{ 0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.7f, 0.0f, 0.0f };    //C
    Vertex vD{ 1.5f, 0.0f, 0.0f, 0.25f, 0.25f, 0.85f, 0.0f, 0.0f };  //D
    Vertex vE{ -1.5f, 0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };    //E
    Vertex vF{ -1.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.7f, 0.0f, 0.0f };   //F
    Vertex vG{ 0.5f, 0.0f, 0.5f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };     //G
    Vertex vH{ 0.5f, 0.0f, -0.5f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };    //H
    Vertex vI{ -1.25f, 0.0f, 0.0f, 0.25f, 0.25f, 0.85f, 0.0f, 0.0f };//I
    Vertex v0{ 0.5f, 0.0f, 0.0f, 0.2f, 0.2f, 0.8f, 0.0f, 0.0f };    //0






    Vertex v1{ (Get::vX(vB)+Get::vX(vD))/((Get::vLength(vB)+(Get::vLength(vD)+0.5f)/2)),
               (Get::vY(vB)+Get::vY(vD))/((Get::vLength(vB)+(Get::vLength(vD))/2)),
               (Get::vZ(vB)+Get::vZ(vD))/((Get::vLength(vB)+(Get::vLength(vD))/2)),
               (Get::vR(vB)+Get::vR(vD))/((Get::vLength(vB)+(Get::vLength(vD))/2)),
               (Get::vG(vB)+Get::vG(vD))/((Get::vLength(vB)+(Get::vLength(vD))/2)),
               (Get::vB(vB)+Get::vB(vD))/((Get::vLength(vB)+(Get::vLength(vD))/2)),
               0.0f, 0.0f   };
    Vertex v2{ (Get::vX(vB)+Get::vX(vA))/((Get::vLength(vB)+(Get::vLength(vA)+0.5f)/2)),
               (Get::vY(vB)+Get::vY(vA))/((Get::vLength(vB)+(Get::vLength(vA))/2)),
               (Get::vZ(vB)+Get::vZ(vA))/((Get::vLength(vB)+(Get::vLength(vA))/2)),
               (Get::vR(vB)+Get::vR(vA))/((Get::vLength(vB)+(Get::vLength(vA))/2)),
               (Get::vG(vB)+Get::vG(vA))/((Get::vLength(vB)+(Get::vLength(vA))/2)),
               (Get::vB(vB)+Get::vB(vA))/((Get::vLength(vB)+(Get::vLength(vA))/2)),
               0.0f, 0.0f   };
    Vertex v3{ (Get::vX(vC)+Get::vX(vA))/((Get::vLength(vC)+(Get::vLength(vA)+0.5f)/2)),
               (Get::vY(vC)+Get::vY(vA))/((Get::vLength(vC)+(Get::vLength(vA))/2)),
               (Get::vZ(vC)+Get::vZ(vA))/((Get::vLength(vC)+(Get::vLength(vA))/2)),
               (Get::vR(vC)+Get::vR(vA))/((Get::vLength(vC)+(Get::vLength(vA))/2)),
               (Get::vG(vC)+Get::vG(vA))/((Get::vLength(vC)+(Get::vLength(vA))/2)),
               (Get::vB(vC)+Get::vB(vA))/((Get::vLength(vC)+(Get::vLength(vA))/2)),
               0.0f, 0.0f   };
    Vertex v4{ (Get::vX(vC)+Get::vX(vD))/((Get::vLength(vC)+(Get::vLength(vD)+0.5f)/2)),
               (Get::vY(vC)+Get::vY(vD))/((Get::vLength(vC)+(Get::vLength(vD))/2)),
               (Get::vZ(vC)+Get::vZ(vD))/((Get::vLength(vC)+(Get::vLength(vD))/2)),
               (Get::vR(vC)+Get::vR(vD))/((Get::vLength(vC)+(Get::vLength(vD))/2)),
               (Get::vG(vC)+Get::vG(vD))/((Get::vLength(vC)+(Get::vLength(vD))/2)),
               (Get::vB(vC)+Get::vB(vD))/((Get::vLength(vC)+(Get::vLength(vD))/2)),
               0.0f, 0.0f   };


    //---

    mVertices.push_back(vA);
    mVertices.push_back(v2);
    mVertices.push_back(vG);

    mVertices.push_back(vB);
    mVertices.push_back(v2);
    mVertices.push_back(vG);


    //---

    mVertices.push_back(vA);
    mVertices.push_back(v2);
    mVertices.push_back(vH);

    mVertices.push_back(vB);
    mVertices.push_back(v2);
    mVertices.push_back(vH);

    //---
    //---

    mVertices.push_back(vD);
    mVertices.push_back(v1);
    mVertices.push_back(vG);

    mVertices.push_back(vB);
    mVertices.push_back(vG);
    mVertices.push_back(v1);

    //---

    mVertices.push_back(vD);
    mVertices.push_back(v1);
    mVertices.push_back(vH);

    mVertices.push_back(vB);
    mVertices.push_back(vH);
    mVertices.push_back(v1);

    //---
    //---

    mVertices.push_back(vA);
    mVertices.push_back(vG);
    mVertices.push_back(v3);

    mVertices.push_back(vG);
    mVertices.push_back(v3);
    mVertices.push_back(vC);

    //---

    mVertices.push_back(vA);
    mVertices.push_back(vH);
    mVertices.push_back(v3);

    mVertices.push_back(vH);
    mVertices.push_back(v3);
    mVertices.push_back(vC);

    //---
    //---

    mVertices.push_back(vD);
    mVertices.push_back(vG);
    mVertices.push_back(v4);

    mVertices.push_back(v4);
    mVertices.push_back(vC);
    mVertices.push_back(vG);


    //---

    mVertices.push_back(vD);
    mVertices.push_back(vH);
    mVertices.push_back(v4);

    mVertices.push_back(v4);
    mVertices.push_back(vC);
    mVertices.push_back(vH);


    //---
    //---

    //
    mVertices.push_back(vE);
    mVertices.push_back(vI);
    mVertices.push_back(vA);

    mVertices.push_back(vF);
    mVertices.push_back(vA);
    mVertices.push_back(vI);

    mMatrix.scale(0.5f);
    mMatrix.translate(0.5f, 0, 0); // fra startNextFrame
}

TriangleSurface::TriangleSurface(const std::string &filename)
{
    std::ifstream inn(filename);
    if (!inn.is_open())
        return;
    // read input from math part of compulsory
    int n;
    Vertex v;
    inn >> n;
    for (auto i=0; i<n; i++)
    {
        inn >> v;
        mVertices.push_back(v);
        //qDebug() << v.x << v.y << v.z;
    }
    inn.close();
}
