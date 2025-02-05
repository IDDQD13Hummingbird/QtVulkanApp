#ifndef VKTRIANGLE_H
#define VKTRIANGLE_H


#include <vector>
#include "vertex.h"


class VkTriangle {
public:
    std::vector<Vertex> mVertices;
    VkTriangle();
    std::vector<Vertex> getVertices() { return mVertices; }
};


#endif // VKTRIANGLE_H
