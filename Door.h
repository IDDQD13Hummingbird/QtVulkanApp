#ifndef DOOR_H
#define DOOR_H

#include "AbstractInteractObject.h"
#include "IScene.h"
#include "SceneSwapper.h"

class Door : public AbstractInteractObject
{
private:
    SceneSwapper* sceneSwapper;
    bool isOpen{0};
    void ToggleOpen();

    void Init();
public:
    Door(IScene* scene, float x, float y, float z, std::string name);

    // VisualObject interface
public:
    virtual void Tick(float deltaTime) override;

    // IInteract interface
public:
    virtual void Interact(IPlayer *interactor) override;

    // VisualObject interface
public:
    virtual void move(float x, float y, float z) override;


    // IOverlap interface
public:
    virtual void ToggleCanOverlap() override;
};

#endif // DOOR_H
