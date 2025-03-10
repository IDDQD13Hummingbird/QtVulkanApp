#ifndef SCENEONE_H
#define SCENEONE_H

#include "IScene.h"

class SceneOne : public IScene
{
public:
    SceneOne();

    // IScene interface
public:
    virtual std::vector<VisualObject *> GetObjects() override;
    virtual IOverlapHandler* GetOverlapHandler() override;
    virtual void ToggleScene() override;
    virtual void TickScene(float deltaTime) override;

private:
    std::vector<VisualObject*> objects;
    IOverlapHandler* overlapHandler;
};

#endif // SCENEONE_H
