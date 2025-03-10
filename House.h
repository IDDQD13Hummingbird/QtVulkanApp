#ifndef HOUSE_H
#define HOUSE_H

#include "AbstractInteractObject.h"

class House : public AbstractInteractObject
{
private:
    void Init();
public:
    House(IOverlapHandler* listner, float x, float y, float z, std::string name);

    // IInteract interface
public:
    virtual void Interact(IPlayer *interactor) override;
};

#endif // HOUSE_H
