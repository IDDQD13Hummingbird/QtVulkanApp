#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include <string>
#include "VisualObject.h"

//Defaults to a quad, but can read a mesh from file
class TriangleSurface : public VisualObject
{
public:
    TriangleSurface();
    TriangleSurface(const std::string& filename);
    void calculateHeightMapNormals();

private:
    std::vector<QVector3D> mNormals;private:
    void applyGradient();
};

#endif // TRIANGLESURFACE_H
