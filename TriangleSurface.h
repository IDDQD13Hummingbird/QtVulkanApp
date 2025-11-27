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

    struct Triangle
    {
        int indexer[3];
        int neighbours[3];
    }; // book proposed version; not needed. We'll use an abridged one, presented below :

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
    float ay = a.z - p.z;

    float bx = b.x - p.x;
    float by = b.z - p.z;

    float cx = c.x - p.x;
    float cy = c.z - p.z;

    float det =
        (ax * ax + ay * ay) * (bx * cy - cx * by) -
        (bx * bx + by * by) * (ax * cy - cx * ay) +
        (cx * cx + cy * cy) * (ax * by - bx * ay);

    return det > 0.0f;
    } ;

    void removeDuplicates(std::vector<edge>& edges) const{

        std::vector<edge> clean;

        for (int i = 0; i < edges.size(); ++i)
        {
            bool duplicate = false;

            for (int j = 0; j < edges.size(); ++j)
            {
                if (i == j) continue;

                if (edges[i].a == edges[j].b &&
                    edges[i].b == edges[j].a)
                {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate)
                clean.push_back(edges[i]);
        }

        edges.swap(clean);
    };

    float orient2d(const point& a, const point& b, const point& c) const {
        return (b.x - a.x) * (c.z - a.z) - (b.z - a.z) * (c.x - a.x);
    };

};

#endif // TRIANGLESURFACE_H
