#include "SceneSwapper.h"

SceneSwapper::SceneSwapper(IScene* scene, std::string parentName) : AbstractInteractObject(scene->GetOverlapHandler(), parentName.append("SceneSwapper"), {0, 0, 0, 0, 0, 0, 0, 0}, 1)
{
    SceneSwapper::scene = scene;
}

void SceneSwapper::Interact(IPlayer *interactor)
{
    scene->ToggleScene();
}

void SceneSwapper::ToggleVisible()
{
    //nothing here, because a scene swapper is not visible.
}
