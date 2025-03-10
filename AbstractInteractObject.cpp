#include "AbstractInteractObject.h"
#include "IOverlapHandler.h"


AbstractInteractObject::AbstractInteractObject(IOverlapHandler *listner, std::string name, Vertex OverlapCenter, float radius) : OverlapObject{name, OverlapCenter, radius}
{
    AddOverlapListner(listner);
}

void AbstractInteractObject::AddOverlapListner(IOverlapHandler* listner)
{
    AbstractInteractObject::listner = listner;
    listner->AddInteractObject(this);
}
