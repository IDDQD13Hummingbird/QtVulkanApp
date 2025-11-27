#include "TriangleSurface.h"
#include <fstream>
#include <QDebug>
TriangleSurface::TriangleSurface() : VisualObject()
{
    Vertex v1{ 0.0f,  0.0f,  0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f};  //  bottom-left corner
	Vertex v2{ 1.0f,  0.0f,  0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f }; //  bottom-right corner
	Vertex v3{ 0.0f,  1.0f,  0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f }; //  top-left corner
	Vertex v4{ 1.0f,  1.0f,  0.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f }; //  top-right corner

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

    //Temporary scale and positioning
    mMatrix.scale(0.5f);
    mMatrix.translate(0.5f, 0.1f, 0.1f);
}

// Delaunay triangulation of scattered terrain points ahead.
// Algorithm: incremental insertion (Bowyer–Watson–style) in 2D.
// Based on:
//  - J.R. Shewchuk, "Lecture Notes on Delaunay Mesh Generation", 1999.
//  - Course textbook, chapter 11.


void TriangleSurface::calculateHeightMapNormals()
{
    std::vector<QVector3D> NormalsSum(mVertices.size(), QVector3D(0.f, 0.f, 0.f));

    for (size_t i = 0; i + 2 < mIndices.size(); i += 3)
    {
        uint32_t i0 = mIndices[i];
        uint32_t i1 = mIndices[i + 1];
        uint32_t i2 = mIndices[i + 2];

        const Vertex &v0 = mVertices[i0];
        const Vertex &v1 = mVertices[i1];
        const Vertex &v2 = mVertices[i2];

        QVector3D p0(v0.x, v0.y, v0.z);
        QVector3D p1(v1.x, v1.y, v1.z);
        QVector3D p2(v2.x, v2.y, v2.z);

        QVector3D e1 = p1 - p0;
        QVector3D e2 = p2 - p0;

        QVector3D NormalFace = QVector3D::crossProduct(e1, e2);
        if (!NormalFace.isNull())
            NormalFace.normalize();

        NormalsSum[i0] += NormalFace;
        NormalsSum[i1] += NormalFace;
        NormalsSum[i2] += NormalFace;
    }
}

void TriangleSurface::applyGradient()
{
    if (mVertices.empty())
        return;

    float minY = mVertices[0].y;
    float maxY = mVertices[0].y;

    for (const auto &v : mVertices)
    {
        if (v.y < minY) minY = v.y;
        if (v.y > maxY) maxY = v.y;
    }

    float range = maxY - minY;
    if (range <= 0.0001f)
        range = 1.0f;

    for (auto &v : mVertices)
    {
        float t = (v.y - minY) / range;   // 0..1

        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;

        v.r = t;
        v.g = t;
        v.b = t;
    }
}

/*

void TriangleSurface::triangulateDelaunay(){
    std::vector<point> pts;
    pts.reserve(mVertices.size());

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minZ = std::numeric_limits<float>::max();
    float maxZ = std::numeric_limits<float>::lowest();

    for (int i = 0; i < static_cast<int>(mVertices.size()); ++i)
    {
        const auto& v = mVertices[i];
        point p { v.x, v.z, i };
        pts.push_back(p);

        minX = std::min(minX, p.x);
        maxX = std::max(maxX, p.x);
        minZ = std::min(minZ, p.z);
        maxZ = std::max(maxZ, p.z);
    }

    float dx = maxX - minX;
    float dz = maxZ - minZ;
    float deltaMax = std::max(dx, dz);
    float midX = (minX + maxX) * 0.5f;
    float midZ = (minZ + maxZ) * 0.5f;

    int super0 = static_cast<int>(pts.size());
    int super1 = static_cast<int>(pts.size()) + 1;
    int super2 = static_cast<int>(pts.size()) + 2;

    pts.push_back({ midX - 2 * deltaMax, midZ - deltaMax, -1 });
    pts.push_back({ midX,                 midZ + 2 * deltaMax, -1 });
    pts.push_back({ midX + 2 * deltaMax, midZ - deltaMax, -1 });

    std::vector<triangle> triangles;
    triangles.push_back({ { super0, super1, super2 } });

    for (int pi = 0; pi < super0; ++pi)
    {
        const auto& p = pts[pi];

        // Find bad triangles
        std::vector<int> badTriangles;
        for (int ti = 0; ti < static_cast<int>(triangles.size()); ++ti)
        {
            if (point_in_range(p, triangles[ti], pts))
            {
                badTriangles.push_back(ti);
            }
        }

        // Find edges around bad triangles
        std::vector<edge> edges;
        for (int idx : badTriangles)
        {
            const auto& t = triangles[idx];

            edge e0{ t.v[0], t.v[1] };
            edge e1{ t.v[1], t.v[2] };
            edge e2{ t.v[2], t.v[0] };

            edges.push_back(e0);
            edges.push_back(e1);
            edges.push_back(e2);
        }

        // Note down bad triangles
        std::vector<bool> removed(triangles.size(), false);
        for (int idx : badTriangles)
            removed[idx] = true;

        // Remove duplicate edges (edges shared by two bad triangles)
        std::vector<edge> boundary;
        for (int i = 0; i < static_cast<int>(edges.size()); ++i)
        {
            bool shared = false;
            for (int j = 0; j < static_cast<int>(edges.size()); ++j)
            {
                if (i == j) continue;
                if (edges[i].a == edges[j].b &&
                    edges[i].b == edges[j].a)
                {
                    shared = true;
                    break;
                }
            }
            if (!shared)
                boundary.push_back(edges[i]);
        }

        // Remove bad triangles from the list
        std::vector<triangle> newTriangles;
        newTriangles.reserve(triangles.size());
        for (int i = 0; i < static_cast<int>(triangles.size()); ++i)
        {
            if (!removed[i])
                newTriangles.push_back(triangles[i]);
        }
        triangles.swap(newTriangles);

        // Re-triangulation
        for (const auto& e : boundary)
        {
            triangle nt;
            nt.v[0] = e.a;
            nt.v[1] = e.b;
            nt.v[2] = pi;
            triangles.push_back(nt);
        }
    }

    std::vector<uint32_t> indices;
    indices.reserve(triangles.size() * 3);

    for (const auto& t : triangles)
    {
        if (t.v[0] >= super0 || t.v[1] >= super0 || t.v[2] >= super0)
            continue;

        //Remapping the indexes
        int i0 = pts[t.v[0]].index;
        int i1 = pts[t.v[1]].index;
        int i2 = pts[t.v[2]].index;

        indices.push_back(static_cast<uint32_t>(i0));
        indices.push_back(static_cast<uint32_t>(i1));
        indices.push_back(static_cast<uint32_t>(i2));
    }

    mIndices = std::move(indices);
}
*/

void TriangleSurface::triangulateDelaunay()
{
{
    // Convert vertices to points (x,z)
    std::vector<point> pts;
    pts.reserve(mVertices.size());

    float minX = 1000000000, maxX = -1000000000;
    float minZ = 1000000000, maxZ = -1000000000;

    for (int i = 0; i < mVertices.size(); ++i)
    {
        const auto& v = mVertices[i];
        pts.push_back({v.x, v.z, i});

        minX = std::min(minX, v.x);
        maxX = std::max(maxX, v.x);
        minZ = std::min(minZ, v.z);
        maxZ = std::max(maxZ, v.z);
    }

    float dx = maxX - minX;
    float dz = maxZ - minZ;
    float delta = std::max(dx, dz);

    int super0 = pts.size();
    int super1 = pts.size() + 1;
    int super2 = pts.size() + 2;

    float midX = 0.5f * (minX + maxX);
    float midZ = 0.5f * (minZ + maxZ);

    float scaleX = 1.0f / (maxX - minX);
    float scaleZ = 1.0f / (maxZ - minZ);

    // Temporary storage for triangulation coordinates
    pts.reserve(mVertices.size());

    for (int i = 0; i < mVertices.size(); ++i)
    {
        const auto& v = mVertices[i];
        float nx = (v.x - minX) * scaleX;
        float nz = (v.z - minZ) * scaleZ;
        // both clamped to [0,1]
        pts.push_back({nx, nz, i});
    }


    pts.push_back({midX - 2 * delta, midZ - delta, -1});
    pts.push_back({midX,           midZ + 2 * delta, -1});
    pts.push_back({midX + 2 * delta, midZ - delta, -1});

    std::vector<triangle> tri;
    tri.push_back({super0, super1, super2});

    // INSERT POINTS
    for (int pi = 0; pi < super0; ++pi)
    {
        const point& p = pts[pi];

        std::vector<int> bad;
        for (int i = 0; i < tri.size(); ++i)
        {
            if (point_in_range(p, tri[i], pts))
                bad.push_back(i);
        }

        // Collect boundary edges
        std::vector<edge> edges;
        for (int i : bad)
        {
            triangle& t = tri[i];
            edges.push_back({ t.v[0], t.v[1] });
            edges.push_back({ t.v[1], t.v[2] });
            edges.push_back({ t.v[2], t.v[0] });
        }

        removeDuplicates(edges);

        // Remove bad triangles
        std::vector<triangle> result;
        for (int i = 0; i < tri.size(); ++i)
        {
            if (std::find(bad.begin(), bad.end(), i) == bad.end())
                result.push_back(tri[i]);
        }
        tri.swap(result);

        // Create new triangles using boundary edges
        for (auto& e : edges)
            tri.push_back({ e.a, e.b, pi });
    }

    // OUTPUT INDEX BUFFER
    mIndices.clear();
    for (const auto& t : tri)
    {
        if (t.v[0] >= super0 || t.v[1] >= super0 || t.v[2] >= super0)
            continue;

        mIndices.push_back(pts[t.v[0]].index);
        mIndices.push_back(pts[t.v[1]].index);
        mIndices.push_back(pts[t.v[2]].index);
    }
    }
};


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

    mIndices.clear();
    mIndices.reserve(mVertices.size());
    for (uint32_t i = 0; i < mVertices.size(); ++i)
        mIndices.push_back(i);

    applyGradient();
    calculateHeightMapNormals();
    triangulateDelaunay();
}

