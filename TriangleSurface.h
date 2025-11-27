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
    void triangulateDelaunay();
private:
    std::vector<QVector3D> mNormals;private:
    void applyGradient();
    struct point
    {
        float x;
        float z;
        int   index;
    };

    struct triangle
    {
        int v[3];
    };

    struct edge
    {
        int a, b;
    };

    bool point_in_range(const point& p, const triangle& tri, const std::vector<point>& pts) const {
        const point& a = pts[tri.v[0]];
        const point& b = pts[tri.v[1]];
        const point& c = pts[tri.v[2]];

        float ax = a.x - p.x;
        float az = a.z - p.z;
        float bx = b.x - p.x;
        float bz = b.z - p.z;
        float cx = c.x - p.x;
        float cz = c.z - p.z;

        float det =
            (ax * ax + az * az) * (bx * cz - cx * bz) -
            (bx * bx + bz * bz) * (ax * cz - cx * az) +
            (cx * cx + cz * cz) * (ax * bz - bx * az);

        return det > 0.0f;
    } ;

    float orient2d(const point& a, const point& b, const point& c) const {
        return (b.x - a.x) * (c.z - a.z) - (b.z - a.z) * (c.x - a.x);
    };

};

#endif // TRIANGLESURFACE_H
