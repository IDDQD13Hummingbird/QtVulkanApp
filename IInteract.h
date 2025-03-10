#ifndef IINTERACT_H
#define IINTERACT_H

#include "IPlayer.h"
class IInteract {
public:
    virtual void Interact(IPlayer* interactor) = 0;
};

#endif // IINTERACT_H
