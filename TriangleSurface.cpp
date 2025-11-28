#include "TriangleSurface.h"
#include <fstream>
#include <limits>
#include <algorithm>
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

    // Test this :
    mVertices = { v1, v2, v3, v4 };

    mIndices = { 0,1,2,  2,1,3 };

    //Temporary scale and positioning
    mMatrix.scale(0.5f);
    mMatrix.translate(0.5f, 0.1f, 0.1f);
}



TriangleSurface::TriangleSurface(const std::string &filename) : VisualObject()
{
    std::ifstream inn(filename);
    if (!inn.is_open())    {
        qWarning() << "Failed to load TriangleSurface, file : " << QString::fromStdString(filename);
        return;
    }
    mVertices.clear();
    mIndices.clear();
    // read input from math part of compulsory
    int n;
    Vertex v;

    // (x, y, z) (r, g, b) (u, v)

    inn >> n;
    for (auto i=0; i<n; i++)
    {
        inn >> v;
        mVertices.push_back(v);
        //qDebug() << v.x << v.y << v.z;
    }
    inn.close();
    /*  This messes up triangulation
    mIndices.clear();
    mIndices.reserve(mVertices.size());
    for (uint32_t i = 0; i < mVertices.size(); ++i)
        mIndices.push_back(i);
    */

    // First we triangulate, then we recalculate normals, then we shade
    // This order is very important, or the code draws nothing

    triangulateDelaunay();

    calculateHeightMapNormals();

    applyGradient();

    //Check that code actually did something :
    qDebug() << "Vertices:" << mVertices.size()
             << "Triangles:" << mIndices.size() / 3;

}



// Delaunay triangulation of scattered terrain points ahead.
// Algorithm: incremental insertion (Bowyer–Watson) in 2D.
// Based on:
//  - J.R. Shewchuk, "Lecture Notes on Delaunay Mesh Generation", February 5, 2012.
//  - Course textbook, chapter 11.


void TriangleSurface::calculateHeightMapNormals()
{
    // Check if code can be applied at all:
    if (mVertices.empty() || mIndices.empty()){
        qDebug() << "Normals failed";
        return;
    }

    std::vector<QVector3D> NormalsSum(mVertices.size(), QVector3D(0.f, 0.f, 0.f));
    // Actually getting mNormals to pass information
    mNormals.assign(mVertices.size(), QVector3D(0,0,0));

    for (size_t i = 0; i + 2 < mIndices.size(); i += 3)
    {
        uint32_t i0 = mIndices[i];
        uint32_t i1 = mIndices[i+1];
        uint32_t i2 = mIndices[i+2];

        QVector3D p0(mVertices[i0].x, mVertices[i0].y, mVertices[i0].z);
        QVector3D p1(mVertices[i1].x, mVertices[i1].y, mVertices[i1].z);
        QVector3D p2(mVertices[i2].x, mVertices[i2].y, mVertices[i2].z);


/*      Old method:
        const Vertex &v0 = mVertices[i0];
        const Vertex &v1 = mVertices[i1];
        const Vertex &v2 = mVertices[i2];

        QVector3D p0(v0.x, v0.y, v0.z);
        QVector3D p1(v1.x, v1.y, v1.z);
        QVector3D p2(v2.x, v2.y, v2.z);

*/
        QVector3D e1 = p1 - p0;
        QVector3D e2 = p2 - p0;


        QVector3D NormalFace = QVector3D::crossProduct(e1, e2);
        if (!NormalFace.isNull()){
            NormalFace.normalize();
        }

        NormalsSum[i0] += NormalFace;
        NormalsSum[i1] += NormalFace;
        NormalsSum[i2] += NormalFace;
    }
/*      No results from this one, investigation ongoing

        QVector3D NormalFace = QVector3D::crossProduct(p1 - p0, p2 - p0);
        if (!NormalFace.isNull()) NormalFace.normalize();

        NormalsSum[i0] += NormalFace;
        NormalsSum[i1] += NormalFace;
        NormalsSum[i2] += NormalFace;
    }

    for (size_t i = 0; i < mVertices.size(); i++)
    {
       QVector3D NormalFace = NormalsSum[i];
        if (!NormalFace.isNull())
            NormalFace.normalize();
        else
            NormalFace = QVector3D(0,1,0);

        mVertices[i].x = NormalFace.x();
        mVertices[i].y = NormalFace.y();
        mVertices[i].z = NormalFace.z();
        QVector3D n = NormalsSum[i];
        if (!n.isNull())
            n.normalize();
        else
            n = QVector3D(0,1,0);

        // store normal in r,g,b  (vertex layout: x,y,z,  r,g,b,  u,v)
        mVertices[i].r = n.x();
        mVertices[i].g = n.y();
        mVertices[i].b = n.z();

    }
*/

    for (QVector3D &n : mNormals)
    {
        if (!n.isNull()) { n.normalize();}
        else {n = QVector3D(0,1,0);};

    }

}

// Because exam demands we render colour gradient for height difference :

void TriangleSurface::applyGradient()
{
    if (mVertices.empty()){
        qDebug() << "Gradient failed";
        return;
    }

    float MinY = mVertices[0].y;
    float MaxY = mVertices[0].y;

    for (const auto &v : mVertices)
    {
        if (v.y < MinY) { MinY = v.y; };
        if (v.y > MaxY) { MaxY = v.y; };
    }
    qDebug() << "Max y : " << MaxY;
    qDebug() << "Min y : " << MinY;

    float range = MaxY - MinY;
    if (range <= 0.0001f) {
        range = 1.0f;
    }

    for (auto &v : mVertices)
    {
        // Our limits : 0.0f - 1.0f
        float grayScaleValue;
        grayScaleValue = (v.y - MinY) / range;
        qDebug() << "Grayscale : " << grayScaleValue;
        //grayScaleValue = (v.y / MaxY); - did I mess up?

        // In case code below doesn't work, use :
        // if (grayscalevalue < 0.0f) grayscalevalue = 0.0f;
        // if (grayscalevalue > 1.0f) grayscalevalue = 1.0f;

        grayScaleValue = std::clamp(grayScaleValue, 0.0f, 1.0f);

        v.r = grayScaleValue;
        v.g = grayScaleValue;
        v.b = grayScaleValue;
    }


    qDebug() << "Gradiented";
}


void TriangleSurface::triangulateDelaunay()
{
    // my code can't run dataset this big all at once.
    // We have to optimize and/or limit the scope.
const int maxN = 5000;

if (static_cast<int>(mVertices.size()) > maxN)
{
        std::vector<Vertex> reduced;
        reduced.reserve(maxN);


        const int step = static_cast<int>(mVertices.size()) / maxN;
        for (int i = 0; i < static_cast<int>(mVertices.size()); i += step)
        {
            reduced.push_back(mVertices[i]);
            if (static_cast<int>(reduced.size()) == maxN)
                break;
        }

        mVertices.swap(reduced);
    }

    const int n = static_cast<int>(mVertices.size());
    if (n < 3)
        return;

    // 1) Build normalized 2D point set (XZ-plane)
    std::vector<point> pts;
    pts.reserve(n);

    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minZ = std::numeric_limits<float>::max();
    float maxZ = std::numeric_limits<float>::lowest();

    for (int i = 0; i < n; ++i)
    {
        const Vertex& v = mVertices[i];
        minX = std::min(minX, v.x);
        maxX = std::max(maxX, v.x);
        minZ = std::min(minZ, v.z);
        maxZ = std::max(maxZ, v.z);
    }

    float dx = maxX - minX;
    float dz = maxZ - minZ;
    float scale = std::max(dx, dz);
    if (scale < 1e-6f) scale = 1.0f;

    for (int i = 0; i < n; ++i)
    {
        const Vertex& v = mVertices[i];
        point p;
        p.x = (v.x - minX) / scale;
        p.z = (v.z - minZ) / scale;
        p.index = i;
        pts.push_back(p);
    }

    // 2) Supertriangle
    // super0 = number of real points;
    // supers are super-triangle vertices
    int super0 = static_cast<int>(pts.size());
    int super1 = super0 + 1;
    int super2 = super0 + 2;

    // big triangle covering [0,1]x[0,1]
    pts.push_back({ -1.0f, -1.0f, -1 }); // super0
    pts.push_back({  2.0f, -1.0f, -1 }); // super1
    pts.push_back({  0.5f,  2.0f, -1 }); // super2

    std::vector<triangle> triangles;
    triangles.push_back({ super0, super1, super2 });

    // 3) Incremental insertion (Bowyer–Watson)
    for (int i = 0; i < super0; i++)
    {
        const point& p = pts[i];

        // Find triangles whose circumcircle contains p
        std::vector<int> badTris;
        for (int i = 0; i < static_cast<int>(triangles.size()); i++)
        {
            if (point_in_range(p, triangles[i], pts))
                badTris.push_back(i);
        }

        // Collect boundary edges of the "hole"
        std::vector<edge> edges;
        for (int idx : badTris)
        {
            const triangle& t = triangles[idx];
            edges.push_back({ t.v[0], t.v[1] });
            edges.push_back({ t.v[1], t.v[2] });
            edges.push_back({ t.v[2], t.v[0] });
        }

        removeDuplicates(edges);

        // Remove bad triangles
        std::vector<triangle> newTris;
        newTris.reserve(triangles.size());
        for (int i = 0; i < static_cast<int>(triangles.size()); i++)
        {
            if (std::find(badTris.begin(), badTris.end(), i) == badTris.end())
                newTris.push_back(triangles[i]);
        }
        triangles.swap(newTris);

        // Retriangulate the hole with new triangles fan around p
        for (const edge& e : edges)
        {
            triangle nt;
            nt.v[0] = e.a;
            nt.v[1] = e.b;
            nt.v[2] = i;
            triangles.push_back(nt);
        }
    }

    // 4) Build index buffer, discard any triangle using supertriangle vertices
    mIndices.clear();
    mIndices.reserve(triangles.size() * 3);

    for (const triangle& t : triangles)
    {
        if (t.v[0] >= super0 || t.v[1] >= super0 || t.v[2] >= super0)
            continue;

        int i0 = pts[t.v[0]].index;
        int i1 = pts[t.v[1]].index;
        int i2 = pts[t.v[2]].index;

        mIndices.push_back(static_cast<uint32_t>(i0));
        mIndices.push_back(static_cast<uint32_t>(i1));
        mIndices.push_back(static_cast<uint32_t>(i2));
    }
}
