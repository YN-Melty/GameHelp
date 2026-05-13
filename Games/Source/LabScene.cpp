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
    std::cout << "hello";
    if (!backgroundTexture.loadFromFile(BackgroundPath))
    {
        std::cerr << "Failed to load background image: " << BackgroundPath << std::endl;
    }

    float scaleX = float(gConfig.windowSize.x) / float(backgroundTexture.getSize().x);
    float scaleY = float(gConfig.windowSize.y) / float(backgroundTexture.getSize().y);
    backgroundSprite.setScale({scaleX, scaleY});

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition({0.f, 0.f});
    backgroundSprite.setColor(sf::Color::White);

    std::cout << "Trying to load background at: " << BackgroundPath << std::endl;
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
    finalBoss.getHitBox().setPosition(finalBoss.getSprite().getPosition());
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