#ifndef WORLD_H
#define WORLD_H
#include "VisualObject.h"

//Simple 3-axis mesh

class World : public VisualObject
{
public:

    int length = 0;

    World();
    ~World(){};
};

#endif // WORLD_H
