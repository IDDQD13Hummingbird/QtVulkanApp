#ifndef ISCENE_H
#define ISCENE_H

#include "IOverlapHandler.h"
#include "VisualObject.h"


class IScene
{
public:
    virtual std::vector<VisualObject*> GetObjects() = 0;
    virtual IOverlapHandler* GetOverlapHandler() = 0;
    virtual void ToggleScene() = 0;
    virtual void TickScene(float deltaTime) = 0;
};

#endif // ISCENE_H
