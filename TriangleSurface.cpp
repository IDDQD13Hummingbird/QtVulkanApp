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
}
