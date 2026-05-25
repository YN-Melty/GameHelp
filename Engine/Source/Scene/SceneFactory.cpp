#include "Scene/SceneFactory.h"

#include "LabScene.h"
#include "StartScene.h"

namespace SceneFactory
{
    Scenes CreateScenes(EngineContext &context)
    {
        Scenes scenes;
        scenes.emplace("StartScene", std::make_unique<StartMenu::StartScreen>(context));
        scenes.emplace("LabScene", std::make_unique<LabScene::Lab>(context));
        return scenes;
    }
}