#ifndef IOVERLAPHANDLER_H
#define IOVERLAPHANDLER_H

#include "AbstractInteractObject.h"

class IOverlapHandler {
public:
    virtual void Tick(float deltaTime) = 0;
    virtual void AddInteractObject(AbstractInteractObject* object) = 0;
    virtual std::map<std::string, AbstractInteractObject*> GetInteractableObjects() = 0;
};

#endif // IOVERLAPHANDLER_H
