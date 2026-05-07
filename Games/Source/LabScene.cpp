#include "LabScene.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

using namespace LabScene;

Lab::Lab(EngineContext &context) : Scene(context), backgroundSprite(backgroundTexture)
{
    Lab::InitBackground();
    Lab::InitChar();
}

void Lab::InitChar()
{
    player.sprite.setTexture(player.playerTexture.texture);

    const auto texSize = player.playerTexture.texture.getSize();
    player.sprite.setOrigin({texSize.x / 2.f, texSize.y / 2.f}); // center origin

    player.sprite.setPosition({200.f, 200.f});
    player.sprite.setScale({0.05f, 0.05f}); // much smaller for a 3k image
    player.sprite.setColor(sf::Color::White);

    playerHitBox.setSize({64.f, 96.f});
    playerHitBox.setOrigin(playerHitBox.getSize() / 2.f);
    playerHitBox.setPosition({200.f, 200.f}); // spawn position

    playerHitBox.setFillColor(sf::Color(0, 0, 0, 0)); // fully transparent fill
    playerHitBox.setOutlineColor(sf::Color::Green);   // border color
    playerHitBox.setOutlineThickness(2.f);            // border thickness
}

void Lab::InitBackground()
{
    if (!backgroundTexture.loadFromFile("Content/Textures/Backgrounds/lab.png"))
    {
        std::cout << "FAILED to load background\n";
        return;
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition({0.f, 0.f});
}

void Lab::Start()
{
    ctx.cursor.SetVisible(false);
}

void Lab::Update()
{
}
void Lab::Render() const
{

    ctx.renderer.Draw(backgroundSprite);
    ctx.renderer.Draw(player.sprite);
    ctx.renderer.Draw(playerHitBox);

    /* ctx.renderer.Draw(background);

     ctx.renderer.Draw(paddle.shape);

     for (const auto &ball : balls)
     {
         ctx.renderer.Draw(ball.shape);
     }

     ctx.renderer.Draw(stats.scoreText);
     ctx.renderer.Draw(stats.highScoreText);
     ctx.renderer.Draw(stats.livesText);
     */
}
void Lab::OnPause(bool paused)
{
}
void Lab::OnCleanup()
{
}