#ifndef SCENESWAPPER_H
#define SCENESWAPPER_H

#include "AbstractInteractObject.h"
#include "IScene.h"

class SceneSwapper : public AbstractInteractObject
{
private:
    IScene* scene;
public:
    SceneSwapper(IScene* scene, std::string parentName);

    // IInteract interface
public:
    virtual void Interact(IPlayer *interactor) override;

    // VisualObject interface
public:
    virtual void ToggleVisible() override;
};

#endif // SCENESWAPPER_H
