#ifndef ABSTRACTINTERACTOBJECT_H
#define ABSTRACTINTERACTOBJECT_H

#include "IInteract.h"
#include "OverlapObject.h"
class IOverlapHandler;

class AbstractInteractObject : public IInteract, public OverlapObject
{
protected:
    IOverlapHandler* listner;
    void AddOverlapListner(IOverlapHandler* listner);
    AbstractInteractObject(IOverlapHandler *listner, std::string name, Vertex OverlapCenter, float radius);


};

#endif // ABSTRACTINTERACTOBJECT_H
