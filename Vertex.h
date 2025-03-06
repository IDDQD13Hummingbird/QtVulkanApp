#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <qvectornd.h>

struct  Vertex {
    float x;
    float y;
    float z;
 //   Vertex (QVector3D pos) : Pos(pos) {}

//    QVector3D Pos;
    float r;
    float g;
    float b;
    float u;
    float v;

    //! Overloaded ostream operator which writes all vertex data on an open textfile stream
    friend std::ostream& operator<< (std::ostream&, const Vertex&);

    //! Overloaded ostream operator which reads all vertex data from an open textfile stream
    friend std::istream& operator>> (std::istream&, Vertex&);

};

namespace Get {
    float vLength(const Vertex& v);
    float vColour(const Vertex& v);
    };

    namespace Get {
    float vX(const Vertex& v), vY(const Vertex& v), vZ(const Vertex& v),
          vR(const Vertex& v), vG(const Vertex& v), vB(const Vertex& v);
    };



#endif // VERTEX_H
