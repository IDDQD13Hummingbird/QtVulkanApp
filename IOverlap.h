#ifndef IOVERLAP_H
#define IOVERLAP_H

#include "vertex.h"


class IOverlap {
protected:
    Vertex OverlapCenter;
    float radius{0.f};
    IOverlap() {
        OverlapCenter = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
    };

    IOverlap(Vertex center, float radius) {
        OverlapCenter = center;
        IOverlap::radius = radius;
    };
    bool bCanOverlap{1};

public:
    virtual bool CheckOverlap(IOverlap* other) {
        if(other == this) return 0; // an object cannot overlap with itself
        if(!CanOverlap()) return false;
        if(!other->CanOverlap()) return false;

        float deltaX = OverlapCenter.x - other->OverlapCenter.x;
        float deltaY = OverlapCenter.y - other->OverlapCenter.y;
        float deltaZ = OverlapCenter.z - other->OverlapCenter.z;
        float distance = sqrt( pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2) );

        float overlapDistance = abs(radius) + abs(other->radius);

        if(distance < overlapDistance) return 1;
        return 0;
    };

    virtual void ToggleCanOverlap() = 0;

    virtual bool CanOverlap() {return bCanOverlap;}

    Vertex const GetCenter() {return OverlapCenter;}
};

#endif // IOVERLAP_H
