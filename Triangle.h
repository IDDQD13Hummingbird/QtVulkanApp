#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "VisualObject.h"
#include "Vertex.h"

class VkTriangle : public VisualObject {
public:
    //std::vector<Vertex> mVertices;
    VkTriangle();
    //std::vector<Vertex> getVertices() { return mVertices; }

    std::vector<Vertex> vertices() const;
    void setVertices(const std::vector<Vertex> &newVertices);
    void MakeTriangle(const Vertex& a, const Vertex& b, const Vertex& c){
        Vertex v;
        v = { Get::vX(a), Get::vY(a), Get::vZ(a), Get::vR(a), Get::vG(a), Get::vB(a), 0.0f, 0.0f };
        mVertices.push_back(v);
        v = { Get::vX(b), Get::vY(b), Get::vZ(b), Get::vR(b), Get::vG(b), Get::vB(b), 0.0f, 0.0f };
        mVertices.push_back(v);
        v = { Get::vX(c), Get::vY(c), Get::vZ(c), Get::vR(c), Get::vG(c), Get::vB(c), 0.0f, 0.0f };
        mVertices.push_back(v);
    }



    float Normalize(const Vertex& a, const Vertex& b, float off){
        return (Get::vLength(a)+(Get::vLength(b)+off));
    }


    void Subdivide(const Vertex& a, const Vertex& b, const Vertex& c, int n){
        if (n > 0) {
            float v1X = ((Get::vX(a)+Get::vX(b))/Normalize(a, b, 0))/1.5;
            float v1Y = ((Get::vY(a)+Get::vY(b))/Normalize(a, b, 0))/1.5;
            float v1Z = ((Get::vZ(a)+Get::vZ(b))/Normalize(a, b, 0))/1.5;

            float v1R = ((Get::vR(a)+Get::vR(b))/Normalize(a, b, 0))/1.5;
            float v1G = ((Get::vG(a)+Get::vG(b))/Normalize(a, b, 0))/1.5;
            float v1B = ((Get::vB(a)+Get::vB(b))/Normalize(a, b, 0))/1.5;

            Vertex v1 { v1X, v1Y, v1Z, v1R, v1G, v1B, 0.0f, 0.0f };

            float v2X = ((Get::vX(a)+Get::vX(c))/Normalize(a, c, 0))/1.5;
            float v2Y = ((Get::vY(a)+Get::vY(c))/Normalize(a, c, 0))/1.5;
            float v2Z = ((Get::vZ(a)+Get::vZ(c))/Normalize(a, c, 0))/1.5;

            float v2R = ((Get::vR(a)+Get::vR(c))/Normalize(a, c, 0))/1.5;
            float v2G = ((Get::vG(a)+Get::vG(c))/Normalize(a, c, 0))/1.5;
            float v2B = ((Get::vB(a)+Get::vB(c))/Normalize(a, c, 0))/1.5;

            Vertex v2 { v2X, v2Y, v2Z, v2R, v2G, v2B, 0.0f, 0.0f };

            float v3X = ((Get::vX(b)+Get::vX(c))/Normalize(b, c, 0))/1.5;
            float v3Y = ((Get::vY(b)+Get::vY(c))/Normalize(b, c, 0))/1.5;
            float v3Z = ((Get::vZ(b)+Get::vZ(c))/Normalize(b, c, 0))/1.5;

            float v3R = ((Get::vR(b)+Get::vR(c))/Normalize(b, c, 0))/1.5;
            float v3G = ((Get::vG(b)+Get::vG(c))/Normalize(b, c, 0))/1.5;
            float v3B = ((Get::vB(b)+Get::vB(c))/Normalize(b, c, 0))/1.5;

            Vertex v3 { v3X, v3Y, v3Z, v3R, v3G, v3B, 0.0f, 0.0f };

            Subdivide(a, v1, v2, n-1);
            Subdivide(c, v2, v3, n-1);
            Subdivide(b, v3, v1, n-1);
            Subdivide(v3, v2, v1, n-1);
        }
        else {
            MakeTriangle(a, b, c);
        }
    }



};

#endif // TRIANGLE_H
