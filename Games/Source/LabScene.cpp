#include "LabScene.h"

#include "InputActions.h"

#include <iostream>
#include <SFML/Graphics/Texture.hpp>

using namespace LabScene;

Lab::Lab(EngineContext &context) : Scene(context), finalBoss(context), player(context), backgroundSprite(backgroundTexture)
{
    InitBackground();
    InitChar();
}

void Lab::InitChar()
{
    player.initChar();
    finalBoss.initChar();
}

void Lab::InitBackground()
{
    if (!backgroundTexture.loadFromFile(BackgroundPath))
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

void Lab::Start()
{
    ctx.cursor.SetVisible(false);

    ctx.input.Bind(ACTION_MOVE_LEFT, Input::Keyboard{sf::Keyboard::Scan::A});
    ctx.input.Bind(ACTION_MOVE_RIGHT, Input::Keyboard{sf::Keyboard::Scan::D});
    ctx.input.Bind(ACTION_JUMP, Input::Keyboard{sf::Keyboard::Scan::W});
    ctx.input.Bind(ACTION_CROUCH, Input::Keyboard{sf::Keyboard::Scan::S});
}

void Lab::Update()
{
    float moveSpeed = 200.0f;
    float dt = ctx.time.GetDeltaTime();
    float gravity = 800.f;

    float windowWidth = gConfig.windowSize.x;
    float windowHeight = gConfig.windowSize.y;
    float LEFT_WALL = 10.f, RIGHT_WALL = windowWidth - 10.f;
    float CEILING = 10.f, FLOOR = windowHeight - 100.f;

    player.pcAction(ctx.input, dt, moveSpeed, gravity, player.playerHitBox, LEFT_WALL, RIGHT_WALL, CEILING, FLOOR);
    player.playerHitBox.setPosition(player.sprite.getPosition());

    finalBoss.EnemyAction(dt, moveSpeed, gravity, finalBoss.getHitBox(), LEFT_WALL, RIGHT_WALL, CEILING, FLOOR);
    finalBoss.setHitBoxToSprite();
}
void Lab::Render() const
{

    ctx.renderer.Draw(backgroundSprite);
    ctx.renderer.Draw(player.sprite);
    ctx.renderer.Draw(player.playerHitBox);
    ctx.renderer.Draw(finalBoss.getSprite());
    ctx.renderer.Draw(finalBoss.getHitBox());
}
void Lab::OnPause(bool paused)
{
}
void Lab::OnCleanup()
{
}