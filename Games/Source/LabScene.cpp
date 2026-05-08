#include "LabScene.h"
#include "CharacterManager/Managers/Config/PlayerStatsConfig.h"
#include "InputActions.h"

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

    ctx.input.Bind(ACTION_MOVE_LEFT, Input::Keyboard{sf::Keyboard::Scan::A});
    ctx.input.Bind(ACTION_MOVE_RIGHT, Input::Keyboard{sf::Keyboard::Scan::D});
    ctx.input.Bind(ACTION_JUMP, Input::Keyboard{sf::Keyboard::Scan::W});
    ctx.input.Bind(ACTION_CROUCH, Input::Keyboard{sf::Keyboard::Scan::S});
}

void Lab::Update()
{
    float moveSpeed = 200.0f, dt = ctx.time.GetDeltaTime();
    float windowWidth = gConfig.windowSize.x;
    float windowHeight = gConfig.windowSize.y;
    float LEFT_WALL = 10.f, RIGHT_WALL = windowWidth - 10.f;
    float CEILING = 10.f, FLOOR = windowHeight - 100.f;
    float halfWidth = playerHitBox.getSize().x / 2.f;
    float halfHeight = playerHitBox.getSize().y / 2.f;

    // --- horizontal movement ---
    sf::Vector2f move(0.f, 0.f);
    if (ctx.input.Pressed(ACTION_MOVE_LEFT))
        move.x -= moveSpeed * dt;
    if (ctx.input.Pressed(ACTION_MOVE_RIGHT))
        move.x += moveSpeed * dt;

    // --- gravity & jump ---
    static float velocityY = 0.f;
    static bool onGround = false;
    const float gravity = 800.f;

    // Jump
    if (ctx.input.Pressed(ACTION_JUMP) && onGround)
    {
        velocityY = -400.f;
        onGround = false;
    }

    // Apply gravity
    velocityY += gravity * dt;
    move.y += velocityY * dt;

    // Move
    player.sprite.move(move);
    playerHitBox.move(move);

    // Clamp X (walls)
    sf::Vector2f pos = player.sprite.getPosition();
    pos.x = std::max(LEFT_WALL + halfWidth, std::min(RIGHT_WALL - halfWidth, pos.x));

    // Clamp Y (floor/ceiling)
    if (pos.y >= FLOOR - halfHeight)
    {
        pos.y = FLOOR - halfHeight;
        velocityY = 0.f;
        onGround = true;
    }
    if (pos.y <= CEILING + halfHeight)
    {
        pos.y = CEILING + halfHeight;
        velocityY = 0.f;
    }

    player.sprite.setPosition(pos);
    playerHitBox.setPosition(pos);
}
void Lab::Render() const
{

    ctx.renderer.Draw(backgroundSprite);
    ctx.renderer.Draw(player.sprite);
    ctx.renderer.Draw(playerHitBox);
}
void Lab::OnPause(bool paused)
{
}
void Lab::OnCleanup()
{
}