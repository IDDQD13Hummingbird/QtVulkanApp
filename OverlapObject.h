#ifndef OVERLAPOBJECT_H
#define OVERLAPOBJECT_H

#include "IOverlap.h"
#include "VisualObject.h"

class OverlapObject : public VisualObject, public IOverlap
{
private:
    bool bIsActive{1};
protected:
    void Deactivate();
public:
    OverlapObject();
    OverlapObject(std::string name, Vertex OverlapCenter, float radius);

    virtual void move(float x, float y=0.0f, float z=0.0f) override;
    virtual void scale(float s) override;

    bool IsActive();

    // IOverlap interface
public:
    virtual bool CanOverlap() override;

    // IOverlap interface
public:
    void ToggleCanOverlap() override;
    void ToggleVisible() override {ToggleCanOverlap();}
};

#endif // OVERLAPOBJECT_H
