#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include "VisualObject.h"
#include "Vertex.h"
#include "ObjMesh.h"

class Heightmap: public VisualObject
{
public:
    Heightmap();
    void makeTerrain(const char* textureData, int grid_size,float horisontal_space, float vertical_space);
    void makeTerrain(const char* textureData, int widthIn, int heightIn);

};


#endif // HEIGHTMAP_H
