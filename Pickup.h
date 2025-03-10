#ifndef PICKUP_H
#define PICKUP_H

#include "AbstractInteractObject.h"


class Pickup : public AbstractInteractObject
{
private:
    void Init();
public:
    Pickup(IOverlapHandler* listner);
    Pickup(IOverlapHandler* listner, float x, float y, float z, std::string name);

    // OverlapObject interface
public:
    void Tick(float deltaTime) override;

    // IInteract interface
public:
    void Interact(IPlayer *interactor) override;
};

#endif // PICKUP_H
