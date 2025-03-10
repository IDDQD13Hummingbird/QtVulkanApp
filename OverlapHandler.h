#ifndef OVERLAPHANDLER_H
#define OVERLAPHANDLER_H

#include "IOverlapHandler.h"

class OverlapHandler : public IOverlapHandler
{
private:
    std::map<std::string, AbstractInteractObject*> interactableObjects;
public:
    OverlapHandler();

    // IOverlapHandler interface
public:
    virtual void Tick(float deltaTime) override;
    virtual void AddInteractObject(AbstractInteractObject *object) override;
    std::map<std::string, AbstractInteractObject*> GetInteractableObjects() override {return interactableObjects;}
private:
    void CheckOverlap();
};

#endif // OVERLAPHANDLER_H
