#include "StartScene.h"
#include <SFML/Graphics/Texture.hpp>

using namespace StartMenu;

StartScreen::StartScreen(EngineContext &context) : Scene(context), backgroundSprite(backgroundTexture), startButtonSprite(startButtonTexture)
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
    auto startButton = tgui::Button::create();
    startButton->getRenderer()->setTexture("Content/Textures/StartMenu/startButton.png");
    startButton->setPosition(100, 200);
    startButton->setPosition("80%", "10%");
    // startButton->getRenderer()->setTextureHover(".../myButtonHover.png");
    startButton->onPress([this]()
                         { this->ctx.scenes.ChangeScene("LabScene"); });
}

/*void StartScreen::Render() const
{

}*/
void StartScreen::OnPause(bool)
{
}

void StartScreen::Start()
{
    ctx.cursor.SetVisible(false);
    StartGame();
}

void StartScreen::Update()
{
}
void StartScreen::Render() const
{
    ctx.renderer.Draw(backgroundSprite);
}