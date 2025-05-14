#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "VisualObject.h"
#include <string>

class HeightMap : public VisualObject
{
public:
    HeightMap();

    void makeTerrain(std::string heightMapImage);

    void makeTerrain(unsigned char* textureData, int width, int height);

    float calculateBarycentric(const QVector2D& P, const QVector3D& A, const QVector3D& B, const QVector3D& C);
    float getHeightOnMap(float worldX, float worldZ, std::vector<Vertex> mapVertices);

    int getWidth(){ return mWidth; }

private:
    int mWidth{ 0 };
    int mHeight{ 0 };
    int mChannels{ 0 };
};

#endif // HEIGHTMAP_H
