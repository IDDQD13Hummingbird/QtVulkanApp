#include "Vertex.h"
#include <QtMath>
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes

std::ostream& operator<< (std::ostream& os, const Vertex& v) {
	os << std::fixed;
	os << "(" << v.x << ", " << v.y << ", " << v.z << ") ";
	os << "(" << v.r << ", " << v.g << ", " << v.b << ") ";
	os << "(" << v.u << ", " << v.v << ") ";
	return os;
}
//
/*
float Normalize(const Vertex& a, const Vertex& b, float off){
        (Get::vLength(a)+(Get::vLength(b)+off))/2;
}
*/
/*
void Subdivide(const Vertex& a, const Vertex& b, const Vertex& c, int n){
    if (n > 0) {
        float v1X = (Get::vX(a)+Get::vX(b))/Normalize(a, b, +0.5f);
        float v1Y = (Get::vY(a)+Get::vY(b))/Normalize(a, b, 0);
        float v1Z = (Get::vZ(a)+Get::vZ(b))/Normalize(a, b, 0);

        float v1R = (Get::vR(a)+Get::vR(b))/Normalize(a, b, 0);
        float v1G = (Get::vG(a)+Get::vG(b))/Normalize(a, b, 0);
        float v1B = (Get::vB(a)+Get::vB(b))/Normalize(a, b, 0);

        Vertex v1 { v1X, v1Y, v1Z, v1R, v1G, v1B, 0.0f, 0.0f };

        float v2X = (Get::vX(a)+Get::vX(c))/Normalize(a, c, +0.5f);
        float v2Y = (Get::vY(a)+Get::vY(c))/Normalize(a, c, 0);
        float v2Z = (Get::vZ(a)+Get::vZ(c))/Normalize(a, c, 0);

        float v2R = (Get::vR(a)+Get::vR(c))/Normalize(a, c, 0);
        float v2G = (Get::vG(a)+Get::vG(c))/Normalize(a, c, 0);
        float v2B = (Get::vB(a)+Get::vB(c))/Normalize(a, c, 0);

        Vertex v2 { v2X, v2Y, v2Z, v2R, v2G, v2B, 0.0f, 0.0f };

        float v3X = (Get::vX(b)+Get::vX(c))/Normalize(b, c, +0.5f);
        float v3Y = (Get::vY(b)+Get::vY(c))/Normalize(b, c, 0);
        float v3Z = (Get::vZ(b)+Get::vZ(c))/Normalize(b, c, 0);

        float v3R = (Get::vR(b)+Get::vR(c))/Normalize(b, c, 0);
        float v3G = (Get::vG(b)+Get::vG(c))/Normalize(b, c, 0);
        float v3B = (Get::vB(b)+Get::vB(c))/Normalize(b, c, 0);

        Vertex v3 { v3X, v3Y, v3Z, v3R, v3G, v3B, 0.0f, 0.0f };

        Subdivide(a, v1, v2, n-1);
        Subdivide(c, v2, v3, n-1);
        Subdivide(b, v3, v1, n-1);
        Subdivide(v3, v2, v1, n-1);
    }
    else {
        makeTriangle(a, b, c);
    }
}
*/
//
float Get::vLength(const Vertex& v) {
    float l = qHypot(v.x, v.y, v.z);
    return l;
}

float Get::vX(const Vertex& v) {
    return v.x;
}
float Get::vY(const Vertex& v) {
    return v.y;
}
float Get::vZ(const Vertex& v) {
    return v.z;
}

//

float Get::vColour(const Vertex& v) {

    float cl = qHypot(v.r, v.g, v.b);
    return cl;
}

//
float Get::vR(const Vertex& v) {
    return v.r;
}
float Get::vG(const Vertex& v) {
    return v.g;
}
float Get::vB(const Vertex& v) {
    return v.b;
}
//


std::istream& operator>> (std::istream& is, Vertex& v) {
<<<<<<< Updated upstream
	// Trenger fire tempor�re variabler som kun skal lese inn parenteser og komma
	char dum, dum2, dum3, dum4;
	is >> dum >> v.x >> dum2 >> v.y >> dum3 >> v.z >> dum4;
	is >> dum >> v.r >> dum2 >> v.g >> dum3 >> v.b >> dum4;
	is >> dum >> v.u >> dum2 >> v.v >> dum3;
	return is;
=======
    // Trenger fire temporære variabler som kun skal lese inn parenteser og komma
    char dum, dum2, dum3, dum4;

    is >> dum >> v.x >> dum2 >> v.y >> dum3 >> v.z >> dum4;
    is >> dum >> v.r >> dum2 >> v.g >> dum3 >> v.b >> dum4;
    is >> dum >> v.u >> dum2 >> v.v >> dum3;
    return is;
>>>>>>> Stashed changes
}


