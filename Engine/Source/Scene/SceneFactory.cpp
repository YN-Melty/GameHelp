#include "Scene/SceneFactory.h"

#include "LabScene.h"

namespace SceneFactory
{
    Scenes CreateScenes(EngineContext &context)
    {
        Scenes scenes;
        scenes.emplace("LabScene", std::make_unique<LabScene::Lab>(context));
        return scenes;
    }
}