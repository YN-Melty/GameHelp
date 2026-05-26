#pragma once
#include <SFML/Graphics.hpp>
#include "Core/EngineVisitor.h"
#include "Core/EngineContext.h"
#include "Scene/SceneFactory.h"

class Engine
{
private:
    sf::RenderWindow window_;

    SceneFactory::Scenes scenes_;
    Scene *currentScene_;

    bool cursorWasVisible_;

public:
    EngineContext context_;

    Engine();
    bool IsRunning() const;

    void ProcessEvents();
    void Update();
    void Render();

private:
    friend struct EngineVisitor;

    void EventWindowClose();
    void EventWindowResized(sf::Vector2u size);
    void EventWindowFocusLost();
    void EventWindowFocusGained();
    void EventGamepadConnected(int id);
    void EventGamepadDisconnected(int id);
    void EventWindowScreenshot() const;
    void EventSceneChange(const std::string &name);
    void EventSceneRestart();
    void EventSceneMenuReturn();
};