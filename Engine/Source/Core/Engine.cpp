#pragma once

#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "Utils/Log.h"
#include "InputActions.h"
#include "Managers/InputManager.h"

#include <SFML/Graphics.hpp>

Engine::Engine() : window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)),
                           gConfig.windowTitle, 0, sf::State::Fullscreen),
                   context_(window_),
                   scenes_(SceneFactory::CreateScenes(context_)),
                   currentScene_(nullptr),

                   cursorWasVisible_(true)
{

    window_.setIcon(sf::Image("Content/Textures/Icon.jpg"));
    window_.setMinimumSize(window_.getSize() / 2u);
    window_.setKeyRepeatEnabled(false);
    window_.setMouseCursorVisible(false);

    if (gConfig.disableSfmlLogs)
    {
        sf::err().rdbuf(nullptr);
    }

    context_.audio.SetGlobalVolume(gConfig.globalVolume);

    LOG_INFO("Window created");
    // LOG_INFO("Random int: {}", context_.random.Int(1, 10));

    context_.scenes.ChangeScene("StartScene"); // here to change start Scene
}

bool Engine::IsRunning() const
{
    return window_.isOpen();
}

void Engine::ProcessEvents()
{
    if (const auto nextScene = context_.scenes.FetchNextScene())
    {
        EventSceneChange(*nextScene);
    }

    while (const auto event = window_.pollEvent())
    {
        event->visit(EngineVisitor{*this});
        context_.gui.ProcessEvent(*event);

        currentScene_->OnEvent(*event);
    }
}

void Engine::Update()
{
    context_.time.Update();
    context_.cursor.Update(context_.time.GetDeltaTime());
}

void Engine::Render()
{
    window_.clear();

    context_.renderer.BeginDrawing();
    currentScene_->Render();
    window_.draw(sf::Sprite(context_.renderer.FinishDrawing()));

    context_.gui.Render();
    context_.cursor.Render();

    window_.display();
}

void Engine::EventWindowClose()
{
    window_.close();
    LOG_INFO("Window closed");
}

void Engine::EventWindowResized(sf::Vector2u size)
{
    LOG_INFO("Window resized to {}x{}", size.x, size.y);
}

void Engine::EventWindowFocusLost()
{

    LOG_INFO("Window focus lost");
}

void Engine::EventWindowFocusGained()
{

    LOG_INFO("Window focus gained");
}

void Engine::EventWindowScreenshot() const
{
    context_.screenshot.Take();
}

void Engine::EventGamepadConnected(int id)
{
    LOG_INFO("Gamepad {} connected", id);
}

void Engine::EventGamepadDisconnected(int id)
{
    LOG_INFO("Gamepad {} disconnected", id);
}

void Engine::EventSceneChange(const std::string &name)
{
    // TODO implement scene switching logic
    assert(scenes_.contains(name));
    Scene *nextScene = scenes_.at(name).get();

    if (currentScene_)
    {
        currentScene_->OnCleanup();
    }
    context_.input.Clear();

    currentScene_ = nextScene;
    currentScene_->Start();
}

void Engine::EventSceneRestart()
{

    context_.scenes.RestartCurrentScene();
}

void Engine::EventSceneMenuReturn()
{

    context_.scenes.ChangeScene("Menu");

    context_.cursor.SetVisible(true);
    context_.cursor.SetSpeed(gConfig.cursorSpeed);
}
