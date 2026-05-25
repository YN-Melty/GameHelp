#include "StartScene.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

using namespace StartMenu;

StartScreen::StartScreen(EngineContext &context)
    : Scene(context),
      backgroundSprite(backgroundTexture),
      startButtonSprite(startButtonTexture)
{
    InitBackground();
}

void StartScreen::InitBackground()
{
    if (!backgroundTexture.loadFromFile(menuStartPath))
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture, true);

    float scaleX = static_cast<float>(gConfig.windowSize.x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(gConfig.windowSize.y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale({scaleX, scaleY});
    backgroundSprite.setColor(sf::Color::White);
    backgroundSprite.setPosition({0.f, 0.f}); // Top-left corner
}

void StartScreen::StartGame()
{
    startButton_ = tgui::Button::create();
    startButton_->getRenderer()->setTexture("Content/Textures/StartMenu/startButton.png");
    startButton_->setSize({200, 80});
    startButton_->setPosition({"40%", "70%"});

    // Lambda to remove button from GUI before changing scene
    startButton_->onPress([this]()
                          {
        if (startButton_) {
            ctx.gui.Remove(startButton_);
            startButton_ = nullptr;
        }
        ctx.scenes.ChangeScene("LabScene"); });

    ctx.gui.Add(startButton_);
}

void StartScreen::Start()
{
    ctx.cursor.SetVisible(true);
    StartGame();
}

void StartScreen::Render() const
{
    ctx.renderer.Draw(backgroundSprite);
}

void StartScreen::OnPause(bool)
{
    if (startButton_)
    {
        ctx.gui.Remove(startButton_);
        startButton_ = nullptr;
    }
}

void StartScreen::Update()
{
}